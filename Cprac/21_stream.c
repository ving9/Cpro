#include <stdio.h>
void ClearLine(void);
// struct employee
// {
//     char name[20];
//     char regiNum[20];
//     int salary;
// };

struct point
{
    int xpos;
    int ypos;
    struct point* ptr;
};

// struct circle
// {
//     double radius;
//     struct point* center;
// };

int main(void)
{
    // int ch1, ch2;

    // ch1 = getchar();
    // ch2 = fgetc(stdin);

    // putchar(ch1);
    // fputc(ch2, stdout);

    // int ch;
    // while(1)
    // {   
    //     ch = getchar();
    //     if(ch == EOF)
    //         break;
    //     putchar(ch);
    // }

    // int strBin;
    // int chardiff = 'a' - 'A';
    // strBin = getchar();
    // if(strBin >= 'a' && strBin <= 'z')
    //     strBin -= chardiff;
    // else if(strBin >= 'A' && strBin <= 'Z')
    //     strBin += chardiff;
    // else
    // {
    //     strBin = -1;
    //     puts("잘못된 입력입니다.");
    // }
    // putchar(strBin);

    // char str[7];
    // int i;

    // for(i = 0; i < 3; i++)
    // {
    //     fgets(str, sizeof(str), stdin);
    //     printf("Read %d: %s \n", i+1, str);
    // }

    // char perID[7];
    // char name[10];

    // fputs("주민번호 앞 6자리 입력: ", stdout);
    // fgets(perID, sizeof(perID), stdin);
    // ClearLine();

    // fputs("이름 입력: ", stdout);
    // fgets(name, sizeof(name), stdin);

    // printf("주민번호 : %s \n", perID);
    // printf("이름 : %s \n", name);

    // struct employee num1;

    // printf("종업원 이름 : ");
    // scanf("%s", num1.name);

    // printf("주민등록번호 : ");
    // scanf("%s", num1.regiNum);

    // printf("급여정보 (정수로입력) : ");
    // scanf("%d", &num1.salary);

    // printf("이름 : %s 주민번호 : %s 급여정보 : %d \n\n", num1.name, num1.regiNum, num1.salary);
    
    // struct employee arr[3];
    // int cnt;
    // for(cnt = 0; cnt<3; cnt++)
    // {
    //     printf("이름, 주민번호, 봉급 입력 : ");
    //     scanf("%s %s %d", arr[cnt].name, arr[cnt].regiNum, &arr[cnt].salary);
    // }
    // for(cnt = 0; cnt<3; cnt++)
    // {
    //     printf("%d번째 사원 정보\n 이름 : %s 주민번호 : %s 봉급 : %d\n", cnt+1, arr[cnt].name, arr[cnt].regiNum, arr[cnt].salary);
    // }

    // struct point cen = {2, 7};
    // double rad = 5.5;

    // struct circle ring = {rad, &cen};
    
    // printf("원의 반지름 :%g \n", ring.radius);
    // printf("원의 중심 [%d, %d] \n", (ring.center)->xpos, (ring.center)->ypos);

    struct point pos1 = {1, 1};
    struct point pos2 = {2, 2};
    struct point pos3 = {3, 3};

    pos1.ptr = &pos2;
    pos2.ptr = &pos3;
    pos3.ptr = &pos1;

    printf("점의 연결관계... \n");
    printf("%d, %d와 %d, %d 연결\n", pos1.xpos, pos1.ypos, pos1.ptr->xpos, pos1.ptr->ypos);

    return 0;
}

void ClearLine(void)
{
    while(getchar() != '\n');
}