#include <stdio.h>

int main(int argc, char *argv[])
{
    int a = 510;
    char *c = (char*)&a;
    printf("%p\n", &a);
    printf("%p\n", (char*)&a);
    printf("%d\n", a);
    printf("%d\n", *c);
    *c =1;
    printf("%p\n", c);
    printf("%d\n", *c);
    printf("%d\n", a);


}