#include <stdio.h>

int main(void)
{
    // 01
    int floor = 0, star = 5, starnum = 0;
    while(floor < 5)
    {
        while(star > starnum)
        {
            printf("*");
            star--;
        }
        star = 5;
        starnum++;
        floor++;
        printf("\n");
    }

    // 02
    int floor2 = 1, star2 = 0, starnum2 = 1, space = 5;
    while(floor2 <= 5)
    {
        while(space > floor2)
        {
            printf(" ");
            space--;
        }
        while(star2 < starnum2)
        {
            printf("*");
            star2++;
        }
        space = 5;
        star2 = 0;
        starnum2 = floor2 * 2 + 1;
        floor2++;
        printf("\n");
    }

    // 03
    int floor3 = 1, star3 = 0, starnum3 = 1, space3 = 5;
    while(floor3 <= 5)
    {
        while(space3 > floor3)
        {
            printf(" ");
            space3--;
        }
        while(star3 < starnum3)
        {
            printf("*");
            star3++;
        }
        space3 = 5;
        star3 = 0;
        starnum3 = floor3 * 2 + 1;
        floor3++;
        printf("\n");
        if(floor3 == 6)
        {   
            floor3 -= 3;
            starnum3 -= 4;
            space3 = 4;
            while(floor3 >= 0)
            {
                while(space3 > floor3)
                {
                    printf(" ");
                    space3--;
                }
                while(star3 < starnum3)
                {
                    printf("*");
                    star3++;
                }
                space3 = 4;
                star3 = 0;
                floor3--;
                starnum3 = floor3 * 2 + 1;
                printf("\n");
            }
            if(floor3 < 0)
            {
                break;
            }
        }
    }

    // 04
    int star4 = 1, star4num = 1, space4 = 4;
    for(int num1 = 4; num1 >= 0; num1--)
    {
        star4num = num1 * 2 + 1;
        while(space4 > num1)
        {
            printf(" ");
            space4--;
        }
        while(star4 <= star4num)
        {
            printf("*");
            star4++;
        }
        star4 = 1;
        space4 = 4;
        printf("\n");
    }
    int star5 = 1, star5num = 1, space5 = 3;
    for(int num2 = 1; num2 <= 4; num2++)
    {
        star5num = num2 * 2 + 1;
        while(space5 >= num2)
        {
            printf(" ");
            space5--;
        }
        while(star5 <= star5num)
        {
            printf("*");
            star5++;
        }
        star5 = 1;
        space5 = 3;
        printf("\n");
    }


    return 0;
}