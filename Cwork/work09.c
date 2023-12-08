#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(void)
{
    int arr[10], i, num, max = 0;

    for(i = 0; i < 10; i++)
    {
        srand(time(NULL));
        num = rand() % 100 + 1;
        arr[i] = num;
        if(max < arr[i])
        {
            max = arr[i];
        }
    }
    printf("가장 큰 값은 %d입니다\n\n", max);

    return 0;
}