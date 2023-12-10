import csv
from cs50 import SQL

# Temp database.
open("new_roster.db", "w").close()
db = SQL("sqlite:///new_roster.db")

db.execute("CREATE TABLE students(id INTEGER, student_name TEXT, PRIMARY KEY(id))")
db.execute("CREATE TABLE houses(id INTEGER, house TEXT, head TEXT, PRIMARY KEY(id))")
db.execute("CREATE TABLE house_assignments(student_id INTEGER, house_id INTEGER, PRIMARY KEY (student_id, house_id),FOREIGN KEY(student_id) REFERENCES students(id), FOREIGN KEY(house_id) REFERENCES houses(id))")

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        student_name = row["student_name"].upper()
        stuid = db.execute("INSERT INTO students(id , student_name) VALUES(?, ?)", row["id"], student_name)
        houid = db.execute("INSERT INTO houses(house, head) VALUES(?, ?)", row["house"], row["head"])
        db.execute("INSERT INTO house_assignments(student_id, house_id) VALUES(?, ?)", stuid, houid)
