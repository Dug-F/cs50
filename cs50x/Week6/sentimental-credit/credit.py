from cs50 import get_string


def main():
    # get card number
    while True:
        card_number = get_string('Number: ')
        if not card_number.isdigit():
            continue
        break

    # check if card number passes algorithm test
    valid_card = valid_number(card_number)

    length = len(card_number)
    if not valid_card:
        print("INVALID\n")
    elif all([card_number[0:2] in ['34', '37'], length == 15]):
        print("AMEX\n")
    elif all([card_number[0:2] in ['51', '52', '53', '54', '55'], length == 16]):
        print("MASTERCARD\n")
    elif all([card_number[0] == "4", (length == 13 or length == 16)]):
        print("VISA\n")
    else:
        print("INVALID\n")


def valid_number(card_number):
    # check if card number passes algorithm test
    # returns True if card number passes algorithm, otherwise False
    even_sum = 0
    odd_sum = 0

    for i, number in enumerate(card_number[::-1]):
        if i % 2 == 0:
            # sum odd numbers
            odd_sum += int(number)
        else:
            # sum digits of doubled even numbers
            digits = str(int(number) * 2)
            for digit in digits:
                even_sum += int(digit)

    return not (even_sum + odd_sum) % 10


if __name__ == '__main__':
    main()