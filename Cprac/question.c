#include <stdio.h>
void Swap(int** dp1, int** dp2)
{
    int* temp = *dp1;
    *dp1 = *dp2;
    *dp2 = temp;
}

int main(void)
{
    // int arr[20] = {17,1,2,3,4,5};
    // int* pointer = arr;

    // printf("%ld\n", sizeof(arr));
    // printf("%ld\n\n", sizeof(pointer)); // 64비트 시스템의 64비트 컴파일러라서 주소값이 8바이트에 저장됨

    // printf("%p\n", (void *)arr); 
    // printf("%p\n\n", (void *)pointer); // 이 두개는 사실상 같다

    // printf("%d\n", *(arr+1));
    // printf("%d\n", arr[1]);
    // printf("%d\n", *(pointer+1)); 
    // printf("%d\n\n", pointer[1]);

    // int num1 = 10, num2 = 20, num3 = 30;
    // int* arr2[3] = {&num1, &num2, &num3};
    // printf("%d \n", *arr2[0]);
    // printf("%p \n", arr2[0]);
    // printf("%d \n", *arr2[1]);
    // printf("%p \n", arr2[1]);
    // printf("%d \n", *arr2[2]);
    // printf("%p \n", arr2[2]);

    int num1=10, num2=20, num3=30;
    int* ptr1=&num1;
    int* ptr2=&num2;
    int* ptr3=&num3;
    
    int* ptrArr[] = {ptr1,ptr2,ptr3};
    int** dptr = ptrArr;

    printf("%d %d %d\n", *(ptrArr[0]), *(ptrArr[1]), *(ptrArr[2]));
    printf("%d %d %d\n", *(dptr[0]), *(dptr[1]), *(dptr[2]));
    printf("%p %p %p\n", ptr1, ptr2, ptr3);


    


    return 0;
}

    

