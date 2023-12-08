#include <stdio.h>
int HighNum(int num1, int num2, int num3);
int LowNum(int num1, int num2, int num3);
void Fibonacci(int num);
// void SimpleFucn(void);

int main(void)
{
    // p.221 문제
    // 01
    int num1, num2, num3, maxNum, minNum;
    printf("3개의 정수를 입력해 주십시오 : ");
    scanf("%d %d %d", &num1, &num2, &num3);
    maxNum = HighNum(num1, num2, num3);
    minNum = LowNum(num1, num2, num3);
    printf("셋 중에 가장 큰 수는 %d 이고 가장 작은 수는 %d 입니다 \n\n", maxNum, minNum);
    
    // 03
    // int input_;
    // printf("피보나치 수열을 몇번까지 보실래요? : ");
    // scanf("%d", &input_);
    // Fibonacci(input_);





    // 반복문 안의 지역변수
    // int cnt;
    // for(cnt = 0; cnt < 3; cnt++)
    // {
    //     int num = 0;
    //     num++;
    //     printf("%d번째 반복, 지역변수 num은 %d. \n", cnt+1, num);
    // }
    // if(cnt == 3)
    // {
    //     int num = 7;
    //     num++;
    //     printf("if문 내에 존재하는 지역변수 num은 %d \n", num);
    // }

    // static 변수
    // int i;
    // for(i=0; i<3; i++)
    //     SimpleFucn();

    // return 0;


}

// void SimpleFucn(void)
// {
//     static int num1; // 함수를 한번 탈출해도 초기화 되지 않음 (기본으로 0으로 초기화)
//     int num2 = 0;
//     num1++;
//     num2++;
//     printf("static : %d, local : %d \n", num1, num2);
// }


int HighNum(int num1, int num2, int num3)
{
    if(num1>num2)
        return (num1>num3) ? num1 : num3;
    else
        return (num2>num3) ? num2 : num3;
}
int LowNum(int num1, int num2, int num3)
{
    if(num1<num2)
        return (num1<num3) ? num1 : num3;
    else
        return (num2<num3) ? num2 : num3;

}

void Fibonacci(int num)
{
    int num1 = 0, num2 = 1, sum = 0;
    for(int i = 0; i < num; i++)
    {
        if(i == 0)
        {
            printf(" %d", sum);
        }
        else if (i == 1)
        {
            printf(" %d", num2);
        }
        else
        {
            sum = num1 + num2;
            num1 = num2;
            num2 = sum;
            printf(" %d", sum);
        }
    }
    return 0;
}