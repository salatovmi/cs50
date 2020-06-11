from sys import argv, exit
import csv
from cs50 import SQL

if len(argv) != 2:
    print("missing command-line argument")
    exit(1)

db = SQL("sqlite:///students.db")
query = f"select * from students where house = '{argv[1]}' order by last asc"
students = db.execute(query)

for std in students:
    first = std["first"]
    middle = std["middle"]
    if std["middle"] is None:
        print(f"{std['first']} {std['last']}, born {std['birth']}")
    else:
        print(f"{std['first']} {std['middle']} {std['last']}, born {std['birth']}")