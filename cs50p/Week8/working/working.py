import re
import sys


def main():
    print(convert(input("Hours: ")))


def convert(s):
    # find match for "09:00 AM to 05:00 PM" format
    if matches := re.search(r"^([0-9]{1,2}):([0-9]{1,2}) (AM|PM) to ([0-9]{1,2}):([0-9]{1,2}) (AM|PM)$", s):
        # validate from and to hours
        for i in [1, 4]:
            validate_hour(matches.group(i))
        # validate from and to minutes
        for i in [2, 5]:
            validate_minute(matches.group(i))

        # calculate from and to hours
        from_hour = convert_hour(matches.group(1), matches.group(3))
        to_hour   = convert_hour(matches.group(4), matches.group(6))

        # return formatted time string
        return (f"{from_hour:02}:{int(matches.group(2)):02} to {to_hour:02}:{int(matches.group(5)):02}")

    # find match for "9 AM to 5 PM" format
    if matches := re.search(r"^([0-9]{1,2}) (AM|PM) to ([0-9]{1,2}) (AM|PM)$", s):
        # validate from and to hours
        for i in [1, 3]:
            validate_hour(matches.group(i))

        # calculate from and to hours
        from_hour = convert_hour(matches.group(1), matches.group(2))
        to_hour   = convert_hour(matches.group(3), matches.group(4))

        # return formatted time string
        return (f"{from_hour:02}:{0:02} to {to_hour:02}:{0:02}")

    # if no match found for either format, raise ValueError
    raise ValueError


def convert_hour(hour, type):
    # calculate hour based on hour entered and AM/PM type
    hour = int(hour)
    if type == "PM" and hour < 12:
        return (hour + 12) % 24
    if type == "AM" and hour == 12:
        return 0
    return hour


def validate_hour(hour):
    # calculate hour is in range
    if (0 <= int(hour) <= 12):
        return True
    raise ValueError


def validate_minute(minute):
    # calculate minute is in range
    if (0 <= int(minute) <= 59):
        return True
    raise ValueError


if __name__ == "__main__":
    main()