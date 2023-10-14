#include <stdio.h>
void Q(int *p)
{
    int q = 15;
    *p = &q;
}

int main(char *argv[], int argc)
{
    int p;
    Q(&p);
    printf("%d\n", p);
}