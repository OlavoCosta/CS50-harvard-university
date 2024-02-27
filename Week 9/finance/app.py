import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]

    user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    user_cash = user_cash_db[0]["cash"]

    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price, name FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)

    total_user = user_cash
    total_cash = 0
    for stock in stocks:
        total_cash += float(stock["price"] * stock["shares"])

    total = total_user + total_cash

    return render_template("index.html", database=stocks, cash=user_cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stock = lookup(symbol.upper())

        if not symbol:
            return apology("must type symbol")
        elif stock is None:
            return apology("invalid symbol")
        elif not shares:
            return apology("must type shares")
        elif not shares.isdigit():
            return apology("you cannot purchase partial shares")

        shares = int(shares)
        if shares < 0:
            return apology("must be positive number")
        transaction = shares * stock["price"]

        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        if user_cash > transaction:

            update_user_cash = user_cash - transaction
            db.execute("UPDATE users SET cash = ? WHERE id = ?", update_user_cash, user_id)

            data = datetime.datetime.now()
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price, data, name) VALUES (?, ?, ?, ?, ?, ?)",
                       user_id, symbol, shares, stock["price"], data, stock["name"])

            flash("Bought!")

            return redirect("/")
        else:
            return apology("insufficient funds")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    stocks = db.execute("SELECT symbol, shares, price, data FROM transactions WHERE user_id = ?", user_id)

    return render_template("history.html", database=stocks)


@app.route("/account", methods=["GET", "POST"])
def account():
    """Change password"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        password = request.form.get("password")
        passwordreplay = request.form.get("passwordreplay")

        # Ensure password was submitted
        if not password:
            return apology("must provide password")

        # Ensure passwordreplay was submitted
        elif not passwordreplay:
            return apology("must repete password")

        # Ensure password and password(again) match
        elif not password == passwordreplay:
            return apology("passwords must match")

        user_id = session["user_id"]

        # Generate password hash to store in databse
        hash = generate_password_hash(password)

        # Add new password to users
        hash = db.execute("UPDATE users SET hash = ? WHERE id = ?", hash, user_id)

        flash("Change!")

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("account.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

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

    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must type symbol")

        stock = lookup(symbol.upper())

        if stock is None:
            return apology("invalid symbol")

        return render_template("quoted.html", name=stock["name"], symbol=stock["symbol"], price=stock["price"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username")

        # Ensure password was submitted
        elif not password:
            return apology("must provide password")

        # Ensure passwordreplay was submitted
        elif not confirmation:
            return apology("must replay password")

        # Ensure password and password(again) match
        elif not password == confirmation:
            return apology("passwords must match")

        # Generate password hash to store in databse
        hash = generate_password_hash(password)

        try:
            # Add data to users
            new_user = db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        except:
            return apology("username already exists")

        # Remember which user has register in
        session["user_id"] = new_user

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        user_id = session["user_id"]
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stock = lookup(symbol.upper())

        if not symbol:
            return apology("must select symbol")
        elif not shares:
            return apology("must type shares")

        shares = int(shares)
        shares_own_db = db.execute(
            "SELECT SUM(shares) AS shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)
        shares_own = shares_own_db[0]["shares"]
        if shares > shares_own:
            return apology("not enough shares")

        transaction = shares * stock["price"]

        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        update_user_cash = user_cash + transaction
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_user_cash, user_id)

        data = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, data, name) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, symbol, (-1)*shares, stock["price"], data, stock["name"])

        flash("Sold!")

        return redirect("/")
    else:
        user_id = session["user_id"]
        symbols_user = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
        return render_template("sell.html", symbols=symbols_user)