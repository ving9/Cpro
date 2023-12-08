#include <stdio.h>

int main(void)
{
    // 문제 01 (1부터 10까지 출력하기)
    int num1 = 1;
    while(num1 <= 10)
    {
        printf("%d\n", num1);
        num1++;
    }

    // 문제 02 (10부터 1까지 출력)
    int num2 = 10;
    while(num2 >= 1)
    {
        printf("%d\n", num2);
        num2--;
    }

    // 문제 03 (1부터 100까지 합구하기)
    int num3 = 1, sum = 0;
    while(num3 <= 100)
    {
        sum += num3;
        num3++;
    }
    printf("%d\n", sum);

    // 문제 04 (1부터 100까지 짝수의 합 구하기)
    int num4 = 2, sum2 = 0;
    while(num4 <= 100)
    {
        sum2 += num4;
        num4 += 2;
    }
    printf("%d\n", sum2);

    // 문제 05 (1부터 100까지 홀수면 더하고 짝수면 빼기)
    int num5 = 1, sum3 = 0;
    while(num5 <= 100)
    {
        sum3 += num5;
        num5 += 2;
    }
    num5 = 2;
    while(num5 <= 100)
    {
        sum3 -= num5;
        num5 += 2;
    }
    printf("%d\n", sum3);

    // 문제 06 (5의 계승을 구하시오)
    int num6 = 1, sum4 = 1;
    while(num6 <= 5)
    {
        sum4 *= num6;
        num6 += 1;
    }
    printf("%d\n", sum4);

    // 문제 07 (10의 약수를 구하시오)
    int result7[256], num7 = 10, array = 0;
    for(int i = 1; i < 10;i++)
    {
        if(num7 % i == 0)
        {
            result7[array] = i;
            printf("%d\n", result7[array]);
            array += 1; 
        }
    }
    
    // 문제 08 (공약수 구하기)
    int result8[256], num8 = 1, array2 = 0;

    for(; num8 < 18; num8++)
    {
        if(18 % num8 == 0 && 24 % num8 == 0)
        {
            result8[array2] = num8;
            printf("%d\n", result8[array2]);
            array2++;
        }
    }


    return 0;
}