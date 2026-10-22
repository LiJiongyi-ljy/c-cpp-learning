#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p = malloc(sizeof(int));

    *p = 100;
                                            //"dangling pointer" 的核心是 a pointer can outlive the object it points to
    free(p);       //after free() , p becomes "dangling pointer" , 因为free是把这块动态分配的内存归还给内存分配系统，使其不再属于你的程序对象
    p = NULL;
    //printf("%d\n", *p);     //Important : this is "use-after-free" , which belongs to UB

    //ownership
    int *p1 = malloc(sizeof(int));

    if (p1 == NULL)
    {
        return 1;
    }

    *p1 = 100;

    int *p2 = p1;   //让p2也指向和p1相同的对象  Important : p2 = p1 和 *p2 = *p1 完全不同
    //alias(别名)   p1和p2都可以称作指向同一个object的aliases
    free(p1);   //ownership
    //free(p2)  //Important : this is "double free(重复释放)" which belongs to UB
    p1 = NULL;  // p1 is "owner" , p2 is "borrower"(this is decided by programmer ,not C)
    free(p1);   //Important : in "free" ,if the argument is null pointer ,free do nothing
    p1 = NULL;

    p2 = NULL;
    
    return 0;
}
