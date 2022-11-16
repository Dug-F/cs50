from cs50 import get_float


def main():
    while True:
        # multiply input by 100 to remove any floating point issues
        change_owed = get_float("Changed owed: ") * 100
        if change_owed > 0:
            break

    # coins to be used
    coins_available = [25, 10, 5, 1]

    coin_count = 0
    change_remaining = change_owed

    # iterate through each available coin
    for coin in coins_available:
        coin_count += int(change_remaining / coin)
        change_remaining = change_remaining % coin
        if change_remaining == 0:
            break

    print(coin_count)


if __name__ == "__main__":
    main()