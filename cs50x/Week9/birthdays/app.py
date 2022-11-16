import os
import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # check if in add or update mode
        action = request.form.get("action", "add").lower()

        # get inputs from user
        id = request.form.get("id")
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # validate input data
        errors = []
        if not name:
            errors.append("Name must be entered")

        try:
            date = datetime.datetime(2020, int(month), int(day))    # 2020 chosen as it is a leap year
        except (ValueError, TypeError):
            errors.append("Valid date must be entered")


        # re-render with messages if errors
        if errors:
            birthdays = db.execute("SELECT * FROM birthdays WHERE id!=? ORDER BY name", -1 if id is None else id)
            print(birthdays, id)
            initial = {"name": name, "month": month, "day": day}
            return render_template("index.html", birthdays=birthdays, id=id, initial=initial, errors=errors)

        # update database
        if action == "add":
            birthdays = db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
        elif action == "update":
            db.execute("UPDATE birthdays SET name=?, month=?, day=? WHERE id=?", name, month, day, id)

        return redirect("/")
    else:
        # Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY name")
        return render_template("index.html", birthdays=birthdays)

@app.route("/update", methods=["POST"])
def update():
        # called if delete or update buttons in table clicked
        # get user inputs
        id = request.form.get("id")
        action = request.form.get("action").lower()

        if action == "delete":
            # remove record from database
            db.execute("DELETE FROM birthdays WHERE id=?", id)
            return redirect("/")
        elif action == "update":
            # get current details from database for record to be updated
            birthday = db.execute("SELECT * FROM birthdays WHERE id=?", id)
            # redirect if no records found
            if not birthday:
                return redirect("/")
            # get updated list of all birthdays from db
            birthdays = db.execute("SELECT * FROM birthdays WHERE id!=? ORDER BY name", id)
            # set initial values for re-render
            initial = {"name": birthday[0]['name'], "month": birthday[0]['month'], "day": birthday[0]['day']}
            # re-render page for update
            return render_template("index.html", birthdays=birthdays, id=id, initial=initial)
        else:
            return redirect("/")

