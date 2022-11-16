#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int count_letters(string);
int count_sentences(string);
int count_words(string);

int main(void)
{
    string text = get_string("Text: ");

    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);

    double L = (double) letter_count * 100 / word_count;
    double S = (double) sentence_count * 100 / word_count;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    // count the number of letters in text
    // letter is defined as uppercase or lowercase alphabetical character, not punctuation, digits, or other symbols
    int letter_count = 0;
    int i = 0;
    // iterate through characters of text until NUL found
    while (text[i] != '\0')
    {
        if (isalpha(text[i]))
        {
            //increment letter count if valid letter found
            letter_count ++;
        }
        i++;
    }

    return letter_count;
}

int count_sentences(string text)
{
    // count the number of sentences in text
    // sentence is defined as a sequence of characters that ends with a . or a ! or a ?
    int sentence_count = 0;
    int i = 0;
    // iterate through characters of text until NUL found
    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            //increment sentence count if valid ending punctuation found
            sentence_count++;
        }
        i++;
    }

    return sentence_count;
}

int count_words(string text)
{
    // count the number of words in text
    // words is defined as a sequence of characters separated by a space
    int word_count = 0;
    int i = 0;
    // iterate through characters of text until NUL found
    while (text[i] != '\0')
    {
        if (text[i] == ' ')
        {
            //increment word count if space found
            word_count++;
        }
        i++;
    }

    // word count is incremented as the last word is not followed by a space
    return word_count + 1;

}