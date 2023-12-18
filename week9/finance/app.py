import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

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

    # Retrieve user's stock portfolio
    user_portfolio = db.execute(
        """
        SELECT
            symbol,
            shares
        FROM
            portfolio
        WHERE
            user_id = ?
    """,
        user_id,
    )

    # Retrieve user's cash balance
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Initialize grand total with cash
    grand_total = cash

    # Add information about each stock by calling lookup
    for stock in user_portfolio:
        stock_info = lookup(stock["symbol"])

        # Ensure the stock_info is not None
        if stock_info:
            stock["current_price"] = stock_info["price"]
            stock["total_holding"] = stock["shares"] * stock_info["price"]
            grand_total += stock["total_holding"]
        else:
            return apology("Error fetching stock information")

    # Round cash and grand total to 2 decimal places
    cash = round(cash, 2)
    grand_total = round(grand_total, 2)

    return render_template(
        "index.html",
        user_portfolio=user_portfolio,
        cash=cash,
        grand_total=grand_total,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # Retrieve the user id.
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("Please enter a symbol")

        quote = lookup(symbol)
        if quote is None:
            return apology("Your symbol does not exist")

        # Validate shares
        try:
            shares = float(shares)
            if shares <= 0 or not shares.is_integer():
                raise ValueError("Invalid number of shares")
        except ValueError:
            return apology("Enter a valid number of shares")

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        if quote["price"] * int(shares) > user_cash[0]["cash"]:
            return apology("Your cash does not satisfy")

        # Update the user cash.
        db.execute("UPDATE users SET cash = cash-?", quote["price"] * int(shares))

        # Add the purchase info to the table.
        db.execute(
            "INSERT INTO purchase_information(user_id, symbol, shares, type, price, date) VALUES(?,?,?,?,?,CURRENT_TIMESTAMP)",
            user_id,
            quote["symbol"],
            int(shares),
            "Buy",
            quote["price"],
        )

        # Calculate the total shares for the user and symbol
        total_shares = db.execute(
            "SELECT SUM(shares) AS total_shares FROM purchase_information WHERE user_id = ? AND symbol = ?",
            user_id,
            quote["symbol"],
        )[0]["total_shares"]

        # Insert or update the portfolio entry
        db.execute(
            "INSERT OR REPLACE INTO portfolio (user_id, symbol, shares) VALUES (?, ?, ?)",
            user_id,
            quote["symbol"],
            total_shares,
        )
        # Flash success message
        flash("Successful purchase!", 'success')
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    # Collect the Data from transactions and join with purchase_information
    transactions = db.execute(
        """
        SELECT
            symbol,
            shares,
            date,
            type,
            price
        FROM
            purchase_information
        WHERE
            user_id = ?
        """,
        user_id,
    )

    print(transactions)
    if not transactions:
        return apology("There are no transactions")

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
        # Ensure that the form is not blank.
        if not symbol:
            return apology("Please enter the symbol")
        quote = lookup(symbol)
        # Ensure that the quote not none.
        if quote is None:
            return apology("invalid symbol")
        return render_template("quoted.html", quote=quote, price=usd(quote["price"]))
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure that the username is not blank.
        if not request.form.get("username"):
            return apology("Please fill the username filed")
        # Ensure that the password is not blank.
        elif not request.form.get("password"):
            return apology("Please fill the password filed")
        # Ensure that the confirmation is not blank.
        elif not request.form.get("confirmation"):
            return apology("Please fill the confirmation filed")
        # Ensure that the username is not match any user in the database.
        rows = db.execute(
            "SELECT username FROM users WHERE username = ?",
            request.form.get("username"),
        )
        if len(rows) != 0:
            return apology("Sorry this username is used, Try another one")
        # Ensure that the password == confirmation.
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("The password filed not match the cofirmation filed")

        # Add the new user to the database.
        hash_pass = generate_password_hash(request.form.get("password"))
        db.execute(
            "INSERT INTO users(username, hash) VALUES(?,?)",
            request.form.get("username"),
            hash_pass,
        )
        # session["user_id"] = request.form.get("username")
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Retrieve user_id from the session
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Validate inputs
        if not symbol or shares <= 0:
            return apology("Invalid input")

        # Check if the user owns enough shares to sell
        user_shares_query = db.execute(
            "SELECT shares FROM portfolio WHERE user_id=? AND symbol=?", user_id, symbol
        )

        total_shares = user_shares_query[0]["shares"] if user_shares_query else 0

        if shares > total_shares:
            return apology("Not enough shares to sell")

        try:
            # Start a transaction
            db.execute("BEGIN")

            # Get the current stock price
            quote = lookup(symbol)

            if not quote:
                raise ValueError("Failed to get stock information")

            # Calculate the total value of the sold shares
            total_value = quote["price"] * shares

            # Update the user's cash
            db.execute(
                "UPDATE users SET cash = cash + ? WHERE id = ?", total_value, user_id
            )

            # Insert a new record for the sell transaction
            db.execute(
                "INSERT INTO purchase_information (user_id, symbol, shares, type, price, date) VALUES (?, ?, ?, ?, ?, CURRENT_TIMESTAMP)",
                user_id,
                quote["symbol"],
                -shares,
                "Sell",
                quote["price"],
            )

            # Calculate the total shares for the user and symbol
            total_shares = db.execute(
                "SELECT SUM(shares) AS total_shares FROM purchase_information WHERE user_id = ? AND symbol = ?",
                user_id,
                symbol,
            )[0]["total_shares"]

            # Update the portfolio entry
            db.execute(
                "UPDATE portfolio SET shares = ? WHERE user_id = ? AND symbol = ?",
                total_shares,
                user_id,
                symbol,
            )

            # Check if the remaining shares are zero and delete the row
            if total_shares == 0:
                db.execute(
                    "DELETE FROM portfolio WHERE user_id = ? AND symbol = ?",
                    user_id,
                    symbol,
                )

            # Commit the transaction
            db.execute("COMMIT")

        except Exception as e:
            # Rollback the transaction in case of an exception
            db.execute("ROLLBACK")
            return apology(f"Transaction failed: {e}")

        # Flash success message
        flash("Successful sale!", 'success')
        return redirect("/")

    # If the request method is GET, render the sell page
    # Retrieve the symbols the user owns
    symbols_query = db.execute("SELECT symbol FROM portfolio WHERE user_id=?", user_id)
    symbol_shares_dict = {}

    # Loop through the symbols
    for symbol_row in symbols_query:
        symbol = symbol_row["symbol"]

        # Select the number of shares of this symbol that the user has
        shares_query = db.execute(
            "SELECT shares FROM portfolio WHERE user_id=? AND symbol=?", user_id, symbol
        )

        # Access the shares value from the query result
        shares = shares_query[0]["shares"] if shares_query else 0

        # Create a new dictionary entry with symbol as key and shares as value
        symbol_shares_dict[symbol] = shares

    return render_template("sell.html", symbol_shares_dict=symbol_shares_dict)


@app.route("/change_password", methods=["GET", "POST"])
def change_password():
    if request.method == "POST" and request.form.get("action") == "change_password":
        # Retrieve user information
        username = request.form.get("username")
        user_info = db.execute(
            "SELECT id, username, hash FROM users WHERE username=?", username
        )

        if not user_info:
            return apology("User not found")

        last_password = request.form.get("last_password")

        if not last_password or not check_password_hash(
            user_info[0]["hash"], last_password
        ):
            return apology("Invalid last password")

        new_password = request.form.get("new_password")

        if not new_password:
            return apology("Enter your new password")

        try:
            # Update the user's password
            db.execute(
                "UPDATE users SET hash = ? WHERE id = ?",
                generate_password_hash(new_password),
                user_info[0]["id"],
            )
        except Exception as e:
            return apology(f"Failed to update password: {e}")

        return redirect("/")

    return render_template("change_password.html")
