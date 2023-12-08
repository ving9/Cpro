#include <stdio.h>
void Draw(int num)
{
    int space = num - 1;
    for(int i = 0; i < num; i++)
    {
        int star = i*2+1;
        int drawstar = 0;
        int drawspace = 0;
        while(drawspace < space)
        {
            printf(" ");
            drawspace++;
        }
        while(drawstar < star)
        {
            printf("*");
            drawstar++;
        }
        space--;
        printf("\n");
    }
}


int main(void)
{
    int input;
    while(1)
    {
        printf("양의 정수 입력: ");
        scanf("%d", &input);
        if(input == 0)
            break;
        Draw(input);
        
    }
    return 0;
}