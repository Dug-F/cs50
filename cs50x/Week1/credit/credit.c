#include <cs50.h>
#include <stdio.h>
#include <math.h>
int add_digits(int);
int calc_check_digit_modulus(long);
int first_chars(long, int);
int get_length(long);
long get_number(void);
int is_amex(long);
int is_mastercard(long);
int is_visa(long);

int main(void)
{
    // get card number and validate whether it is valid
    long card_number = get_number();

    int check_digit_modulus = calc_check_digit_modulus(card_number);

    // validate against known card providers
    if (check_digit_modulus == 0)
    {
        if (is_amex(card_number))
        {
            printf("AMEX\n");
            return 0;
        }
        else if (is_visa(card_number))
        {
            printf("VISA\n");
            return 0;
        }
        else if (is_mastercard(card_number))
        {
            printf("MASTERCARD\n");
            return 0;
        }
    }

    printf("INVALID\n");
}

int add_digits(int number)
{
    // sum the individual digits in a number
    int total = 0;
    while (number >= 1)
    {
        int current_digit = number % 10;
        total += current_digit;
        number /= 10;
    }

    return total;
}

int calc_check_digit_modulus(long card_number)
{
    // apply Luhn's algorithm to the card number and return resulting modulus
    int i = 1;
    int even_digits = 0;
    int odd_digits = 0;
    while (card_number >= 1)
    {
        int current_digit = card_number % 10;
        if (i % 2 == 0)
        {
            // for even digits (from the right)
            even_digits += add_digits(current_digit * 2);
        }
        else
        {
            // for odd digits
            odd_digits += current_digit;
        }
        card_number /= 10;
        i++;
    }

    return (even_digits + odd_digits) % 10;
}

int first_chars(long card_number, int digits)
{
    // return the first n digits of a number, n is specified by digits
    int length = get_length(card_number);
    int first_chars = card_number / pow(10.0, (double)(length - digits));
    return first_chars;
}

int get_length(long card_number)
{
    // get number of digits in a number
    return log10((double)(card_number)) + 1;
}

long get_number(void)
{
    // handle user input of credit card number
    long n;
    do
    {
        n = get_long("Credit card number: ");
    }
    while (n < 1);
    return n;
}

int is_amex(long card_number)
{
    // check if card number is a valid american express number
    int first_digits = first_chars(card_number, 2);
    if (first_digits != 34 && first_digits != 37)
    {
        return false;
    }
    int length = get_length(card_number);
    if (length != 15)
    {
        return false;
    }

    return true;

}

int is_mastercard(long card_number)
{
    // check if card number is a valid mastercard number
    int first_digits = first_chars(card_number, 2);
    if (first_digits < 51 || first_digits > 55)
    {
        return false;
    }
    int length = get_length(card_number);
    if (length != 16)
    {
        return false;
    }

    return true;

}

int is_visa(long card_number)
{
    // check if card number is a valid visa number
    int first_digits = first_chars(card_number, 1);
    if (first_digits != 4)
    {
        return false;
    }
    int length = get_length(card_number);
    if (length != 13 && length != 16)
    {
        return false;
    }

    return true;

}