#include <stdio.h>
double FindPower(int,int);

int main(void)
{
    int num1, num2;
    double result1;
    printf("a,b에 들어갈 두개의 정수를 입력하세요 순서대로 a의 b승: ");
    scanf("%d %d", &num1, &num2);
    result1 = FindPower(num1, num2);
    printf("%d의 %d승은 %f 입니다\n\n", num1, num2, result1);
    printf("%d의 %d승은 %f 입니다\n\n", num1, num2, FindPower(num1, num2));
    return 0;
}

double FindPower(int m,int n)
{   
    double result = 1;
    if(m == 0)
    {
        result = 0;
    }
    else
    {
        if(n > 0)
        {
            for(int i = 1; i <= n; i++)
            {
                result *= m;
            }
        }
        else if(n == 0)
        {
            result = 1;
        }
        else
        {
            for(int i = 0; i > n; i--)
            {
                result *= (1/(double)m);
            }
        }   
    }
    return result;
}