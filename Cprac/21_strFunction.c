#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void RemoveBSN(char str[]){
//     int len = strlen(str);
//     str[len-1] = 0;
// }

int main(){

    // char str[] = "1234567";
    // printf("%ld \n", strlen(str));

    // char str[100];
    // printf("문자열 입력: ");
    // fgets(str, sizeof(str), stdin);
    // printf("길이: %ld, 내용: %s \n", strlen(str), str);
    // RemoveBSN(str);
    // printf("길이: %ld, 내용: %s \n", strlen(str), str);  // fgets로 받으면 마지막 사용자가 때린 엔터 \n 까지 인식하므로 그걸 없애주는 과정
    // return 0;


    // // 문자열 복사
    // char str1[20] = "1234567890";
    // char str2[20];
    // char str3[5];
    // // case 1
    // strcpy(str2, str1);
    // puts(str2);

    // // case 2
    // strncpy(str3, str1, sizeof(str3));
    // puts(str3);

    // // case 3
    // strncpy(str3, str1, sizeof(str3)-1); // 마지막에 널문자를 자동으로 복사해주지 않으므로 마지막 전까지만 복사하고..
    // str3[sizeof(str3)-1] = 0; // 마지막 항에 0으로 널문자를 추가해준다
    // puts(str3);
  

    // // 문자열 덧붙이기
    // char str1[20] = "First~ ";
    // char str2[20] = "Second";

    // char str3[20] = "Simple num : ";
    // char str4[20] = "1234567890";

    // // case 1
    // strcat(str1, str2); // str1의 뒤에 str2를 덧붙이겠다
    // puts(str1);

    // // case 2
    // strncat(str3, str4, 7); // str3의 뒤에 str4에서 7문자만큼 덧붙이겠다 (실제론 8문자 넘어감 널문자 포함해서)
    // puts(str3); 


    // 문자열 비교하기
    // char str1[20];
    // char str2[20];
    // printf("문자열 입력 1:");
    // scanf("%s", str1);
    // printf("문자열 입력 2:");
    // scanf("%s", str2);

    // if(!strcmp(str1, str2))
    //     puts("두 문자열은 동일");
    // else
    // {
    //     puts("두 문자열 동일하지 않음");
    //     if(!strncmp(str1, str2, 3))
    //         puts("그러나 앞 세글자는 동일합니다");
    // }

    char str[20];
    printf("정수 입력 : ");
    scanf("%s", str);
    printf("%d\n", atoi(str)); // 문자열 내용을 인트로 변환

    printf("실수 입력: ");
    scanf("%s", str);
    printf("%g\n", atof(str)); // 문자열 내용을 더블형으로 변환


    return 0;   
}