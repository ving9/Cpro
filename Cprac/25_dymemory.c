#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* ReadUserName(void)
{
    char* name = (char*)malloc(sizeof(char)*30); // name을 역참조하면 거기서부터 30바이트를 읽는다는건가?

    printf("What's your name? ");
    fgets(name, 30, stdin);

    return name;
}
// char* ReverseString(void)
// {
//     int maxlen, len, i;
//     char * str;
//     printf("문자열의 최대 길이는? : ");
//     scanf("%d", &maxlen);
//     getchar();
//     str = (char*)malloc(sizeof(char)*(maxlen+1)); // +1은 공백문자까지 받아야하니까..

//     printf("문자열 입력: ");
//     fgets(str, maxlen+1, stdin); // str에 만약 최대길이를 사용자가 10이라고 입력했다면 11까지 받겠다 왜냐? 그래야 널문자까지 받으니까
//     str[strlen(str)-1] = 0; // 아.. 마지막이 \n이 아니어도 어차피 널문자니까 0으로 바꿔도 상관이 없다 개똑똑하네?
    
//     return str;
// }


int main(void)
{
    // int* ptr1 = (int*)malloc(sizeof(int));
    // int* ptr2 = (int*)malloc(sizeof(int)*7);
    // int i;

    // printf("%ld\n\n", sizeof(*ptr2));

    // *ptr1 = 20;
    // for(i=0; i<7; i++)
    //     ptr2[i] = i+1;
    // printf("%d \n", *ptr1);

    // for(i=0; i<7; i++)
    //     printf("%d ", ptr2[i]);
    
    // free(ptr1);
    // free(ptr2);


    // 동적할당으로 함수에서 문자열 받아오기
    // char* name1;
    // char* name2;
    // name1 = ReadUserName();
    // printf("name1 : %s \n", name1); // name1 이 가지고 있는 값은 문자열 근데 문자열은 주소값이기 때문에 %s로 받아와짐
    // printf("name1 : %p \n", name1); // name1 자체의 주소값
    // printf("name1 : %s \n", *name1); // name1이 가지고 있는 값 그자체


    // name2 = ReadUserName();
    // printf("name2 : %s \n", name2);

    // printf("again name1 : %s \n", name1);
    // printf("again name2 : %s \n", name2);
    // free(name1);
    // free(name2);


    // 동적 할당으로 문자열 받아서 역으로 출력하기
    // char* str01;
    // int len, i;
    // str01 = ReverseString();
    // len = strlen(str01);
    
    // for(i=len; i>0; i--) // 0을 제외하지 않으면 첫번째 단어는 출력 안함
    // {
    //     if(str01[i] == ' ')
    //     {
    //         printf("%s ", &str01[i+1]); // 프린트 함수에서 %s를 했을때 문자열 (주소값을 읽으니까... 이렇게하면 알아서 단어까지 읽음..)
    //         str01[i] = 0; // 공백 부분을 null로 만들어서 &str01[i+1] 이것이 문자열 전체 끝까지 읽지 못하게 함
    //     }
    // }
    // printf("%s ", &str01[0]); // 빠진 0번째 단어를 입력;
    // free(str01);

    int num = 5;
    int* inputNum = (int*)malloc(sizeof(int)*num);
    int input;
    int i = 0, y;
    while(1) // 오우 오우 책도 이런식으로 했네
    {
        printf("정수를 입력하세요 : ");
        scanf("%d", &input);
        if(i+1 == num){
            inputNum = (int*)realloc(inputNum, sizeof(int)*( num+=3 )); // 주의할것 realloc은 기존 + 증가량을 해줘야함  기존꺼 없이 증가량만 하면 안됨...
        }
        inputNum[i] = input;
        if(input == -1){
            for(y = 0; y<i; y++)
                printf(" %d", inputNum[y]);
            free(inputNum);
            break;
        }
        i++;
    }

    return 0;
}