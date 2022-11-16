from random import randint

def main():
    # get level from user
    level = get_level()

    score = 0
    # ask 10 questions
    for _ in range(10):
        # generate operands
        op1, op2 = generate_integer(level), generate_integer(level)
        # get guess from user

        if get_guess(op1, op2):
            score += 1

    # print final result
    print(f"Score: {score}")


def get_guess(op1, op2):
    # get guess from user.  Returns True if guess is correct, otherwise False
    # allow up to 3 incorrect guesses
    for i in range(0, 3):
        guess = input(f"{op1} + {op2} = ")
        if guess == str(op1 + op2):
            # if correct guess
            return True

        # incorrect guess
        print ("EEE")

    # 3 incorrect guesses
    print(f"{op1} + {op2} = {op1 + op2}")

    return False


def get_level():
    # get level from user
    while True:
        try:
            if (value := int(input("Level: "))) in range(1, 4):
                return value
            else:
                raise ValueError
        except ValueError:
            pass


def generate_integer(level):
    # generate random number with <level> digits
    return randint([0, 10, 100][level - 1], [9, 99, 999][level - 1])


if __name__ == "__main__":
    main()
