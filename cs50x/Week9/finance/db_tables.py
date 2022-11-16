import os

from cs50 import SQL

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

db.execute("""
    CREATE TABLE transactions (
        id        INTEGER    PRIMARY KEY AUTOINCREMENT NOT NULL,
        user_id   INTEGER    NOT NULL,
        type      TEXT       NOT NULL,
        symbol    TEXT       NOT NULL,
        price     NUMERIC    NOT NULL,
        shares    INTEGER    NOT NULL,
        timestamp TIMESTAMP  DEFAULT CURRENT_TIMESTAMP NOT NULL,
        FOREIGN KEY (user_id) REFERENCES users (id)
    );
""")

db.execute("""
    CREATE INDEX user_id_idx ON transactions (user_id);
""")
