#include <stdio.h>

int main(void)
{

    // int num1, num2, num3;
    // printf("Type the three integer number : ");
    // scanf("%d %o %x", &num1, &num2, &num3);
    // printf("입력된 정수 10진수 출력 : \n");
    // printf("%d %d %d\n\n", num1, num2, num3);

    float num1;
    double num2;
    long double num3;
    printf("Type the real number(e-notation) : ");
    scanf("%f", &num1);
    printf("Typed real number : %f \n", num1);

    printf("Type the real number(e-notation) : ");
    scanf("%lf", &num2);
    printf("Typed real number : %f \n", num2);

    printf("Type the real number(e-notation) : ");
    scanf("%Lf", &num3);
    printf("Typed real number : %Lf \n", num3);


    return 0;
}