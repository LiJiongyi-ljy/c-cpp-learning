#include <stdio.h>

int main(void)
{      
    int score = 85;    //" = " means assignment

    //if statement
    if (score >= 90)        //if (condition statement(条件语句))    The core of if is condition evaluation
    {
        printf("A\n");
    }
    else if (score >= 80)   //else if
    {
        printf("B\n");
    }
    else if (score >= 70)   //Important : evaluate from top to bottom
    {
        printf("C\n");
    }
    else                    //else
    {
        printf("D\n");
    }

    //important : " 0 " is represent for " false " , and " !=0 " is represent for " true "
    if (1)  //if (0) the loop body won't execute , and "while (1)" means " infinite loop "
    {
        printf("Hello\n");
    }

    //logical operators

    // && means AND , intersection(交集)
    if (score >= 80 && score <= 90)
    {
        printf("The score is between 80~90.\n");
    }

    // || means OR , union(并集)
    if (score >= 90 || score < 70)
    {
        printf("The score is either A or D.\n");
    }

    // ! means NOT , negation(取反) , complement(非集 补集)     by the way: in "binary bit operation" , you can say "invert" , "bitwise NOT"
    if (!(score < 70))
    {
        printf("The score is not D.\n");
    }

    //====================================================================================================================

    int i = 0;

    //while loop
    while (i < 5)   //while (conditions). it means : if i < 5 , execute
    {
        printf("Hello\n");
        i = i + 1;  //without "i=i+1" ,the program will constantly output "Hello". The situation is called "infinite loop(无限循环)"
    }

    //for loop
    for (int i = 0; i < 5; i++)     //for(initialization ; condition ; update). it means : starts from i=0 , if i<5(evaluation) , execute , and add 1 to i ,and then comes back to evaluation
    {                               //i++ means i adds 1 (i--)
        printf("i = %d\n", i );     //the loop has 5 iteration(iteration意为“迭代”，这个循环进行了 5 次迭代（即一共执行五次）)
    }

    //do...while
    do
    {
        printf("do..while %d\n", i);  //loop body
        i++;                //loop body
    }
    while (i < 3);  //while (condition)
                    //what's the difference between while and do...while ?
                    //in "while" the program while evaluate first, then execute
                    //in "do..while" the program while execute first, then evaluate
                    //so when users want to "do at least once", do...while would be suitable

    //break
    for (int i = 0; i < 10; i++)
    {
        printf("break %d\n", i);

        if (i == 3)
        {
            break;  //break : 直接结束循环
        }
    }

    //continue
    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
        {
            continue;   //continue : 跳过当前这一轮，直接进入下一轮
        }

        printf("continue %d\n", i);
    }

    //nested loop
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("i = %d, j = %d\n", i, j);
        }
    }
                    //运行结果
                    //i = 0, j = 0
                    //i = 0, j = 1
                    //i = 1, j = 0
                    //i = 1, j = 1
                    //i = 2, j = 0
                    //i = 2, j = 1

    return 0;
}
