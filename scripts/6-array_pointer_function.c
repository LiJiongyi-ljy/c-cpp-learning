//array as function parameter
#include <stdio.h>

void print_array(int arr[], int n)  //Important : int arr[] 会调整为 int *arr , "array-to-pointer conversion（数组到指针的转换）" happens here
{                                   //为什么要定义 n ，既然 numbers 这个数组里已经定义有四个元素了？
    for (int i = 0; i < n; i++)     //因为：在定义函数里发生了array-to-pointer conversion，所以实际上numbers转换成了指向第一个元素的指针
    {                               //指针指到从哪里开始，但不知道从哪里结束，所以需要传入array length
        printf("%d\n", arr[i]);
    }
}

void change_first(int arr[])    //为什么指针也能使用 arr[i] ?   因为 arr[i] == *(arr + i)   甚至可以写 i[arr] , 因为 i[arr] == *(i + arr)
{                               //Important : []实际上是 subscript operator(下标运算符)
    arr[0] = 999;               
}

int main(void)
{
    int numbers[4] = {10,20,30,40};     //Important : 假如 printf("%d\n",numbers[4]) 即访问一个数组外的元素
                                        //称 out-of-bounds access(越界访问) , 同时也归于 Undefined Behavior(未定义行为，UB)
                                        //严重时甚至导致 Buffer Overflow(缓冲区溢出)
                                        //其他常见的错误有 off-by-one error(差一错误)
    print_array(numbers,4); //equals to print_array(&numbers[0], 4); array-to-pointer conversion
    
    change_first(numbers);
    printf("unmbers[0] = %d\n", numbers[0]);    //output : numbers[0] = 999

    return 0;
}
