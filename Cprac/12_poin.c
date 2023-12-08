#include <stdio.h>

int main(void)
{
    const unsigned int NUM1 = 3;
    const unsigned int NUM2 = 5;
    const unsigned int NUM3 = NUM1 & NUM2;
    printf("%d\n", NUM3);
    printf("%p\n", (void*)&NUM3);


    // int num1 = 100, num2 = 100;
    // int* pnum;
    
    // pnum = &num1;
    // *pnum += 30;

    // pnum = &num2;
    // *pnum -= 30;

    // printf("num1 : %d, num2 : %d\n\n", num1, num2);

    // p 284 문제
    // 01
    // int num = 10;
    // int * ptr1 = &num;
    // int * ptr2 = ptr1;

    // (*ptr1)++;
    // (*ptr2)++;
    // printf("%d \n", num);

    // 02  // 참조할 주소를 이미 알고 있다면
    // int num1 = 10, num2 = 20;

    // int * ptr1 = &num1;
    // int * ptr2 = &num2;

    // *ptr1 += 10;
    // *ptr2 -= 10;

    // ptr1 = &num2;  
    // ptr2 = &num1;

    // printf("ptr1 : %d, ptr2 : %d\n\n", *ptr1, *ptr2);

    // 02 -2  // 참조할 주소를 정확히 모르는데 두 포인터를 바꿔야 하는 경우
    // int num1 = 10, num2 = 20;

    // int * ptr1 = &num1;
    // int * ptr2 = &num2;

    // *ptr1 += 10;
    // *ptr2 -= 10;

    // int * temp = ptr1;
    // ptr1 = ptr2;
    // ptr2 = temp;

    // printf("ptr1 : %d, ptr2 : %d\n\n", *ptr1, *ptr2);


    // p299 문제
    // 01
    // int arr[5] = {1,2,3,4,5};
    // int * ptr = &arr[0];
    // int i;
    // for(i=0; i <5; i++)
    // {
    //     *(ptr++) += 2;
    //     printf("%d", arr[i]);
    // }
    // printf("\n");

    // 02
    // ptr = &arr[0];
    // printf("%p\n", ptr);
    // for(i=0; i <5; i++)
    // {
    //     if(i == 0)
    //         *ptr += 2;
    //     else
    //         *(ptr+i) += 2;
    //     printf("%d", arr[i]);
            
    // }
    // printf("%p\n", ptr);

    // 03
    // int arr[5] = {1,2,3,4,5};
    // int *ptr = &arr[4];
    // int sum = 0, i;
    // for(i = 0; i < 5; i++)
    // {
    //     sum += *(ptr--);
    // }
    // printf("배열의 합은 %d\n\n", sum);

    // 04
    // int arr[6] = {1,2,3,4,5,6};
    // int * ptr1 = &arr[0];
    // int * ptr2 = &arr[5];
    // int i, temp;
    // for(i = 0; i < (sizeof(arr)/sizeof(int))/2; i++)
    // {
    //     temp = *(ptr1+i);
    //     *(ptr1+i) = *(ptr2-i);
    //     *(ptr2-i) = temp;
    //     // *ptr1++;
    //     // *ptr2--;
    // }
    // for(i=0; i<6; i++)
    //     printf("%d", arr[i]);

    // char str1[] = "My String";
    // char * str2 = "Your String";
    // printf("%s %s\n", str1, str2);

    // str2 = "Our String";
    // printf("%s %s \n", str1 ,str2);
    // str1[0]="x";
    // // str2[0]="x"; // 상수형태의 문자배열은 가르키는 문자열은 스위칭이 가능하지만 그 문자열의 일부를 수정하는 것은 불가능하다
    // printf("%s %s \n", str1 ,str2);

    // int num1=10, num2=20, num3=30;
    // int * arr[3]={&num1, &num2, &num3};
    // printf("%d \n", *arr[0]);
    // printf("%d \n", *arr[1]);
    // printf("%d \n", *arr[2]);


    // 문자열 포인터 배열
    char * strArr[]= {"Simple", "String", "Array"}; // 문자열 자체가 주소값으로 변경되므로..
    printf("%s\n", strArr[0]); // 이렇게 부르면 주소값이 나오는데 어차피 문자열은 주소값을 불러오므로 상관없다
    printf("%s\n", strArr[1]);
    printf("%s\n", strArr[2]);

    printf("%p\n", strArr[0]); // Simple 의 S가 가진 주소값 호출
    printf("%d\n", *strArr[0]); // Simple 의 S가 가지고 있는 아스키코드넘버가 추출된다;
    
    return 0;
}