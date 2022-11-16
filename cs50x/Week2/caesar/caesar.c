#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char rotate(char c, int key);
bool str_isnumeric(string s);
string to_cipher(string plaintext, int key);

int main(int argc, string argv[])
{
    // check if passed cli parameter count if valid and if so is the parameter a valid numeric input
    if (argc != 2 || !str_isnumeric(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // convert input parameter to int
    int key = atoi(argv[1]);

    // get plaintext input from user
    string plaintext = get_string(("plaintext: "));

    // print out cipher text character by character
    printf("ciphertext: ");
    int i = 0;
    while (plaintext[i] != '\0')
    {
        char cipher_char = rotate(plaintext[i], key);
        printf("%c", cipher_char);
        i++;
    }
    printf("\n");
}

char rotate(char c, int key)
{
    // converts char to cipher equivalent is alpha, otherwise returns original char

    if (!isalpha(c))
    {
        // return original char if not an alphabetic character
        return c;
    }
    // default base_char is for lower case char
    char base_char = 'a';
    if (isupper(c))
    {
        // base char for upper case rotation
        base_char = 'A';
    }

    // add cipher key to base char, wrapping round if necessary
    return base_char + (c - base_char + key) % 26;
}

bool str_isnumeric(string s)
{
    // returns true if a string contains only numeric digits else returns false
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] < '0' || s[i] > '9')
        {
            // return false if non-numeric char
            return false;
        }
        i++;
    }

    // return true if only numeric chars found
    return true;
}

