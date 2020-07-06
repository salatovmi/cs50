import os
import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set") ##https://iexcloud.io/console/


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    if request.method == "GET":
        own = db.execute("SELECT * FROM users_shares where userID = :id and amount > 0", id=session["user_id"])
        cash = db.execute("SELECT cash FROM users WHERE id = :userid",
                          userid=session["user_id"])[0]["cash"]
        for row in own:
            row["cur_price"] = lookup(row["symbol"])["price"]
            row["sum"] = row["cur_price"] * row["amount"]
        return render_template("index.html", own = own, cash = cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":
        shares = float(request.form.get("shares"))
        resp = lookup(request.form.get("symbol"))
        if resp is None:
            return render_template("buy.html", symbol = True)
        total = shares * resp["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = :userid",
                          userid=session["user_id"])[0]["cash"]
        if total > cash:
            return render_template("buy.html", money = True)
        db.execute("UPDATE users SET cash = :rest WHERE id = :userid",
                        rest=cash-total, userid=session["user_id"])
        db.execute("INSERT INTO trades ('userID', 'symbol', 'amount', 'price', 'companyName', 'total', 'date', 'side') VALUES (:userid, :symbol, :amount, :price, :companyName, :total, :date, :side)",
                        userid=session["user_id"],symbol=resp["symbol"],amount=shares,price=resp["price"],companyName=resp["name"],total=total,date=datetime.datetime.now().strftime("%c"),side='buy')
        owns = db.execute("SELECT * FROM users_shares where userID = :id and symbol = :symbol", id=session["user_id"], symbol=resp["symbol"])
        if len(owns) == 0:
            db.execute("INSERT INTO users_shares ('userID', 'symbol', 'amount') VALUES (:id, :symbol, :amount)",
                        id=session["user_id"],symbol=resp["symbol"],amount=shares)
        else:
            db.execute("UPDATE users_shares SET amount = :amount WHERE userID = :id and symbol = :symbol",
                        amount=owns[0]["amount"]+shares, id=session["user_id"],symbol=resp["symbol"])
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "GET":
        empty = False
        trades = db.execute("SELECT * FROM trades where userID = :id", id=session["user_id"])
        if len(trades) == 0:
            empty = True
        return render_template("history.html", trades=trades, empty=empty)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return render_template("login.html", valid_creds = False)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        inp = request.form.get("symbol").replace(" ", "")
        responses = []
        if "," in inp:
            symbols = inp.split(",")
            for s in symbols:
                res = lookup(s)
                if res is not None:
                    responses.append(res)
        else:
            te = lookup(inp)
            if te is not None:
                responses.append(te)
        if len(responses) == 0:
            return render_template("quote.html", again = True, symbol = inp)
        else:
            return render_template("quoted.html", responses = responses)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=username)
        if len(rows) != 0:
            return render_template("register.html", valid_creds = False)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)",
                        username=username, password=password)
            return render_template("login.html", created = True)

    elif request.method == "GET":
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    own = db.execute("SELECT * FROM users_shares where userID = :id and amount > 0", id=session["user_id"])
    if request.method == "GET":
        return render_template("sell.html", own=own)
    elif request.method == "POST":
        for row in own:
            if row["symbol"] == request.form.get("symbol"):
                shares = int(request.form.get("shares"))
                if shares > row["amount"]:
                    return render_template("sell.html", too_much = True, own=own)
                else:
                    db.execute("UPDATE users_shares SET amount = :n_amount where userID =:id and symbol = :symbol",
                                n_amount=row["amount"]-shares,id=session["user_id"],symbol=row["symbol"])
                    cash = db.execute("SELECT cash FROM users where id = :id", id=session["user_id"])[0]["cash"]
                    resp = lookup(row["symbol"])
                    earn = resp["price"] * float(shares)
                    db.execute("UPDATE users SET cash = :n_cash where id = :id",
                                n_cash=cash+earn, id=session["user_id"])
                    db.execute("INSERT INTO trades ('userID', 'symbol', 'amount', 'price', 'companyName', 'total', 'date', 'side') VALUES (:userid, :symbol, :amount, :price, :companyName, :total, :date, :side)",
                        userid=session["user_id"],symbol=resp["symbol"],amount=shares,price=resp["price"],companyName=resp["name"],total=shares*resp["price"],date=datetime.datetime.now().strftime("%c"),side='sell')
                    return redirect("/")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
