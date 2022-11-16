def main():
    # get input from user
    greeting = input("Greeting: ")
    print(f"${value(greeting)}")


def value(greeting):
    greeting = greeting.lower().lstrip()
    # check start of greeting and return appropriate amount
    if greeting.startswith("hello"):
        return 0
    if greeting.startswith("h"):
        return 20
    return 100


if __name__ == "__main__":
    main()