#include <stdio.h>
double Max(double*, int);

int main(void)
{

    double aRR[] = {3.14, 4, 5, 10.9, 85, 75.2, 3.4, 7.1, 0.12, 7.55};
    int lenaRR = sizeof(aRR)/sizeof(double);
    double result;
    result = Max(aRR, lenaRR);
    printf("가장 큰 실수는 %.3f 입니다\n\n", result);
    printf("가장 큰 실수는 %.3f 입니다\n\n", Max(aRR, lenaRR));
    return 0;
}

double Max(double* arr, int num)
{
    double max;
    int cnt;
    max = arr[0];
    for(cnt = 1; cnt < num; cnt++)
    {
        if(max < arr[cnt])
        {
            max = arr[cnt];
        }
    }
    return max;
}