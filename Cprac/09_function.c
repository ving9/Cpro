#include <stdio.h>

// int Add(int num1, int num2)
// {
//     int result = num1 + num2;
//     return result;
// }
// void ShowAddResult(int num)
// {
//     printf("Result of add : %d \n", num);
// }
// int ReadNum(void)
// {
//     int num;
//     scanf("%d", &num);
//     return num;
// }
// void HowToUseThisProg(void)
// {
//     printf("두 개의 정수를 입력하시면 덧셈 결과가 출력됩니다.\n");
//     printf("자! 그러면 두 개의 정수를 입력하세요.\n");
// }

int AbsoCompare(int num1, int num2); // 절대값이 큰 정수 반환
int GetAbsoValue(int num); // 전달인자의 절대값을 반환

int main(void)
{
    // // printf 함수도 반환값이 있다!
    // int num1, num2;
    // num1 = printf("12345\n");
    // num2 = printf("I love C lang\n");
    // printf("%d %d\n\n", num1, num2);

    // Add 함수 만들어서 써보기
    // int result;
    // result = Add(8, 11);
    // printf("The result of add : %d\n", result);
    // result = Add(10, 9);
    // printf("The result of add : %d\n", result);

    // int result, num1, num2;
    // HowToUseThisProg();
    // num1 = ReadNum();
    // num2 = ReadNum();
    // result = Add(num1, num2);
    // ShowAddResult(result);

    int num1, num2;
    printf("두 정수의 절대값 비교! 입력하세요 : ");
    scanf("%d %d", &num1, &num2);
    printf("%d 와 %d 중 절대값이 더 큰 정수 : %d\n\n", num1, num2,
     AbsoCompare(num1, num2));

    return 0;
}
int AbsoCompare(int num1, int num2)
{
    if(GetAbsoValue(num1) > GetAbsoValue(num2))
        return num1;
    else
        return num2;
}
int GetAbsoValue(int num)
{
    if(num < 0)
        return num * -1;
    else
        return num;
}