#include <stdio.h>

int main(void)
{
    // // 01
    // int num1;
    // int i = 1;
    // printf("Type the positive integer number : ");
    // scanf("%d", &num1);
    // while(i <= num1)
    // {
    //     printf("Hello World!\n");
    //     i++;
    // }

    // // 02
    // int num2, cal1;
    // int count = 1;
    // printf("Type the positive integer number : ");
    // scanf("%d", &num2);
    // while(count <= num2)
    // {
    //     cal1 = 3 * count;
    //     printf("%d\n", cal1);
    //     count++;
    // }

    // 03
    // int num3 = 1, sum1 = 0;
    // while(num3 != 0)
    // {
    //     printf("Type the integer number (type 0 is exit): ");
    //     scanf("%d", &num3);
    //     sum1 += num3;
    // }
    // printf("모든 값의 합은 %d 입니다.\n\n", sum1);

    // 04
    // int num4, count2 = 9;
    // printf("원하는 구구단 단수는? : ");
    // scanf("%d", &num4);
    // while(count2 > 0)
    // {
    //     printf("%d x %d = %d\n", num4, count2, num4*count2);
    //     count2--;
    // }

    // 05
    // int num5, num6, x, y = 0;
    // printf("몇개의 정수를 입력하시겠습니까? : ");
    // scanf("%d", &num5);
    // x = num5;
    // while(x > 0)
    // {
    //     printf("정수를 입력해주세요 : ");
    //     scanf("%d", &num6);
    //     y += num6;
    //     x--;
    // }
    // printf("입력한 값의 평균 : %f\n", ((double)y/num5));


    // while 중첩
    // 01
    // int num, sum = 0, i = 0;
    // while (i < 5)
    // {
    //     printf("1 이상의 5개의 정수를 입력해주세요 : ");
    //     scanf("%d", &num);
    //     while(num == 0)
    //     {
    //         printf("1 이상의 정수만 입력해주세요 : ");
    //         scanf("%d", &num);
    //     }
    //     sum += num;
    //     i++;
    // }
    // printf("모든 수의 합은 : %d\n\n", sum);

    // 02
    // int floor = 0, i = 0, x = 0;
    // while(floor < 5)
    // {
    //     while(i < x)
    //     {
    //         printf("o");
    //         i++;           
    //     }
    //     printf("*\n");
    //     floor++;
    //     x++;
    //     i = 0;
    // }


    // do while
    // int total = 0, num = 1;
    // do
    // {
    //     printf("Type the integer number (type 0 is quit) : ");
    //     scanf("%d", &num);
    //     total += num;
    // }while(num != 0);
    // printf("Sum all number : %d\n", total);

    // do while question
    // 01-1
    // while(num != 0)
    // {
    //     printf("Type the integer number (type 0 is quit) : ");
    //     scanf("%d", &num);
    //     total += num;
    // }
    // printf("Sum all number : %d\n", total);

    // 02
    // int total = 0, num = 0;
    // do
    // {   
    //     total += num;
    //     num += 2;
    // }while(num <= 100);
    // printf("%d", total);

    // 03
    // int cur = 2, is = 0;

    // do
    // {
    //     is = 1;
    //     do
    //     {
    //         printf("%d x %d = %d\n", cur, is, cur*is);
    //         is++;
    //     }while(is <= 9);
    //     cur++;
    // }while(cur<=9);


    // 반복문 탈출
    // int sum = 0, num = 0;
    // while(1)
    // {
    //     sum += num;
    //     if(sum>5000)
    //     {
    //         break;
    //     }
    //     num++;
    // }
    // printf("sum: %d\n", sum);
    // printf("num: %d\n", num);

    // 반복문 continue
    // int num;
    // printf("start! ");
    // for(num=1; num<20; num++)
    // {
    //     if(num%2 == 0 || num % 3 == 0)
    //     {
    //         continue;
    //         printf("%d ", num);
    //     }
    //     printf("%d ", num);
    // }
    // printf("end! \n");

    // continue, break 활용 문제
    // 01
    // for(int num1 = 2; num1 <= 9; num1++)
    // {
    //     if(num1 % 2 != 0) // 이게 두번째 포문 밖에 있어야 칸이 한칸씩 띄워짐
    //     {
    //         continue;
    //     }
    //     for(int num2 = 1; num2 <= 9; num2++)
    //     {
    //         if(num1 < num2) // 어차피 해당 단수 만큼 진행하는거니까 한줄로 요약 가능
    //             break;
    //         printf("%d x %d = %d\n", num1, num2, (num1*num2));
    //     }
    //     printf("\n");
    // }

    // 02
    // int a, b;
    // int sum1 = 0;
    // for(a = 1; a <= 9; a++)
    // {
    //     for(b = 1; b <= 9; b++)
    //     {
    //         if(a + b == 9)
    //         {
    //             printf("%d%d + %d%d = %d\n", a, b, b, a, 99);
    //         }
    //     }
    // }

    // page200 switch문 변경
    int n;
    printf("0이상의 정수 입력하세요 : ");
    scanf("%d", &n);
    switch(n/10)
    {
        case 0:
            printf("0이상 10미만");
            break;
        case 1:
            printf("10이상 20미만");
            break;
        case 2:
            printf("20이상 30미만");
            break;
        default:
            pritnf("30이상입니다");

    }





    return 0;
}