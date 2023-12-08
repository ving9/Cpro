#include <stdio.h>

int main(void)
{
    // int result;
    // int num1, num2;

    // printf("decimal first: ");
    // scanf("%d", &num1);
    // printf("decimal second: ");
    // scanf("%d", &num2);
    // result = num1 + num2;

    // printf("%d + %d = %d \n\n", num1, num2, result);


    // scanf 문제
    // 01
    int num1, num2, sub, mul;
    printf("Type the two decimals : ");
    scanf("%d %d", &num1, &num2);
    sub = num1 - num2;
    mul = num1 * num2;
    printf("%d - %d = %d\n", num1, num2, sub);
    printf("%d X %d = %d\n\n", num1, num2, mul);

    // 02
    int num3, num4, num5, result1;
    printf("Type the three decimals : ");
    scanf("%d %d %d", &num3, &num4, &num5);
    result1 = num3*num4+num5;
    printf("%d x %d + %d = %d\n\n", num3, num4, num5, result1);

    // 03
    int num6, square;
    printf("Type the one decimal : ");
    scanf("%d", &num6);
    square = num6*num6;
    printf("The sqaure of %d is %d!\n\n", num6, square);

    // 04
    int num7, num8, quotient, remainder;
    printf("Type the two decimals : ");
    scanf("%d %d", &num7, &num8);
    quotient = num7 / num8;
    remainder = num7 % num8;
    printf("The quotient of %d divided by %d is %d and the remainder is %d! \n\n", num7, num8,
    quotient, remainder);

    // 05
    int num9, num10, num11, result2;
    printf("Type the three decimals : ");
    scanf("%d %d %d", &num9, &num10, &num11);
    result2 = (num9 - num10) * (num10 + num11) * (num11 % num9);
    printf("The result of calculation is %d\n\n", result2);

    


    return 0;
}