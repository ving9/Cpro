#include <stdio.h>

double Max(double* arr, int len);

int main(void)
{
    double num[5];
    int lenarr = sizeof(num)/sizeof(double);
    double result;
    printf("5개의 실수를 입력하세요 : ");
    scanf("%lf %lf %lf %lf %lf", &num[0], &num[1], &num[2], &num[3], &num[4]);
    result = Max(num, lenarr);
    printf("5개 실수 중에 가장 큰 수는 %f 입니다!!\n\n", result);
    printf("5개 실수 중에 가장 큰 수는 %f 입니다!!\n\n", Max(num, lenarr));
    return 0;
}

double Max(double* arr, int len)
{
    double max = arr[0];
    int cnt = 1;
    for(;cnt<len;cnt++)
    {
        if(max<arr[cnt])
            max = arr[cnt];
    }
    
    return max;
}