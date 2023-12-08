#include <stdio.h>

int main(void)
{
    // int total = 0;
    // int i, num;
    // printf("0부터 num까지의 덧셈을 합니다. num 입력 : ");
    // scanf("%d", &num);

    // for (i = 0; i < num+1; i++)
    // {
    //     total += i;
    // }

    // printf("0부터 %d까지의 덧셈 결과 : %d \n\n", num, total);


    // int num1, num2, sum1 = 0;
    // printf("Type the two integer number(second num is bigger) : ");
    // scanf("%d %d", &num1, &num2);
    // for(int i = num1; i <= num2; i++)
    // {
    //     sum1 += i;
    // }
    // printf("%d부터 %d까지의 합은 %d 입니다.\n\n", num1, num2, sum1);

    // int cur, is;
    // for(cur=2; cur < 10; cur++)
    // {
    //     printf("\n\n구구단을 외자 구구단을 외자 %d단!\n", cur);
    //     for(is = 1; is < 10; is++)
    //     {
    //         printf("%d x %d = %d\n", cur, is, (cur*is));
    //     }
    // }

    // 팩토리얼 문제
    int num, fac = 1, i = 1;
    printf("입력한 정수의 팩토리얼을 알려드립니다 : ");
    scanf("%d", &num);
    for(; i <= num; i++)
    {
        fac *= i; 
    }
    printf("%d의 팩토리얼 값은 %d 입니다.\n", num, fac);

    return 0;
}