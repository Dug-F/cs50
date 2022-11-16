import requests
import sys


def main():
    # print cost of n bitcoins where n is command line argument
    if len(sys.argv) < 2:
        sys.exit("Missing command-line argument")

    try:
        # convert command line argument to float
        bitcoins = float(sys.argv[1])
    except (ValueError, IndexError):
        sys.exit("Number of bitcoins must be a float")

    print(f"${get_rate() * bitcoins:,.4f}")


def get_rate():
    # get rate from coindesk
    try:
        response = requests.get("https://api.coindesk.com/v1/bpi/currentprice.json")
        return float(response.json()['bpi']['USD']['rate'].replace(",", ""))
    except (requests.RequestException, ValueError):
        sys.exit("Problem getting bitcoin prices")


if __name__ == "__main__":
    main()