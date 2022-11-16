import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
#from password_strength import PasswordPolicy

from helpers import apology, login_required, lookup, usd

from validations import validate_buy_form_data, validate_buy_txn_data, validate_sell_form_data, validate_sell_txn_data

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# policy = PasswordPolicy.from_names(
#     length=8,  # min length: 8
#     uppercase=1,  # need min. 1 uppercase letter
#     numbers=1,  # need min. 1 digit
#     special=1,  # need min. 1 special character
# )


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
    holdings = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id=? GROUP BY symbol ORDER BY symbol", session["user_id"])

    user = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])
    if len(user) < 1:
        return apology("Could not find cash balance")

    positions = []
    positions_balance = 0
    for holding in holdings:
        if not (data := lookup(holding['symbol'])):
            return apology("Stock symbol lookup failed")
        value = holding['total_shares'] * data['price']
        positions.append({"symbol": holding['symbol'], "shares": holding['total_shares'], "price": usd(
            data['price']), "value": usd(value)})
        positions_balance += value

    return render_template("index.html", positions=positions, positions_balance=positions_balance, cash=user[0]['cash'])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if error := validate_buy_form_data(request):
            return apology(error)

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        stock_data = lookup(symbol)
        user_account = db.execute(
            "SELECT * FROM users WHERE id=?", session["user_id"])

        if error := validate_buy_txn_data(request, stock_data, user_account):
            return apology(error)

        cost_of_shares = stock_data['price'] * shares

        # Update user balance in database
        new_balance = user_account[0]['cash'] - cost_of_shares
        db.execute("UPDATE users SET cash=? WHERE id=?",
                   new_balance, session["user_id"])

        # Create transaction record in database
        db.execute("INSERT INTO transactions (user_id, type, symbol, price, shares) VALUES (?, 'BUY', ?, ?, ?)",
                   user_account[0]['id'], symbol.upper(), stock_data['price'], shares)

        # Redirect to home page
        return redirect("/")
    else:
        # Render initial buy page
        return render_template("buy.html")


@app.route("/password", methods=["GET", "POST"])
def change_password():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username")

        # Ensure password, new password and confirmation were submitted
        if not (password and new_password and confirmation):
            return apology("must provide password, new password and confirmation")

        # Ensure password and confirmation match
        print ("passwords", new_password, confirmation)
        if new_password != confirmation:
            return apology("new password and confirmation must match")

        # # check new password confirms to policy
        # pw_result = policy.test(new_password)
        # if len(pw_result) > 0:
        #     return apology("new password must contain an upper, a lower, a number and a special character and be minimum 8 characters")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return apology("invalid username and/or password")

        # Update new password in database
        db.execute("UPDATE users SET hash=? WHERE id=?",
                   generate_password_hash(new_password), session['user_id'])

        # Redirect to login page
        return redirect("/")

    else:
        # Render initial change password page
        return render_template("password.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id=? ORDER BY timestamp", session["user_id"])
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
        if not request.form.get("symbol"):
            return apology("Stock symbol must be entered")

        if not (data := lookup(request.form.get("symbol"))):
            return apology("Stock symbol not found")
        return render_template("quote.html", symbol=request.form.get("symbol"), price=usd(data['price']))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username")

        # Ensure password and confirmation were submitted
        if not (password and confirmation):
            return apology("must provide password and confirmation")

        # Ensure password and confirmation match
        if not password == confirmation:
            return apology("password and confirmation must match")

        # # check new password confirms to policy
        # pw_result = policy.test(password)
        # if len(pw_result) > 0:
        #     return apology("password must contain an upper, a lower, a number and a special character and be minimum 8 characters")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure user does not already exists
        if len(rows) != 0:
            return apology("user already exists")

        # Insert new user into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   username, generate_password_hash(password))

        # Redirect to login page
        return redirect("/login")

    else:
        # Render initial register page
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if error := validate_sell_form_data(request):
            return apology(error)

        symbol = request.form.get("symbol")

        stock_data = lookup(symbol)
        holding = db.execute(
            "SELECT SUM(shares) as total_shares FROM transactions WHERE user_id=? AND symbol=?", session["user_id"], symbol.upper())
        user_account = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])

        if error := validate_sell_txn_data(request, stock_data, user_account, holding):
            return apology(error)

        # calculate proceeds of sale
        proceeds = int(request.form.get("shares")) * stock_data['price']

        db.execute("UPDATE users SET cash=? WHERE id=?",
                   user_account[0]['cash'] + proceeds,  session["user_id"])

        # Create transaction record in database
        db.execute("INSERT INTO transactions (user_id, type, symbol, price, shares) VALUES (?, 'SELL', ?, ?, ?)",
                   user_account[0]['id'], request.form.get("symbol").upper(), stock_data['price'], int(request.form.get("shares")) * (-1))

        # Redirect to home page
        return redirect("/")

    else:
        # render initial sell page
        holdings = db.execute(
            "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id=? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", holdings=holdings)
    return apology("TODO")
