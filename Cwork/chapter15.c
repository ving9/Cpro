#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void OddNum(int* arr, size_t len);
void EvenNum(int* arr, int len);
int StringNum(const char* arr);
void DesSort(int* arr, int len);

int main(void)
{
    // 01
    // int arr[10], i = 0;
    // int Lenarr = sizeof(arr)/sizeof(int);
    // printf("총 10개의 정수 입력\n");
    // while(i < 10)
    // {
    //     printf("입력 : ");
    //     scanf("%d", &arr[i]);
    //     i++;
    // }
    // printf("홀수 출력 : ");
    // OddNum(arr, Lenarr);
    // printf("짝수 출력 : ");
    // EvenNum(arr, Lenarr);

    // 02
    // int num, i = 0, temp, cnt;
    // printf("10진수 정수 입력 : ");
    // scanf("%d", &num); 
    // int sum[32]; // int타입 변수 num의 2진수 최대 표현 자릿수는 32자리 이므로 이것이 최대값이다
    // while(num > 0)
    // {
    //     sum[i] = num % 2; // 배열에 2로 나눈 나머지 값 계속 저장
    //     num /= 2; // 최초 받은 num값 계속 2로 나눠서 초기화
    //     if(num == 1) // num이 1일때는 2진수를 구하는 연산이 끝난 것이므로 더 나누지 말고 종료시켜야함
    //     {
    //         sum[++i] = 1; // i가 아직 바뀌기 전이므로 증가시키고 입력시킨다
    //         break;
    //     }
    //     i++;
    // }
    // for(cnt = 0; cnt <= i/2; cnt++)  // i가 내가 원하는 2진수가 입력된 마지막 칸의 번호 이므로 거기까지만 계산하면 된다
    // {
    //     temp = sum[cnt];
    //     sum[cnt] = sum[(i) - cnt];
    //     sum[(i) - cnt] = temp;        
    // }
    // for(cnt = 0; cnt <= i; cnt++)
    // {
    //     printf("%d", sum[cnt]);    
    // }
    
    // 03
    // int arr[10], i, num;
    // int lenarr = sizeof(arr)/sizeof(int);
    // int odd = 0, even = (lenarr - 1); // 홀수와 짝수에 해당하는 배열의 번호를 서로 다르게 저장하고 조건에 따라 변화하게 하면 됨

    // printf("총 10개의 숫자 입력\n");
    // for(i=0; i < lenarr; i++) // 총 횟수는 배열의 수만큼 진행
    // {
    //     printf("입력 : ");
    //     scanf("%d", &num);
    //     if (num % 2 != 0)
    //     {
    //        arr[odd] = num;
    //        odd++; // 홀수에 해당 될때만 증가
    //     }
    //     else
    //     {
    //         arr[even] = num;
    //         even--; // 짝수에 해당 될때만 감소
    //     }
    // }
    // printf("배열요소의 출력 : ");
    // for(i=0; i < lenarr; i++)
    // {
    //     printf(" %d", arr[i]);
    // }

    // 04
    char input_[256];
    int input_Num; // 문자열 길이 저장할 변수
    int cnt; // 문자열 0번부터 확인할 변수
    int numCheck = 0; // 문자열 앞과 끝이 같을때마다 +1씩 올라가는 변수

    printf("회문인지 판단할 영단어 입력 : ");
    scanf(" %s", input_);
    input_Num = StringNum(input_); // 문자열 길이 알려주는 함수
    
    for(cnt = 0; cnt < input_Num/2; cnt++)
    {
        if(input_[cnt] == input_[(input_Num - 1) - cnt])
            numCheck++;
    }
    if(numCheck == input_Num/2)
        printf("회문입니다. \n\n");
    else
        printf("회문아닙니다.\n\n");

    


    // 도전 5
    int arr[7], cnt;
    srand(time(0));
    for(cnt = 0; cnt < sizeof(arr)/sizeof(int); cnt++)
    {
        arr[cnt] = rand() % 100 + 1;
    }
    for(cnt = 0; cnt < sizeof(arr)/sizeof(int); cnt++)
    {
        printf(" %d", arr[cnt]);
    }
    printf("\n\n");
    DesSort(arr, sizeof(arr)/sizeof(int));
    for(cnt = 0; cnt < sizeof(arr)/sizeof(int); cnt++)
    {
        printf(" %d", arr[cnt]);
    }
    printf("\n\n");    





    return 0;
}



void OddNum(int* arr, size_t len)
{
    int cnt;
    for(cnt = 0; cnt < len; cnt++)
    {
        if(arr[cnt] % 2 != 0) 
        {
            printf(" %d", arr[cnt]);
        }
    }
    printf("\n");
}

void EvenNum(int* arr, int len)
{
    int cnt;
    for(cnt = 0; cnt < len; cnt++)
    {
        if(arr[cnt] % 2 == 0)
        {
            printf(" %d", arr[cnt]);
        }
    }
    printf("\n");
}

int StringNum(const char* arr)
{
    int cnt = 0; // 문자열 길이 저장할 변수
    while(arr[cnt] != '\0') // '\0'은 그냥 0으로 써도 됨
    {
        cnt++;
    }
    return cnt;
}

void DesSort(int* arr, int len)
{
    int cnt01; // 총 확인할 라운드 
    int cnt02; // 맨 마지막 제외하면서 돌릴 숫자
    int temp; // 바꾸기 위해 잠시 저장할 변수

    for(cnt01 = 0; cnt01 < len-1; cnt01++)
    {
        for(cnt02 = 0; cnt02 < (len-1)-cnt01; cnt02++) // 배열의 길이와 배열의 순번을 헷깔리지 말자 len-1을 해야 다음항까지 확인가능
        {
            if(arr[cnt02]<arr[cnt02+1])
            {
                temp = arr[cnt02];
                arr[cnt02] = arr[cnt02+1];
                arr[cnt02+1] = temp;
            }
        }
    }
}