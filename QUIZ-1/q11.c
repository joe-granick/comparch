#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    char* c = strdup(argv[2]); 
    //int n = 15;
    int n;
    n = atoi(argv[1]);
    //c = malloc((strlen(argv[1])+1)); 
    //strcpy(c,argv[1]);
    //int n = atoi(argv[2]);
    for(int i = 0; i < n; i++)
    {
        printf("%s\n", (c+i));
    }
    printf("\n");
 
 //printf("%s", c);
 free(c);

return 0;
}