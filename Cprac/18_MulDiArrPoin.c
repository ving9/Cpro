#include <stdio.h>
void ShowArr2DStyle(int (*arr)[4], int row);
int SUm2DArr(int arr[][4], int row);

int main(void)
{
    // 다차원 배열과 포인터 

    // int arr2d[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    // printf("%p\n", arr2d);
    // printf("%p\n", arr2d[0]);
    // printf("%d\n", arr2d[0][0]);

    // printf("%p\n", arr2d[1]);
    // printf("%d\n", arr2d[1][0]);

    // printf("%p\n", arr2d[2]);
    // printf("%d\n", arr2d[2][0]);

    // printf("sizeof(arr2d) : %ld \n", sizeof(arr2d));
    // printf("sizeof(arr2d[0]) : %d \n", sizeof(arr2d[0]));
    // printf("sizeof(arr2d[1]) : %d \n", sizeof(arr2d[0]));
    // printf("sizeof(arr2d[2]) : %d \n", sizeof(arr2d[0]));


    // int arr1[3][2];
    // int arr2[2][3];

    // printf("arr1: %p \n", arr1);
    // printf("arr1+1: %p \n", arr1+1);
    // printf("arr1+2: %p \n", arr1+2);

    // printf("arr2: %p \n", arr2);
    // printf("arr2+1: %p \n", arr2+1);


    // int num1=10, num2=20, num3=30, num4=40;
    // int arr2d[2][4] = {1,2,3,4,5,6,7,8};
    // int i, j;
    // int* whoA[4] = {&num1, &num2, &num3, &num4};
    // int (*whoB)[4] = arr2d;
    // printf("%d %d %d %d \n", *whoA[0], *whoA[1], *whoA[2], *whoA[3]);
    // for(i=0; i<2; i++)
    // {
    //     for(j=0; j<4; j++)
    //     {
    //         printf("%d ", whoB[i][j]);
    //     }
    //     printf("\n");
    // }

    // p384 예제
    // int arr1[2][4] = {1, 2, 3, 4, 5, 6, 7, 8};
    // int arr2[3][4] = {1, 1, 1, 1, 3, 3, 3, 3, 5, 5, 5, 5};

    // ShowArr2DStyle(arr1, sizeof(arr1)/sizeof(arr1[0]));
    // ShowArr2DStyle(arr2, sizeof(arr2)/sizeof(arr2[0]));
    // printf("arr1의 합 : %d \n", SUm2DArr(arr1, sizeof(arr1)/sizeof(arr1[0])));
    // printf("arr2의 합 : %d \n", SUm2DArr(arr2, sizeof(arr2)/sizeof(arr2[0])));

    // int arr[3][3] = {1,2,3,4,5,6};
    // arr[2][1] = 4;
    // printf("%d\n", arr[2][1]);
    // (*(arr+2))[1] = 5;
    // printf("%d\n", arr[2][1]);
    // *(arr[2]+1) = 6;
    // printf("%d\n", arr[2][1]);
    // *(*(arr+2)+1) = 7;
    // printf("%d\n", arr[2][1]);

    
    //p387 문제
    //01
    // int* arr1[5];
    // int* arr2[3][5];
    // // 첫번쨰 물음표
    // int** dp1 = arr1; 
    // // 두번째 물음표
    // int* (*dp2)[5] = arr2;

    //05
    int arr[2][2][2] = {100,200,300,400, 10,20,30,40};
    // 2개의 층으로 이루어진 2x2 배열 한층에 4개씩 들감
    // printf("%d \n", ***arr);
    // printf("%p \n", ***arr);
    // printf("%p \n", **arr);
    // printf("%p \n", *arr);
    // printf("%p \n", arr);
    printf("%p \n", arr[0]);
    printf("%p \n", arr[1]);
    printf("%p \n", *(*(arr+1))+1);
    printf("%d \n", *(*(*(arr+1)+1)+1));
    printf("%d \n\n", arr[1][1][1]);

    printf("%p \n", arr[1]);
    printf("%p \n", arr[1][1]);
    printf("%p \n", arr[1][1][1]); // 뒤에 [] 완벽하게 안붙이면 그 지점까지의 주소값만 주는거?

    printf("%d \n", arr[1][0][1]);
    printf("%d \n", (*(arr+1))[0][1]);
    printf("%d \n", (*(*(arr+1))+0)[1]);
    printf("%d \n", *(*(*(arr+1)+0)+1));
    printf("%d \n\n", *((*(arr+1))[0]+1));

    printf("%d \n", *(arr[1][0]+1));
    printf("%d \n", *(*(arr[1]+0)+1));
    printf("%d \n", (*(arr[1]+0))[1]);

    // 배열 옆의 []가 의미하는 것이 그 배열안의 데이터를 가져오겠다는 것? []를 붙이는 순간
    // *를 붙이는 것과 같은 효과가 나타남
    // 왜냐? arr[i] = *(arr+i) 니까...
    // 와 개빡치네...


    return 0;
}

void ShowArr2DStyle(int (*arr)[4], int row) // 배열요소 출력
{
    int i, j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<4; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int SUm2DArr(int arr[][4], int row) // 배열요소 합 반환
{
    int i, j, sum = 0;
    for(i=0; i<row; i++)
    {
        for(j=0; j<4; j++)
            sum += arr[i][j];
    }
    return sum;
}