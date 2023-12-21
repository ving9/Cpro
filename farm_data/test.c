#include <stdio.h>
#include <string.h>


int main(){
    FILE* fp;
    fp = fopen("../../farmdata/2013/201301_.csv", "r");
    if (fp == NULL){
        printf("파일을 열 수 없습니다\n");
        return 1;
    }

    char line[256];
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        // char* token;
        // token = strtok(line, ",");
        // while (token != NULL)
        // {
        //     printf("%s", line);
        //     token = strtok(NULL, ",");
        // }
        printf("%s", line);
        
    }

    fclose(fp);
    return 0;
}