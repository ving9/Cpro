#include <stdio.h>

int main()
{
    // int villa[4][2];
    // int popu, i, j;

    // // 가구별 거주인원 입력 받기
    // for(i = 0; i < 4; i++)
    // {
    //     for(j = 0; j < 2; j++)
    //     {
    //         printf("%d floor %d room people : ",i+1, j+1);
    //         scanf("%d", &villa[i][j]);
    //     }
    // }
    // // 빌라의 층별 인구수 출력
    // for(i = 0; i < 4; i++)
    // {
    //     popu = 0;
    //     popu += villa[i][0];
    //     popu += villa[i][1];
    //     printf("%d층 인구수 : %d\n\n",i+1, popu);
    // }


    // 348p 문제
    // 문제 1
    // int mulTable[3][9];
    // int x,y;
    // for(x=0;x<3;x++)
    // {
    //     for(y=0;y<9;y++)
    //     {
    //         mulTable[x][y] = (x+2) * (y+1);
    //     }
    // }
    // for(x=0;x<3;x++)
    // {
    //     for(y=0;y<9;y++)
    //         printf("%3d ", mulTable[x][y]);
    //     printf("\n");
    // }

    // 문제 2
    // int table_01[2][4];
    // int table_02[4][2];
    // int x,y;
    // for(x=0;x<2;x++)
    // {
    //     for(y=0;y<4;y++)
    //     {
    //         table_01[x][y] = (x*4) + (y+1);
    //         table_02[y][x] = table_01[x][y];
    //     }
    // }
    // for(x=0;x<2;x++)
    // {
    //     for(y=0;y<4;y++)
    //         printf("%d ", table_01[x][y]);
    //     printf("\n");
    // }
    // for(x=0;x<4;x++)
    // {
    //     for(y=0;y<2;y++)
    //         printf("%d ", table_02[x][y]);
    //     printf("\n");
    // }

    // 문제03
    // int reportTable[5][5] = {0,}, x, y;
    // char* label[5] = {"국어","영어","수학","국사","총점"};
    // char* label2[5] = {"철희","철수","영희","영수","과목별 총점"};
    // for(x = 0; x < 4; x++)
    // {  
    //     for(y = 0; y < 4; y++)
    //     {
    //         printf("%s의 %s 점수 :", label2[x], label[y]);
    //         scanf("%d", &reportTable[x][y]);
    //         reportTable[x][4] += reportTable[x][y]; // 각 행의 마지막에 각 학생별 점수의 합을 입력하는 과정
    //         reportTable[4][y] += reportTable[x][y]; // 각 열의 마지막에 각 과목별 합을 입력하는 과정
    //     }
    //     reportTable[4][4] += reportTable[x][4]; // 제일 끝칸에 모든 점수의 합을 입력하는 과정;
    // }
    // for(x = 0; x < 5; x++)
    // {
    //     for(y = 0; y < 5; y++)
    //     {
    //         printf(" %3d", reportTable[x][y]);
    //     }
    //     printf("\n");
    // }

    int mean = 0, i, j;
    int record[3][3][2] = 
    {
        {
            {70, 80},
            {94, 90},
            {70, 85}
        },
        {
            {83, 90},
            {95, 60},
            {90, 82}
        },
        {
            {98, 89},
            {99, 94},
            {91, 87}
        }
    };
    for(i=0; i<3; i++)
    {
        for(j=0; j<2; j++)
        {
            mean += record[0][i][j];
        }
    }
    printf("A 학급 전체 평균: %.1f \n", (double)mean/6);
    mean = 0;
    for(i=0; i<3; i++)
    {
        for(j=0; j<2; j++)
        {
            mean += record[1][i][j];
        }
    }
    printf("B 학급 전체 평균: %.1f \n", (double)mean/6);
    mean = 0;
    for(i=0; i<3; i++)
    {
        for(j=0; j<2; j++)
        {
            mean += record[2][i][j];
        }
    }
    printf("C 학급 전체 평균: %.1f \n", (double)mean/6);
    






    return 0;
}