months = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
]

def main():

    while True:
        # get user input
        input_date = input("Date: ").strip()

        try:
            if '/' in input_date:
                # split short format date
                month, day, year = input_date.split('/')
                long_format = False
            else:
                # split long format date
                month, day, year = input_date.split(' ')
                long_format = True
        except (ValueError):
                # re-prompt
                continue

        try:
            # validate day, month and year
            day = validate_day(day, long_format)
            month = validate_month(month, long_format)
            year = validate_year(year)
            break
        except ValueError:
            # if not valid, re-prompt
            continue

    # print date in iso format
    print(format_iso_date(year, month, day))


def format_iso_date(year, month, day):
    # format day, month, year into iso format
    return f"{year:04d}-{month:02d}-{day:02d}"


def validate_day(day, long_format):
    if long_format:
        # remove "," from end of long-format day
        if not day.endswith(","):
            raise ValueError
        day = day[:-1]
    day = int(day)

    # check day is in valid range
    if not(1 <= day <= 31):
        raise ValueError

    return day


def validate_month(month, long_format):
    if long_format:
        # look up month from list if long-format
        if month not in months:
            raise ValueError
        month = months.index(month) + 1
    else:
        month = int(month)

    # check month is in valid range
    if not (1 <= month <= 12):
        raise ValueError

    return month


def validate_year(year):
    year = int(year)

    # check year is in valid range
    if year < 0:
        raise ValueError

    return year


if __name__ == "__main__":
    main()