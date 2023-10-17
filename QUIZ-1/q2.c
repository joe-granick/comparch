#include <stdio.h>
void Q(int *p, int q)
{
    printf("%p\n", &q);
    p = &q;
    printf("%p\n", p);
}

int main(char *argv[], int argc)
{
    int p;
    int q = 15;
    Q(&p, q);
    printf("%p\n", &q);
    printf("%p\n", &p);
    printf("%d\n", p);
    return 0;
}