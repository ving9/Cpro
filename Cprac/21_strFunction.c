#include <stdio.h>
#include <string.h>

void RemoveBSN(char str[]){
    int len = strlen(str);
    str[len-1] = 0;
}

int main(){

    // char str[] = "1234567";
    // printf("%ld \n", strlen(str));


    char str[100];
    printf("문자열 입력: ");
    fgets(str, sizeof(str), stdin);
    printf("길이: %ld, 내용: %s \n", strlen(str), str);

    RemoveBSN(str);
    printf("길이: %ld, 내용: %s \n", strlen(str), str);  // fgets로 받으면 마지막 사용자가 때린 엔터 \n 까지 인식하므로 그걸 없애주는 과정
    return 0;
}