#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    srand(time(0));
    int maxarr[3][5];
    int x,y; // 2차원 배열 순서 찾는 변수
    int max; // 최대값 저장 변수
    for(x=0;x<3;x++)
    {
        for(y=0;y<5;y++)
        {
            maxarr[x][y] = rand() % 100 + 1;
        }
    }
    for(x=0;x<3;x++)
    {
        printf("%d행 배열 : ", x+1);
        for(y=0;y<5;y++)
        {
            printf(" %d", maxarr[x][y]);
        }
        printf("\n");
    }

    for(x=0;x<3;x++)
    {
        max = maxarr[x][0];
        for(y=1;y<5;y++)
        {
            if(max < maxarr[x][y])
            {
                max = maxarr[x][y];
            }
        }
        printf("%d행의 최대값은 %d 입니다\n", x+1, max);
    }



    return 0;
}