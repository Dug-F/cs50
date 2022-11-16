from validator_collection import validators, checkers, errors


def main():
    # prompt user for email address input
    email = input("What's your email address: ")

    # valid email address in correct format
    try:
        email_address = validators.email(email, allow_empty=False)
        print("Valid")
    except errors.InvalidEmailError:
        print("Invalid")


if __name__ == "__main__":
    main()