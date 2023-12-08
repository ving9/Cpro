#include <stdio.h>

int main(void)
{
    // int arr[5];
    // int sum = 0, i;

    // arr [0] = 10, arr [1] = 20, arr [2] = 30, arr [3] = 40, arr [4] = 50;

    // for (i = 0; i < sizeof(arr)/sizeof(int); i++)
    // {
    //     sum += arr[i];
    // }
    // printf("%d\n\n", sum);


    // p260 문제
    // 01
    // int arr1[5];
    // int max, min, sum;
    // for(int i = 0; i < 5; i++)
    // {
    //     printf("정수를 입력하세요 : ");
    //     scanf("%d", &arr1[i]);
    // }
    // max = sum = min = arr1[0];  // 이렇게 쓸 생각 한번도 안해봤다... 이게 되는구나?
    // for(int i = 1; i < sizeof(arr1) / sizeof(int); i++)
    // {
    //     sum += arr1[i];
    //     if(max < arr1[i]) // 이미 첫번쨰 값이 들어갔으므로.. 쭉 비교만 하면 최대값 나옴
    //     {
    //         max = arr1[i];
    //     }
    //     if(min > arr1[i])
    //     {
    //         min = arr1[i];
    //     }
    // }
    // printf("5개 정수중의 합 : %d\n", sum);
    // printf("5개 정수중에 최대값 : %d\n", max);
    // printf("5개 정수중에 최소값 : %d\n", min);

    // // 02
    // char good[] = "Good time";
    // for(int i = 0; i < sizeof(good) / sizeof(char); i++)
    // {
    //     printf("%c", good[i]);
    // }


    // char str[] = "good morning!";
    // printf("배열 str의 크기 : %d \n", sizeof(str));
    // printf("널 문자 문자형 출력 : %c \n", str[sizeof(str)-1]);
    // printf("널 문자 정수형 출력 : %d \n", str[sizeof(str)-1]);

    // str[sizeof(str)-2] = '?';
    // printf("문자열 출력 : %s \n", str);


    // char str[50];
    // int idx;
    // printf("문자열 입력 : ");
    // scanf("%s", str);
    // printf("입력 받은 문자열 : %s \n", str);

    // printf("문자 단위 출력 : ");
    // for(idx = 0; str[idx] != '\0'; idx++)
    // {
    //     printf("%c", str[idx]);
    // }
    // printf("\n");

    // char str[] = "I like C programming";
    // printf("string: %s \n", str);

    // str[8] = '\0';
    // printf("string: %s \n", str);

    // str[1] = '\0';
    // printf("string: %s \n", str);

    // printf("%c\n", str[7]); // 여전히 나머지 문자는 문자열에 저장 되어 있다


    // p268 문제
    // 01
    // char eng[50];
    // int cnt = 0;
    // printf("Type the english word : ");
    // scanf("%s", eng);

    // while(eng[cnt] != '\0')
    // {
    //     cnt++;
    // }
    // printf("%s의 단어 길이는 : %d 입니다\n\n", eng, cnt);

    // // 02
    // char word[50], temp;
    // int cnt = 0, i;
    // printf("Type the english word : ");
    // scanf("%s", word);
    // while(word[cnt] != '\0')
    // {
    //     cnt++;
    // }
    // for(i = 0; i < cnt/2; i++)
    // {
    //     temp = word[i];
    //     word[i] = word[(cnt-1)-i];
    //     word[(cnt-1)-i] = temp;
    // }
    // printf("Reverse word : %s \n\n", word);

    // 03
    char input_[50];
    int cnt = 0, max = 0;
    printf("영단어를 입력하면 아스키코드가 가장 큰값을 찾아드림 : ");
    scanf("%s", input_);
    while(input_[cnt] != 0)
    {
        if(max < input_[cnt])
        {
            max = input_[cnt];
        }
        cnt++;
    }
    printf("%s 중에 아스키 코드가 가장 큰 문자는 %c\n\n", input_, max);


    return 0;
}