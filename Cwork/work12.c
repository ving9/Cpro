#include <stdio.h>
void Pattern(int* arr,int len);

int main(void)
{
    int Arr1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int Arr2[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int LenArr1 = sizeof(Arr1)/sizeof(int);
    int LenArr2 = sizeof(Arr2)/sizeof(int);
    Pattern(Arr1, LenArr1);
    Pattern(Arr2, LenArr2);
    for(int i = 0; i < LenArr1; i++)
    {
        printf("%d ", Arr1[i]);
    }
    printf("\n");
    for(int i = 0; i < LenArr2; i++)
    {
        printf("%d ", Arr2[i]);
    }


    return 0;
}

void Pattern(int* arr,int len)
{
    if(len % 2 == 0)
    {
        arr[(len/2)-1] = 1;
        arr[len/2] = 1;
    }
    else
    {
        arr[(len/2)] = 1;
    }
}