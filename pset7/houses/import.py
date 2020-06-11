from sys import argv, exit
import csv
from cs50 import SQL

if len(argv) != 2:
    print("missing command-line argument")
    exit(1)


def insert_into_table(query):
    db = SQL("sqlite:///students.db")
    db.execute(query)


def csv_characters_reader():
    with open(argv[1]) as file:
        reader = csv.reader(file, delimiter=',')
        m = 0
        for row in reader:
            if m == 0:
                m += 1
            else:
                name = row[0].split()
                if len(name) == 3:
                    query = f"insert into students(first, middle, last, house, birth) values ('{name[0]}', '{name[1]}', '{name[2]}', '{row[1]}', {int(row[2])} );"
                else:
                    query = f"insert into students(first, middle, last, house, birth) values ('{name[0]}', NULL, '{name[1]}', '{row[1]}', {int(row[2])} );"
                insert_into_table(query)


csv_characters_reader()