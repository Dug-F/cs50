#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
//              a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p   q  r  s  t  u  v  w  x  y   z

int calc_letter_score(char letter);
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int calc_letter_score(char letter)
{
    // convert letter to lowercase
    char letter_lower = tolower(letter);

    // reject any non-letter characters - scores 0
    if (letter_lower < 'a' || letter_lower > 'z')
    {
        return 0;
    }

    // convert character ASCII code to index for POINTS, starting from a (97) -> 0
    int letter_index = letter_lower - 'a';

    return POINTS[letter_index];
}

int compute_score(string word)
{
    // calculate score for passed word
    int score = 0;
    int i = 0;

    // iterate through word letter by letter until end of string
    while (word[i] != '\0')
    {
        score += calc_letter_score(word[i]);
        i++;
    }

    return score;
}
