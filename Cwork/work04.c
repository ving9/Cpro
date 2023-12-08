#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    int num = 1; // 지나갈 턴
    int goldnum; // 금붕의 쌍의 수 
    int goldsum = 2; // 금붕어 총 합
    int goldcount; // 금붕어 각 쌍을 세는 역할
    
    while(goldsum <= 1000)
    {
        srand(time(NULL));
        int goldprob = (rand() % 5 + 1) * 2; // 한턴에 낳는 물고기 수 
        double golddie = (rand() % 4 + 2) * 0.1; // 한턴에 죽는 물고기 확률
        goldnum = goldsum / 2; // 매턴 시작할때 금붕어 쌍이 몇쌍인지 저장
        int goldcount = 1; // 각 쌍마다 돌아갈 마리수 체크 초기화
        if(num == 1)
        {
            goldsum = goldnum * goldprob;
        }
        else
        {
            while(goldcount <= goldnum) // 각 쌍마다 낳는 마리수가 다름
            {
                goldsum += (1 * goldprob);
                goldcount++;
            }
            goldnum = goldsum / 2; // 각 턴마다 다 낳고나서 죽는걸로 계산하기 위해
            goldsum -= (goldnum * golddie) * 2; // 2턴째부터 죽는 금붕어 쌍 계산
        }
        printf("%d턴 째 금붕어 마리 수 : %d\n", num, goldsum);
        num++;
    }
    printf("금붕어 %d 마리, 진행 턴 수 : %d\n\n", goldsum, (num-1));
    

    return 0;
}