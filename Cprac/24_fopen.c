#include <stdio.h>

int main(void){

    // FILE* fp = fopen("data.txt", "wt");
    // if(fp == NULL){
    //     puts("파일 오픈 실패!");
    //     return -1;
    // }
    // fputc('A', fp);
    // fputc('B', fp);
    // fputc('C', fp);
    // fclose(fp);
    
    int ch, i;
    FILE* fp2 = fopen("data.txt", "rt");
    if(fp2 == NULL)
    {
        puts("파일오픈 실패!");
        return -1;
    }
    for(i=0; i<3; i++)
    {
        ch = fgetc(fp2);
        printf("%c \n", ch);
    }
    fclose(fp2);

    return 0;
}