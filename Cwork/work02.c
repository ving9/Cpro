#include <stdio.h>

int main(void)
{
    // 문제 01 두 수 중 큰 수 찾기
    int a1, b1;
    printf("Type the two integer number : ");
    scanf("%d %d", &a1, &b1);
    if(a1 > b1)
    {
        printf("%d\n", a1);
    }
    else
    {
        printf("%d\n", b1);
    }

    // 문제 02 양수 0 음수 판별하기
    int a2;
    printf("Type the integer number : ");
    scanf("%d", &a2);
    if(a2 > 0)
    {
        printf("양수\n");
    }
    else if(a2 < 0)
    {
        printf("음수\n");
    }
    else
    {
        printf("0\n");
    }

    // 문제 03 세 수 중 가장 큰 수 찾기
    int a3, b3, max;
    printf("Type the integer number : ");
    scanf("%d", &max);
    printf("Type the integer number : ");
    scanf("%d", &a3);
    if (a3 > max)
    {
        max = a3;
    }
    printf("Type the integer number : ");
    scanf("%d", &b3);
    if (b3 > max)
    {
        max = b3;
    }
    printf("%d\n\n", max);

    // 문제 04 홀수 짝수 판별
    int a4;
    printf("Type the integer number : ");
    scanf("%d", &a4);
    if(a4 == 0)
    {
        printf("0은 좀 입력하지 마라\n");
    }
    else if(a4 % 2 != 0)
    {
        printf("홀수\n");
    }
    else
    {
        printf("짝수\n");
    }

    // 문제 05 3의 배수 판별
    int a5;
    printf("Type the integer number : ");
    scanf("%d", &a5);
    if(a5 == 0)
    {
        printf("제발 0좀 쓰지마\n");
    }
    else if(a5 % 3 == 0)
    {
        printf("3의 배수입니다!\n");
    }
    else
    {
        printf("3의 배수가 아닙니다\n");
    }
    
    // 문제 06 나이에 따른 입장료
    int a6;
    printf("나이를 양의 정수로 입력하세요 : ");
    scanf("%d", &a6);
    if(a6 >= 60)
    {
        printf("당신의 요금은 2,500원 입니다.\n");
    }
    else if(a6 >= 8)
    {
        printf("당신의 요금은 5,000원 입니다.\n");
    }
    else
    {
        printf("당신의 요금은 0원 입니다.\n");
    }
    
    // 문제 07 3의 배수이면서 5의 배수 판별
    int a7;
    printf("당신의 수가 3과 5의 공배수인지 알려드립니다! : ");
    scanf("%d", &a7);
    if(a7 == 0)
    {
        printf("장난치지 마세요(정색)\n");
    }
    else if(a7 % 3 == 0 && a7 % 5 == 0)
    {
        printf("당신의 수는 3과 5의 공배수가 맞습니다!\n");
    }
    else
    {
        printf("아쉽지만 공배수가 아니네요\n");
    }

    // 문제 08 나이 입장료 문제 2
    int a8;
    printf("당신의 나이를 입력하세요. : ");
    scanf("%d", &a8);
    if(a8 >= 60 || a8 < 8)
    {
        printf("입장료 무료\n");
    }
    else
    {
        printf("당신의 입장료는 5,000원 입니다.\n");
    }


    return 0;
}