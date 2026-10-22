//address&pointer
#include <stdio.h>

int age = 20;

int main(void)
{
    int *ptr;       //*ptr 表示沿着 ptr 保存的地址，找到那个地址对应的对象，并访问它,int * 告诉编译器这个地址指向的是一个 int 对象
    ptr = &age;     //ptr 表示保存的地址
    //int *ptr = &age;  actually &age == ptr , age 的地址 = ptr 中保存的地址；为什么要有int？因为地址+变量类型（决定访问多少内存）共同帮助C访问对象

    printf("age = %d\n", age);
    printf("address of age = %p\n", (void *)&age);  //get the address of age
    printf("ptr = %p\n", (void *)ptr);              // (void *) 是一个 explicit type conversion(显式类型转换 也可写cast / type cast)，把 int * 转换成 void * ，因为 %p 只能输出地址值，即指针的数值表示
    printf("*ptr = %d\n", *ptr);                                    //C 标准里称它的语法为 cast operator，是一个单目运算符

    //change the value of variable through *ptr
    *ptr = 30;
    printf("age = %d\n",age);

    //符号 * 有两种作用
    //1. 指针声明（int *ptr;），这里 * 是 声明语法（declaration） 的一部分，表示ptr是一个指向int的指针
    //2. 指针使用（*ptr），这里的 * 是 解引用运算符（dereference operator），表示沿着指针ptr保存的地址访问对应的对象
    //3. 并且，指针的类型也表示为 int * , int ** , float * ...

    //===============================================================================================================

    //sizeof(sizeof = size of something) how many bytes does it have?

    printf("char:   %zu bytes\n", sizeof(char));    //char: 1bytes
    printf("int:    %zu bytes\n", sizeof(int));     //int: 4bytes
    printf("float:  %zu bytes\n", sizeof(float));   //float: 4bytes
    printf("double: %zu bytes\n", sizeof(double));  //double: 8bytes
    
    printf("the size of age = %zu\n", sizeof(age)); //sizeof(int)的类型是"size_t",所以对应"%zu"
    printf("sizeof(ptr) = %zu\n", sizeof(ptr));     //how much space does ptr occupy?   actually it's 8 bytes
    //ptr本质需要保存一个内存地址（memory address）   //but why? Because most of the computers are 64-bit system,and 64 bits = 8 bytes
    
    //===============================================================================================================

    //pointer arithmetic & C array
    
    int numbers[4] = {10, 20, 30, 40};  //数组（array）是一组连续存放的、类型相同的对象 An array is a contiguous sequence of objects of the same type

    int *p = numbers;   //numbers本质是一个数组对象，但在大多数表达式中，数组名会转换为指向数组第一个元素的指针，即 array-to-pointer conversion(数组到指针的转换)
    //int *p = &numbers[0];效果相同，p就是第一个元素的地址 first element address
    printf("size of numbers = %zu\n", sizeof(numbers)); //这里使用sizeof()，没有把numbers转换为指针
    printf("size of p = %zu\n", sizeof(p));             //数组≠指针！

    size_t length = sizeof(numbers) / sizeof(numbers[0]);   //典型的C数组长度计算公式（假设int numbers[] = {10, 20, 30, 40};我们不知道数组的大小）
    printf("length of numbers = %zu\n",length); //%zu 是打印​ size_t 类型值的标准写法，z 表示“size_t 类型”，u 表示“无符号十进制（unsigned decimal）”

    printf("numbers[0] = %d\n", numbers[0]);    //numbers[0]  ≈  *(numbers + 0)
    printf("numbers[1] = %d\n", numbers[1]);    //numbers[1]  ≈  *(numbers + 1)
    printf("numbers[2] = %d\n", numbers[2]);    //numbers[2]  ≈  *(numbers + 2)
    printf("numbers[3] = %d\n", numbers[3]);    //numbers[3]  ≈  *(numbers + 3)

    printf("*p       = %d\n", *p);
    printf("*(p + 1) = %d\n", *(p + 1));    //p表示当前这个地址，而p + 1 表示下一个相同类型对象的位置，because pointer arithmetic is scaled(缩放) by the pointed-to type
    printf("*(p + 2) = %d\n", *(p + 2));    //a[b] == *(a + b)
    printf("*(p + 3) = %d\n", *(p + 3));

    return 0;
}
