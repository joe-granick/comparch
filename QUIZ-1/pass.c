#include <stdio.h>

void modifyByValue(int a, int b)
{
    a = a * 2;
    b = b +5;
    printf("Inside modifyByValue - a: %d, b %d\n", a, b);
}

void modifyByReference(int* a, int* b)
{
    *a = *a * 2;
    *b = *b + 5;
    printf("Inside modifyByReference - a: %d, b %d\n", *a, *b);
}

int main(){
    int x = 10, y = 20;

    printf("Original values - x: %d, y %d\n", x, y);
    
    modifyByValue(x, y);
    printf("After modifyByValue - x: %d, y %d\n", x, y);

    modifyByReference(&x, &y);
    printf("After modifyByReference - x: %d, y %d\n", x, y);
    
    return 0;
}