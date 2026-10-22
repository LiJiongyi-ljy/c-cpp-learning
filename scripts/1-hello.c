#include <stdio.h>  //告诉 C 编译器：“我要使用标准输入输出库里的东西。”  stdio = standard input output  
                    //.h = header file  .h 文件是 C 语言的头文件，里面包含了函数的声明和宏定义等内容。
                    // 所以 #include <stdio.h> 即引入标准输入输出相关的声明
int main(void)            //main() 函数是 C 程序的入口点，int表示返回一个整数(若写void则表示不返回任何结果) main(void)表示这个函数不接受参数
{                         ////the first "int" declears the "return type(返回类型)"
    printf("Hello, C!\n");  //调用 printf 函数，把格式化后的内容输出到标准输出
    return 0;              //main 函数执行结束，并向操作系统返回整数 0
}                           //程序退出状态（exit status）的惯例中，0 通常表示成功，非 0 通常表示某种错误或异常状态.但是这里即使return 1也不一定代表异常


//  void hello(void)        一个不接收参数，也不返回结果的函数 第一个void：函数不返回值 第二个void：函数不接受参数
//  {
//      printf("Hello!\n");
//  }