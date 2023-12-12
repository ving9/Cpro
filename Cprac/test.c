#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
    char abc[1024] = "newjeans\n";
    int num;
    num = strlen(abc);
    printf("%d\n", num);
    
    return 0;
}