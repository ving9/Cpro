#include <stdio.h>
typedef struct point    
{
    int xpos;
    int ypos;
} Point;

// void ShowPosition(Point pos)
// {
//     printf("[%d, %d] \n", pos.xpos, pos.ypos);
// }

// Point GetCurPos(void)
// {
//     Point cen;
//     printf("Input current pos : ");
//     scanf("%d %d", &cen.xpos, &cen.ypos);
//     return cen;
// }

// Point AddPoint(Point pos1, Point pos2)
// {
//     Point pos = {pos1.xpos + pos2.xpos, pos1.ypos + pos2.ypos};
//     return pos;
// }
// Point SubPoint(Point pos1, Point pos2)
// {
//     Point pos = {pos1.xpos - pos2.xpos, pos1.ypos - pos2.ypos};
//     return pos;
// }

// void SwapPoint(Point* pos1, Point* pos2)
// {
//     // Point change = {pos1->xpos, pos1->ypos}; // 아니 이렇게 안해도 된다고!!
//     Point change = *pos1;
//     *(pos1) = *(pos2);
//     *(pos2) = change;
// }

typedef enum
{
    Do = 1, Re = 2, Mi=3, Fa=4, So=5, La=6, Ti=7
} Syllable;

void Sound(Syllable sy)
{
    switch (sy)
    {
        case Do: puts("도는 하얀 도라지"); return;
        case Re: puts("레는 둥근 레코드"); return;
        case Mi: puts("미는 파란 미나리"); return;
        case Fa: puts("파는 예쁜 파랑새"); return;
        case So: puts("솔은 작은 솔방울"); return;
        case La: puts("라는 라디오"); return;
        case Ti: puts("시는 졸졸 시냇물"); return;
    }
}

int main(void)
{
    // Point curPos = GetCurPos();
    // ShowPosition(curPos);


    // 구조체 변수간 연산
    // Point pos1 = {5, 6};
    // Point pos2 = {2, 9};
    // Point result;

    // result = AddPoint(pos1, pos2);
    // printf("[%d %d] \n", result.xpos, result.ypos);

    // result = SubPoint(pos1, pos2);
    // printf("[%d %d] \n", result.xpos, result.ypos);


    // // 구조체 변수간 스왑
    // Point pos1 = {2, 4};
    // Point pos2 = {5, 7};
    // printf("[%d %d], [%d %d]\n", pos1.xpos, pos1.ypos, pos2.xpos, pos2.ypos);
    // SwapPoint(&pos1, &pos2);
    // printf("[%d %d], [%d %d]\n", pos1.xpos, pos1.ypos, pos2.xpos, pos2.ypos);


    // 열거형 변수
    Syllable tone;
    for(tone=Do; tone<=Ti; tone+=1)
        Sound(tone);
    return 0;
}