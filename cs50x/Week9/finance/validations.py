from helpers import lookup

def validate_buy_form_data(request):
    # returns tuple (stock_data, cash_balance, error)

    symbol = request.form.get("symbol")

    # Validate symbol entered
    if not symbol:
        return "Stock symbol must be entered"

    # Validate number of shares entered
    try:
        shares = int(request.form.get("shares"))
    except ValueError:
        return "Number of shares must be a positive whole number"

    if shares < 1:
        return "Number of shares must be a positive whole number"

    return None


def validate_buy_txn_data(request, stock_data, user_account):

    # Validate symbol exists
    if not stock_data:
        return "Stock symbol not found"

    # Get current number of shares
    if not user_account:
        return "User not found"

    cost_of_shares = stock_data['price'] * int(request.form.get("shares"))

    # Valdate sufficient funds available
    if cost_of_shares > user_account[0]['cash']:
        return "Insufficient funds to buy shares"

    return None


def validate_sell_form_data(request):
    # Validate symbol entered
    if not request.form.get("symbol"):
        return "Stock symbol must be entered"

    # Validate number of shares entered
    try:
        shares = int(request.form.get("shares"))
    except (ValueError, TypeError):
        return "Number of shares must be a positive whole number"

    if shares < 1:
        return "Number of shares must be a positive whole number"

    return None


def validate_sell_txn_data(request, stock_data, user_account, holding):
    # Validate symbol exists
    if not stock_data:
        return None, "Stock symbol not found"

    # Validate holds sufficient shares to sell
    try:
        if holding[0]['total_shares'] < int(request.form.get('shares')):
            return "Insufficient shares to sell requested number"
    except (TypeError, ValueError, IndexError):
        return "Insufficient shares to sell requested number"

    # validate user account exists
    if len(user_account) < 1:
        return "Could not find account balance"

    return None