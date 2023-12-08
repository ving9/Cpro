#include <stdio.h>
int Power(int num)
{   
    if (num == 0)
    {
        return 1;
    }
    return 2 * Power(num-1);
}

int main(void)
{
    // // 도전 1
    // int decimal;
    // printf("정수를 입력하세요 : ");
    // scanf("%d", &decimal);
    // printf("%d의 16진수 표현은 %x 입니다\n\n", decimal, decimal);

    // 도전 2
    int num1, num2;
    printf("두 정수를 입력하세요 : ");
    scanf("%d %d", &num1, &num2);
    if(num1 > num2) // 받은 두 수중에 더 작은 수를 체크하는 조건문
    {
        for(;num2 <= num1;num2++)  // 받은 수 중에 더 큰 수가 반복문을 벗어나는 기준이 되고 더 작은 수가 시작점이 된다.
        {
            for(int i = 1; i < 10; i++)
            {
                printf("%d x %d = %d\n", num2, i, num2*i);
            }
        }
    }
    else
    {
        for(;num1 <= num2;num1++)
        {
            for(int i = 1; i < 10; i++)
            {
                printf("%d x %d = %d\n", num1, i, num1*i);
            }
        }
    }


    // // 도전 3
    // int num1, num2, gcd = 0;
    // printf("두개의 정수를 입력해주세요 : ");
    // scanf("%d %d", &num1, &num2);
    // if(num1 > num2)
    //     for(int i = 1; i <= num2; i++)
    //     {
    //         if(num1 % i == 0 && num2 % i == 0)
    //         {
    //             gcd = i;
    //         }
    //     }
    // else if(num2 > num1)
    // {
    //     for(int i = 1; i <= num1; i++)
    //     {
    //         if(num1 % i == 0 && num2 % i == 0)
    //         {
    //             gcd = i;
    //         }
    //     }
    // }
    // else
    // {
    //     printf("정신좀차리세요");
    // }
    // printf("%d와 %d의 최대 공약수는 %d 입니다\n\n", num1, num2, gcd);

    // 도전4
    // int money = 5000, cream = 500, shrimp = 700, cola = 400;
    // int c_num, s_num, co_num;
    // printf("현재 당신이 소유하고 있는 금액 : %d\n", money);
    // for(c_num = 1;cream * c_num  < money;c_num++)
    // {
    //     for(s_num = 1;shrimp * s_num <= money - (c_num*cream);s_num++)
    //     {
    //         for(co_num = 1;cola * co_num  <= money - (c_num*cream + s_num*shrimp);co_num++)
    //         {
    //             if(cream * c_num + shrimp * s_num + cola * co_num == money)
    //                 printf("크림빵 %d개 새우깡 %d개 콜라 %d개\n", c_num, s_num, co_num);
    //         }
    //     }
    // }
    // printf("어떻게 구입하시겠습니까?\n\n");

    // 도전 5
    // int total_print = 20; // 뽑아내고 싶은 소수의 갯수
    // int count = 0; // 돌아갈 횟수 체크 (소수를 찾으면 +1 되야함)
    // int target = 2; // 하나씩 올라가면서 소수인지 판단할 변수
    // int cnt; // 소수가 아닐때 +1이 되어서 소수가 아니라는 신호를 주는 변수

    // while (count != total_print) { // 뽑아내고 싶은 소수가 될때까지 돌리겠다
    //     cnt = 0; // 소수 판단 변수 초기화
    //     for (int i=2; i<=target/2; i++) {  // 소수가 아닌걸 골라내는 for문 (어차피 약수는 대상 수의 절반을 초과할 수 없으므로 나누기 2를 해서 연산을 줄인다)
    //         if (target % i == 0) { // 타겟이 i부터 target/2까지 가면서 나눠지는 순간 소수가 아니게 된다
    //             cnt += 1;   // 소수가 아니니까 cnt에 변경을 줘서 신호를 준다
    //         }
    //     }
    //     if (cnt == 0) { // for문에서 살아남은 target은 소수로 판별됨!
    //         printf("%d ", target);
    //         count += 1;  // 소수 발견했으니까 돌아갈 횟수 +1
    //     }
    //     target += 1;  // 소수인지 확인하기 위한 다음숫자
    // }
    // printf("\n");

    // 도전 6
    // int input_, hour, minute, second;
    // printf("시간초를 입력해주세요 (정수) : ");
    // scanf("%d", &input_);

    // hour = input_ / 3600;
    // minute = (input_ % 3600) / 60;
    // second = input_ % 60;

    // printf("입력한 초 : %d\n", input_);
    // printf("h:%d m:%d s:%d\n\n", hour, minute, second);

    // // 도전 7
    // int input_1;
    // int two = 2;
    // int cnt = 0;
    // printf("양의 정수를 입력해주세요 : ");
    // scanf("%d", &input_1);

    // while(two <= input_1) // 2의 지수를 구하는 문제이므로 입력값이 될때까지 2를 곱하기만 하면 된다
    // {
    //     cnt++; // 몇번 곱해졌는지 (지수) 구하기 위한 변수
    //     two *= 2;
    // }

    // printf("입력된 정수 : %d\n", input_1);
    // printf("상수까지의 2의 지수 최대값은 : %d\n\n", cnt);


    // 도전 8
    // int input_2;
    // printf("양의 정수를 입력해주세요 : ");
    // scanf("%d", &input_2);
    // printf("정수 입력 %d\n", input_2);
    // printf("2의 %d승은 %d\n\n", input_2, Power(input_2));

    return 0;
}