#include <stdio.h>

void say_number(int x)  //function definition（函数定义）   //x function parameter  //the first "void" declears the "return type(返回类型)"
{           //Important : at function declearation , parameter can only be "type" , "value/expression" can be used at function call
    printf("%d\n", x);  //function body
}

void change(int x)
{
    x = 100;
}

void change_by_pointer(int *p)  //在 int *p 里，做参数的是 p 而不是 *p ，* 用于表示：p 是一个指针（pointer）
{                               
    *p = 80;                    //这里 * 是 dereference operator
}

int main(void)
{
    say_number(10);     //function call（函数调用）         //10 argument(实际参数 实参)
    say_number(20);

    int age = 30;
    say_number(age);    //variable can be argument

    change(age);
    printf("age = %d\n", age);    //重要：C的参数是"pass by value(值传递)"  这里输出 age = 30 ，为什么？
                                            //age 在内存中有一个地址，里面存着 30。
                                            //调用 change(age) 时，系统给参数 x 分配了一块新的内存，把 30 复制进去。
                                            //x = 100 只改变了 x 那块内存里的值，完全没有动 age 所在的内存。
                                            //但是如果输入参数的是“指针”的话就不一样了
    change_by_pointer(&age);
    printf("age changed to %d\n");          //这里输出 age changed to 80

    return 0;
}