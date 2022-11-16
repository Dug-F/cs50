#include <cs50.h>
#include <stdio.h>
int get_height();
void print_characters(int, char);
void print_rows(int);

int main(void)
{
    // get height of pyramid
    int height = get_height();

    // print rows
    print_rows(height);
}

int get_height()
{
    // handle user input of height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;

}

void print_characters(int count, char symbol)
{
    for (int i = 0; i < count; i++)
    {
        printf("%c", symbol);
    }
}

void print_rows(int count)
{
    char brick = '#';
    char space = ' ';

    for (int i = 1; i <= count; i++)
    {
        print_characters(count - i, space);
        print_characters(i, brick);
        printf("\n");
    }
}