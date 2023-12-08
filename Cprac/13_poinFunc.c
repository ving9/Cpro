#include <stdio.h>
void ShowAray(int*, int);
int SquareByValue(int num);
int SquareByReference(int* num);
void Swap3(int* num1,int* num2,int* num3);

void ShowData(const int* ptr);

int main(void)
{
    // int arr1[3] = {1,2,3};
    // int arr2[5] = {4,5,6,7,8};
    // ShowAray(arr1, sizeof(arr1)/sizeof(int));
    // ShowAray(arr2, sizeof(arr2)/sizeof(int));

    // p320 문제
    // 01
    // int num1;
    // printf("제곱할 정수를 입력해주세요 : ");
    // scanf("%d", &num1);
    // printf("%d\n", SquareByValue(num1));
    // printf("%d\n", num1);
    // printf("%d\n", SquareByReference(&num1));
    // printf("%d\n", num1);

    // 02
    // int num1 = 1, num2 = 5, num3 = 10;
    // printf("%d %d %d\n\n", num1, num2, num3);
    // Swap3(&num1, &num2, &num3);
    // printf("1은 10으로 바뀜 5는 1로 바뀜 10은 5로 바뀜\n\n");
    // printf("%d %d %d\n\n", num1, num2, num3);

    // p324 문제2
    int num = 10;
    int* ptr=&num;
    ShowData(ptr);



    return 0;
}

void ShowAray(int* param, int len)
{
    int i;
    for(i=0; i<len; i++)
    {
        printf(" %d", param[i]);
    }
    printf("\n");
}

int SquareByValue(int num)
{
    num *= num;
    return num;
}

int SquareByReference(int* num)
{
    *num *= *num;
    return *num;
}

void Swap3(int* num1,int* num2,int* num3)
{
    int temp;
    temp = *num1;
    *num1 = *num3;
    *num3 = *num2;
    *num2 = temp; 
}

void ShowData(const int* ptr)
{
    int* rptr = ptr;
    printf("%d \n", *rptr);
    *rptr = 20;
}