#include <stdio.h>
#include <stdlib.h>

void make(int n) {
    char *s = malloc((n)*sizeof(char));
    for(int i = 0; i<n; i++)
    {
        s[i] = rand() % 256;
        printf("%d", s[i]);
        printf(": ");
        printf("%c\n", s[i]);

    }
    printf("%s\n", s);
    free(s);
}

int main(int argc, char *argv[])
{
    make(15);
}