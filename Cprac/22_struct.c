#include <stdio.h>

struct point{
    int xpos;
    int ypos;
};

// struct person
// {
//     char name[20];
//     char phoneNum[20];
//     int age;
// };

struct circle{
    double radius;
    struct point* center;
};

int main(void)
{
    // struct point pos = {10, 20};
    // struct person man = {"이승기", "010-1212-0001", 21};
    // printf("%d %d \n", pos.xpos, pos.ypos);
    // printf("%s %s %d \n", man.name, man.phoneNum, man.age);


    // 포인터 변수를 구조체 멤버로 선언하기
    struct point cen = {2, 7};
    double rad = 5.5;

    struct circle ring = {rad, &cen};
    printf("원의 반지름 : %g \n",ring.radius);
    printf("원의 중심 : [%d , %d] \n", (ring.center)->xpos, (ring.center)->ypos);

    return 0;
}