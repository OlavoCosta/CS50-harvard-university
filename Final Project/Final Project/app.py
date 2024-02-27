import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup

# Configure application
app = Flask(__name__)
app.config['JSON_SORT_KEYS'] = False

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///registrations.db")


# Decorator in order to give a new functionality to the line underneath.
@app.route("/home")
@app.route("/")
def home():
    return render_template("home.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        name = request.form.get("name")
        email = request.form.get("email")
        telephone = request.form.get("telephone")
        gender = request.form.get("gender")
        birthdate = request.form.get("birthdate")
        state = request.form.get("state")
        city = request.form.get("city")

        new_user = db.execute("INSERT INTO registration (name, email, telephone, gender, birthdate, state, city) VALUES(?, ?, ?, ?, ?, ?, ?)", name, email, telephone, gender, birthdate, state, city)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

if __name__ == '__main__':
    app.run(debug=True)