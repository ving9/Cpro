#include <stdio.h>

int main(void)
{
    int quit = 1, menu_quit = 1, money, cal3, menu_num = 0;
    char cal1, cal2;
    int menu_list[14] = {1200,1900,1200,1100,900,1100,1800,1900,1600,2100,1700,900,900,1700};
    
    int choice_sum = 0;
    int change = 0;
    while(1)
    {
        int choice_list[256] = {0};
        printf("콜라 1200\n우주맛 콜라 1900\n제로콜라 1200\n스프라이트 1100\n환타 900\n닥터페퍼\n몬스터 1800\n파워에이드 1900\n네스티 1600\n글라소 비타민 워터 2100\n미닛메이드 1700\n조지아커피 900\n암바사 900\n마테차 1700\n");
        printf("돈을 입력하세요 : ");
        scanf("%d", &money);
        if(money < 900)
        {
            printf("돈이 부족합니다\n\n");
        }
        else
        {
            while(1)
            {
                printf("1)콜라 1200\n2)우주맛 콜라 1900\n3)제로콜라 1200\n4)스프라이트 1100\n5)환타 900\n6)닥터페퍼\n7)몬스터 1800\n8)파워에이드 1900\n9)네스티 1600\n10)글라소 비타민 워터 2100\n11)미닛메이드 1700\n12)조지아커피 900\n13)암바사 900\n14)마테차 1700\nS)계산하기\nX)종료하기\n\n");
                printf("원하시는 메뉴를 골라주세요 정확하게 입력: ");
                scanf(" %c%c", &cal1, &cal2);
                printf("%d\n\n", cal1);
                printf("%d\n\n", cal2);
                
                cal3 = cal1 + cal2;
                printf("%d\n\n", cal3);
                if(cal3 == 98 || cal3 == 130)
                {
                    menu_num = 0;
                    printf("초기화면으로 돌아갑니다.\n\n");
                    break;
                }
                else if(cal3 == 93 || cal3 == 125)
                {
                    menu_num = 0;
                    for(int i = 0; i < sizeof(choice_list) / sizeof(int);i++)
                    {
                        choice_sum += choice_list[i];
                    }
                    if(money < choice_sum)
                    {
                        printf("돈이 부족합니다 다시 돈넣으세요\n\n");
                        break;
                    }
                    else
                    {
                        change = money - choice_sum;
                        printf("결제 완료 되었습니다. 거스름돈 : %d원 입니다\n\n", change);
                        break;
                    }
                }
                else
                {
                    if(cal3 >= 97 && cal3 <=101)
                    {
                        cal3 -= 88;
                        choice_list[menu_num] = menu_list[cal3];
                        menu_num++;
                    }
                    else if(cal3 >= 59 && cal3 <= 67)
                    {
                        cal3 -= 49;
                        choice_list[menu_num] = menu_list[cal3];
                        menu_num++;
                    }
                }
            }
        }

    }


    return 0;
}
