def main():
    while True:
        # get time from user
        input_time = input("What time is it? ")

        try:
            hours = convert(input_time)
            break
        except (ValueError, TypeError):
            print("Valid inputs [x]x:xx [a.m. or p.m.]")

    if meal := get_meal(hours):
        print(f"{meal}")


def convert(input_time):
    # split expression to get components
    hours, minutes = input_time.lower().split(":")
    # check if input contains am or pm
    if minutes.endswith((' a.m.', ' p.m.')):
        # convert am/pm time to hours
        minutes, meridiem = minutes.split(" ")
        if 'p.m.' in meridiem:
            hours = int(hours) + 12
            if hours > 24:
                raise ValueError
    return int(hours) + float(minutes) / 60


def get_meal(hours):
    # calculate which meal given input time in hours
    if 7 <= hours <= 8:
        return "breakfast time"
    if 12 <= hours <= 13:
        return "lunch time"
    if 18 < hours <= 19:
        return "dinner time"

    return None


if __name__ == "__main__":
    main()