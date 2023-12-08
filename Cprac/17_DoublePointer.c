#include <stdio.h>
void MaxAndMin(int* arr,int** max, int** min, int len);

int main(void)
{
    // int* maxPtr = 0;
    // int* minPtr = 0;
    // int arr[5] = {1, 2, 3, 4, 5};
    // int lenarr = sizeof(arr)/sizeof(int);
    // MaxAndMin(arr, &maxPtr, &minPtr, lenarr);

    // printf("%p %p\n\n", &arr[4], &arr[0]);
    // printf("%p %p\n\n", maxPtr, minPtr);
    // printf("%d %d\n\n", *maxPtr, *minPtr);

    // 너 이거 틀렸어 중요해..
    int num1, num2;
    int* p;
    int* q;
    int* r;
    int** pp;

    num1 = 10;
    num2 = 20;

    p = &num1;
    q = &num2;
    r = &num1;

    pp = &p;
    *pp = q;  // 여기서 p가 &num2 가 된다  // 제발 치환하지말고 걍 순서대로 생각하라고!!!
    // *pp는 p일 뿐이야 &num1으로 치환해서 생각하지마!!!!!!!! 
    // 이 식은 p라는 메모리 안에 &num2라는 데이터를 넣는다라고 생각해야됨
    // 글고 이건 대입연산이니까 당연히 그렇게 생각해야지
    // num = 10은 num이라는 변수(메모리) 안에 10이라는걸 넣는거잖아 새꺄
    **pp = 1024; // 여기서 num2 = 1024가 된다
    pp = &r;
    **pp = *p * 2;  // num1 = num2 * 2;

    printf("%d %d\n\n", num1, num2);





    return 0;
}

void MaxAndMin(int* arr,int** max, int** min, int len)
{
    // max 가 나타내는 것은 maxPtr자체의 주소
    // min 이 나타내는 것은 minPtr자체의 주소

    int cnt; // 횟수 체크하는 변수
    int* MAX = &arr[0]; 
    int* MIN = &arr[0];
    for(cnt=0; cnt < len; cnt++)
    {
        if(*MAX<arr[cnt])   // 이렇게 해놓으면 비교할 땐 숫자(데이터)로 비교하고
            MAX = &arr[cnt]; // 저장할땐 주소값으로 저장할 수 있다...
        if(*MIN>arr[cnt])
            MIN = &arr[cnt];
    }
    *max = MAX; // *max는 받아온 포인터 함수의 메모리 주소값안에 있는 데이터를 의미함
    *min = MIN; // 즉 max라는 포인터의 주소값의 메모리안에 MAX라는 주소값을 넣는다는 의미
}