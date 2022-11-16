from datetime import date, datetime
import inflect
import sys


def main():
    # get input from user
    birthdate = input("Birthdate: ")

    # calc and print elapsed minutes
    elapsed_minutes = calc_elapsed_minutes(birthdate)
    print(number_to_words(elapsed_minutes))


def calc_elapsed_minutes(date_string):
    # calc elapsed minutes between passed date and today (both assumed to be midnight)
    start_date = to_datetime(date_string)
    today = date.today()
    end_date = datetime(today.year, today.month, today.day)

    return (end_date - start_date).days * 24 * 60

def number_to_words(number):
    # convert number to words representation of number
    inf = inflect.engine()
    words = inf.number_to_words(number, andword="")
    return f"{words.capitalize()} minutes"

def to_datetime(date_string):
    # convert date string to datetime object (assumed midnight)
    try:
        year, month, day = date_string.split('-')
        return datetime(int(year), int(month), int(day))
    except ValueError:
        sys.exit("Invalid date")


if __name__ == "__main__":
    main()