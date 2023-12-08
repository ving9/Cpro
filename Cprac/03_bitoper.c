#include <stdio.h>

int main(void)
{
    // int num1 = 2, num2 =3;
    // int result1 = num1 & num2;
    // int result2 = num1 | num2;
    // int result3 = num1 ^ num2;
    // printf("%d %d %d\n", result1, result2, result3);

    // int num1 = 1;
    // int result1 = num1 << 1;
    // int result2 = result1 << 2;
    // int result3 = result2 >> 3;

    // printf("%d %d %d\n\n", result1, result2, result3);


    // 100page question
    // 01
    int num1, negnum;
    printf("Type the integer number : ");
    scanf("%d", &num1);
    negnum = ~num1 + 1;
    printf("%d의 음수는 %d입니다\n\n", num1, negnum);

    // 02
    int num2 = 3;
    num2 = num2 << 3;
    num2 = num2 >> 2;
    printf("%d\n\n", num2);


    return 0;
}