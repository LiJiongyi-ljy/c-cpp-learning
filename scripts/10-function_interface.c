#include <stdio.h>
#include <stdlib.h>

typedef enum    //typedef means type definition / type alias
{           //"enum" means enumeration(枚举) , it's a kind of type. Important : enum can be "anonymous enum(匿名枚举类型)"
    CREATE_OK = 0,
    CREATE_INVALID_ARGUMENT,    //these are "enumeration constants(枚举常量)"
    CREATE_OUT_OF_MEMORY        //Acquiescently, if we define CREATE_OK=0 , C will assgin CREATE_INVALID_ARGUMENT=1 ...
} CreateResult; //枚举名称

CreateResult create_number(int **out)   //Important : the output of create_number() is "CreateResult"(CreateResult is a type) 
{                                       //it can also be written as "CreateResult result = create_number();"
    if (out == NULL)
    {
        return CREATE_INVALID_ARGUMENT;
    }

    *out = NULL;

    int *new_p = malloc(sizeof *new_p);

    if (new_p == NULL)
    {
        return CREATE_OUT_OF_MEMORY;
    }

    *new_p = 42;
    *out = new_p;

    return CREATE_OK;
}

int main(void)
{
    int *p = NULL;

    CreateResult result = create_number(&p);

    if (result != CREATE_OK)
    {
        if (result == CREATE_OUT_OF_MEMORY)
        {
            fputs("Not enough memory.\n", stderr);
        }
        else
        {
            fputs("Invalid output parameter.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    printf("Value: %d\n", *p);

    free(p);
    p = NULL;

    return EXIT_SUCCESS;
}