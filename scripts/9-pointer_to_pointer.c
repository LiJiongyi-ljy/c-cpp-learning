#include <stdio.h>
#include <stdlib.h>

int create_number(int **out)    //here "int **out" is "output parameter(输出参数)"
{                       //Important : "int *create_number(void);"  means the output of the function is a pointer
    if (out == NULL)
    {
        return 0;
    }

    int *new_p = malloc(sizeof *new_p); //note: here two "*" have different meanings

    if (new_p == NULL)
    {
        return 0;
    }

    *new_p = 42;

    *out = new_p;

    return 1;
}


int main(void)

{    
    int x = 10;
    int *p = &x;
    int **pp = &p;      //why is here two "*" ? Because ** means pp has to dereference twice to reach the original value(the int)

    printf("x = %d\n", x);
    printf("*p = %d\n", *p);
    printf("*pp = %p\n", (void *)*pp);  // *pp == p
    printf("**pp = %d\n", **pp);        // **pp == *p == x

    int *q = NULL;

    if (create_number(&q) == 0)
    {
        printf("Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Value: %d\n", *q);

    free(q);
    q =NULL;

    return 0;
}
