#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 배열의 값을 무작위로 재정렬하기
void Shuffle(int arr[], int len)
{
    srand(time(0));
    int temp, i;
    int event = rand() % 3;
    if(event== 0){ // 가운데 항으로 오면서 배열의 첫항과 마지막항을 바꾸는 것
        if(len % 2 == 0){
            for(i=0;i<len/2;i++){
                temp = arr[i];
                arr[i] = arr[(len-1)-i];
                arr[(len-1)-i] = temp;
            }
        }
        else{
            for(i=0;i<len/2 + 1;i++){
                if(i == len/2){
                    temp = arr[i];
                    arr[i] = arr[0];
                    arr[0] = temp;
                }
                temp = arr[i];
                arr[i] = arr[(len-1)-i];
                arr[(len-1)-i] = temp;
            }
        }
    }
    else if(event == 1){ // 배열의 첫항과 다음항을 계속 바꾸면서 뒤로 가는 것
        for(i=0;i<len-1;i++){   
            temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
        }
    }
    else if(event == 2){ // 배열의 마지막 항과 마지막 이전항을 바꾸면서 앞으로 가는 것
        for(i=0;i<len-1;i++){
            temp = arr[len-1-i];
            arr[len-1-i] = arr[len-2-i];
            arr[len-2-i] = temp;
        }
    }

}

int main(void) // 흠... 이것 뿐인가
{
    srand(time(0));
    int i;
    int arr01[10];
    int len_arr01 = sizeof(arr01)/sizeof(int);

    for(i=0;i< len_arr01;i++)
        arr01[i] = rand() % 100 + 1;

    for(i=0;i< len_arr01;i++)
        printf("%3d", arr01[i]);
    printf("\n");
    Shuffle(arr01, len_arr01);
    for(i=0;i< len_arr01;i++)
        printf("%3d", arr01[i]);
    printf("\n");

    

    return 0;
}

    

