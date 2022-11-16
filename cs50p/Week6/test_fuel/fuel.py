def main():
    while True:
        # get user input
        fraction = input("Fraction: ")
        try:
            # convert to % integer
            dec_value = convert(fraction)
            break
        except (ValueError, IndexError, ZeroDivisionError):
            pass

    # print input converted to %
    print(gauge(dec_value))


def convert(value):
    # convert input string in format x/y to integer

    numerator, denominator = value.split("/")
    numerator, denominator = int(numerator), int(denominator)

    if numerator > denominator:
        raise ValueError

    # convert to % integer
    return int(round(numerator / denominator * 100.0))


def gauge(value):
    # convert value to printable string
    if value <= 1:
        return "E"
    if value >= 99:
        return "F"
    return f"{value}%"


if __name__ == "__main__":
    main()