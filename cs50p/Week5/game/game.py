from random import randint

def main():
    # get level from user
    level = get_positive_int("Level: ")

    # generate target number to be guessed
    target = randint(1, level)

    # while the guess is not the target number
    while (guess := (get_positive_int("Guess: ") - target)) != 0:
        # if guess is too large
        if guess > 0:
            print("Too large!")
            continue
        # if guess is too small
        print ("Too small!")

    # guess is correct
    print ("Just right!")


def get_positive_int(prompt):
    # get positive integer from user
    while True:
        try:
            if (value := int(input(prompt))) > 0:
                return value
        except ValueError:
            pass


if __name__ == "__main__":
    main()
