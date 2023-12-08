#include <stdio.h>
#include "header.h"
 
int main(void)
{
    int a=1, b=2, add;
    double ave;
    point dot={1, 2};
 
    add=sum(a, b);
    printf("Sum is %d\n", add);
 
    ressum(&a, &b, &add);
    printf("Sum is %d\n", add);
 
    ave=average(a, b);
    printf("Average is %f\n", ave);
 
    resaverage(&a, &b, &ave);
    printf("Average is %f\n", ave);
 
    dot.x++; dot.y++;
    printf("점을 x방향으로 1, y방향으로 1 평행이동: (%f, %f)", dot.x, dot.y);
 
    return 0;
}