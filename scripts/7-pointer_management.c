#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p;
    //*p = 100;   //Important : 这里未定义指针p指向哪个地址，会出现 uninitialized pointer(未初始化指针)

    p = NULL;  //Important : null pointer(空指针)

    //dynamic memory allocation(动态内存分配)
    //malloc = memory allocation
    p = malloc(5 * sizeof(int));    //malloc(size)
                    //malloc allocates raw memory   the output of malloc is void * (void pointer / generic pointer / 通用对象指针 / generic object pointer)
    if (p == NULL)  //and "void *" can be implicit conversion(隐式转换) to any other pointer type ,so we don't write "int *p = (int *)malloc(20)"
    {               //Important : in C, there's two types of pointer : 1.Generic pointer; 2.Typed pointer
        return 1;
    }

    p[0] = 10;
    p[1] = 20;
    p[2] = 30;
    p[3] = 40;
    p[4] = 50;

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", p[i]);
    }

    free(p);    //Important : deallocate. free = release dynamically allocated memory(释放动态分配的内存)
                //为什么要free？假如不释放malloc占用的内存，那么程序会不断占用新的内存，这叫 memory leak(内存泄漏)
                //free() means the end of the lifetime of the dynamic memory

    //calloc = contiguous allocation(连续分配)
    p = calloc(5, sizeof(int));     //calloc set all the allocated memory to 0 bits. Assume 4bytes, all bits are zero means"00000000 00000000 00000000 00000000"
                        //function signature : calloc(number_of_elements, size_of_each_element)
    if (p == NULL)
    {
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", p[i]);
    }

    free(p);

    //realloc = resize allocated memory
    int *numbers = malloc(5 * sizeof(int));

    if (numbers == NULL)
    {
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        numbers[i] = (i + 1) * 10;
    }

    printf("Before realloc:\n");

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    int *temp = realloc(numbers, 10 * sizeof(int));     //realloc(p(the pointer that decleared by malloc), new_size)

    if (temp == NULL)   //this step is indispensable , because "realloc" may fail
    {
        free(numbers);
        return 1;
    }

    numbers = temp;

    for (int i = 5; i < 10; i++)
    {
        numbers[i] = (i + 1) * 10;
    }

    printf("After realloc:\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    free(numbers);

    return 0;
}