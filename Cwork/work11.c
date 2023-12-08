#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void Sort(int* arr, int len);


int main(void)
{  
    srand(time(NULL));
    int cnt;
    int arr01[10];
    int lenarr = sizeof(arr01)/sizeof(int);
    for(cnt = 0; cnt < lenarr; cnt++)
    {
        arr01[cnt] = rand() % 100 + 1;
        printf("%d ", arr01[cnt]);
    }

    Sort(arr01, lenarr);
    printf("\n");

    for(cnt = 0; cnt < lenarr; cnt++)
    {   
        printf("%d ", arr01[cnt]);
    }

    return 0;
}


void Sort(int* arr, int len)
{
    int min = arr[0], cnt1, cnt2;

    for(cnt1 = 0; cnt1 < len-1; cnt1++)  // 마지막 두개 남을때까지만 검사하면 되니까...
    {
        for(cnt2 = (cnt1+1); cnt2 < len; cnt2++)
        {
            if(min>arr[cnt2])
            {
                min = arr[cnt2];
                arr[cnt2] = arr[cnt1]; // 어차피 이렇게 해도 상관없는게 한번 바뀌고 나면 그 다음수부터 비교하므로 걱정없다...
                arr[cnt1] = min;
            }
        }
        min = arr[cnt1+1]; // 매번 비교하는 수 초기화 해줘야함
    }
}

