#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void MaxMin(int **Max, int **Min) // 포인터 변수의 주소값을 받아옴
{
    int *temp;
    if(**Min > **Max){ // num1의 값을 비교
        temp = *Max; // 포인터 변수 주소값 메모리 안에 있는 것을 역참조 즉, num1의 주소값
        *Max = *Min;
        *Min = temp;
    }

}

int main(void)
{
    char *str[] = {"newjeans", "bunnies"};
    char **ptr = str;
    printf("%s", ptr[0]);
    // 역참조하면 첫번째 문자를 찾아옴
    // 배열의 인덱스값으로 부르는건 역참조 하는거라 생각하면되나?
    
    

    
    return 0;
}