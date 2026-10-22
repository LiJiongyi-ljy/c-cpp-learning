#include <stdio.h>

int age = 20;
float score = 95.5f;
double pi = 3.1415926535;
char grade = 'A';
char name[]="Tom";
// 放在函数外面为global variable
// 注意字符character和字符串string不是一回事 字符用单引号，字符串用双引号
int main(void)
{
    age=21;     // 给age赋值，不需要声明变量类型type
                // 放在函数里面为 local variable局部变量
    printf("age = %d\n", age);      // *格式说明符（format specifier）* %d→int ; %f→float (%.2f表示保留两位小数) ; %lf→double% ; %c→char ; %s→string 
    printf("score = %f\n", score);  // *转义字符（escape character）* \n → 换行 ; \t → 制表符 ; \\ → 反斜杠 ; \' → 单引号 ; \" → 双引号
    printf("grade = %c\n", grade);
    printf("name = %s\n", name);
    printf("pi = %lf\n", pi);

    return 0;
}
