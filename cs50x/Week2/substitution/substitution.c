#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char encrypt(char c, string key);
bool isvalid_key(string key);

int main(int argc, string argv[])
{
    // check if passed cli parameter count if valid and if so is the parameter a valid numeric input
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    if (!isvalid_key(key))
    {
        printf("Key is not valid\n");
        return 1;
    }

    // get plaintext input from user
    string plaintext = get_string(("plaintext: "));

    // print out cipher text character by character
    printf("ciphertext: ");
    int i = 0;
    while (plaintext[i] != '\0')
    {
        // cipher the char using the key
        char cipher_char = encrypt(plaintext[i], key);
        printf("%c", cipher_char);
        i++;
    }
    printf("\n");

    return 0;
}

char encrypt(char c, string key)
{
    // converts char to cipher equivalent is alpha, otherwise returns original char

    if (!isalpha(c))
    {
        // return original char if not an alphabetic character
        return c;
    }

    // default base_index is for lower case substitution
    int index = toupper(c) - 'A';
    if (isupper(c))
    {
        // return upper case substitution if c is upper case
        return toupper(key[index]);
    }

    // otherwise return lower case substitution
    return tolower(key[index]);
}

bool isvalid_key(string key)
{
    int i = 0;
    int occurrences[26] = {0};
    while (key[i] != '\0')
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        // convert char to index
        int char_index = toupper(key[i]) - 'A';

        // check if we have seen this char before - if so, error
        if (occurrences[char_index] > 0)
        {
            return false;
        }

        // note that we have seen this char
        occurrences[char_index] = 1;

        i++;
    }

    // if length of key is not 26, error
    if (i != 26)
    {
        return false;
    }

    return true;
}