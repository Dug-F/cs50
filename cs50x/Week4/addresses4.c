#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    printf("%p\n", s);
    printf("%s\n", s);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);

    printf("%c\n", *s);            // pointer arithmetic
    printf("%c\n", *(s+1));
}