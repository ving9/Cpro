#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM 5 //개발몬 숫자

typedef struct
{
    char* name;
    int iNum;
    char* pName;
    char* skpName;
    int hp, max_hp, mp, max_mp;
    int power, sk_power;
} DevMon;

DevMon init_mon = { "0",-1, };
DevMon devmon[NUM+1]={{"꼬부기",1,"몸통박치기","물대포",},{"이상해씨",2,"전광석화","솔라빔",},{"파이리",3,"마구햘퀴기","브레스",},{"고라파덕",4,"박치기","뇌절",},{"잠만보",5,"한손밀치기","지구던지기",},{"0",-1,}};
DevMon user_mon[3] = {{"0",-1,},{"0",-1,},{"0",-1,}};

typedef struct //유저 정보 저장
{
    char name[20];
    int level, xp, hour;
    int xpos, ypos;
    int total_hp, max_hp;  // Hp 총합, Hp 최댓값
} UserInfo;
UserInfo userS;

typedef struct
{
    FILE* img[NUM];
    char gnt[50];
} MonImg;
MonImg monFace;

typedef struct
{
    int selUser;
    int selNpc;
} SelNum;
SelNum selNum;

typedef struct //아이템
{
    char name[20];
    int iNum;
    int fig; //아이템 수치
    int count;
} Item;
Item mash[3] = {{"얼음",0,0,},{"주먹밥",1,100},{"커피",2,50}}; 
Item user_item[5]= { {"0",-1,},{"0",-1,} ,{"0",-1,},{"0",-1,} ,{"0",-1,} };


void ClearBuffer(void);
void init_play(void);
int CountMon(DevMon* mon);
void UpdateHp(void);
void AddTeam(DevMon* mon1, DevMon* mon2, int idx);


void PrintBattle(int iNum);
void PrintVic(int iNum);
void Attack01(int atNum,int dfNum, DevMon* atmon, DevMon* dfmon);
void Attack02(int atNum,int dfNum, DevMon* atmon, DevMon* dfmon);
void NpcAttack(void);
void BattleActSel(int num);
int BattleMonSel(int num);
void BattleVictory(void);
void BattleCore(void);


//개발몬 리스트(배열) 선언 필요 -> 구조체 리스트로도 가능
//char* mon_list[개발몬수]; 개발몬 이름 저장
//int mon_skill[개발몬수][4(hp,mp,공격력,특수공격력)]; 능력치 저장


int main(void)
{   
    // monFace.img[0] = fopen("img\\mon1.txt","rt");
    // monFace.img[1] = fopen("img\\mon2.txt","rt");
    // monFace.img[2] = fopen("img\\mon3.txt","rt");

    srand(time(NULL));
    int choice;
    int i;
    printf("시작화면 \n");
    printf("당신의 이름은? >");
    scanf("%s", userS.name);
    init_play();
    for(int i=0;i<CountMon(devmon);i++) 
    {
        printf("%d번 몬스터 name: %s hp: %d mp: %d\n",i+1,devmon[i].name,devmon[i].hp,devmon[i].mp);
        printf("공격력: %d 특수공격력: %d\n",devmon[i].power,devmon[i].sk_power);
    }
    printf("어떤 몬스터를 고르실껀가요? : ");
    scanf("%d", &choice);
    choice -= 1;
    AddTeam(devmon, user_mon, choice);
    while(1)
    {
        BattleCore();
        printf("test");
    }
    printf("\n\n");
    return 0;
}








void ClearBuffer(void)
{
    while (getchar() != '\n');
}

void init_play(void) //개발몬 초기 능력치 설정
{
    for (int i = 0;i < NUM;i++)
    {
        devmon[i].hp = rand() % 100 + 200; devmon[i].max_hp = devmon[i].hp; //최소 몇 최대 몇
        devmon[i].mp = rand() % 50 + 50; devmon[i].max_mp = devmon[i].mp;
        devmon[i].power = rand() % 40 + 50;
        devmon[i].sk_power = rand() % 50 + 50;
    }
}

int CountMon(DevMon* mon) // 개발몬 수 세기
{
    int idx = 0;
    while(mon[idx].iNum > 0)
    {
        idx++;
    }
    return idx;
}
//유저 hp정보 갱신
void UpdateHp(void)
{
    userS.total_hp = 0; userS.max_hp = 0;
    for (int i = 0;i < CountMon(user_mon);i++)
    {
        userS.total_hp += user_mon[i].hp;
        userS.max_hp += user_mon[i].max_hp;
    }
}

void AddTeam(DevMon* mon1, DevMon* mon2, int idx)
{
    //mon1의 idx번째 멤버를 mon2에 추가
    // int uidx = 0; CountMon(mon2); 
    int uidx = CountMon(mon2);

    mon2[uidx] = mon1[idx]; //mon1의 idx번째 개발몬 정보 mon2에 복사
    // mon2[uidx].iNum = uidx; //고유번호 설정

    //빠져나간 멤버 리스트에서 제거 ->배열 요소 제거 함수로 따로 구현해도 될듯!
    // for (int i = idx;i < NUM - 1;i++)
    for (int i = idx;i < CountMon(mon1) - 1;i++)
    {
        mon1[i] = mon1[i + 1];
        // mon1[i].iNum--;
    }
    mon1[NUM - 1] = init_mon; //빈자리 초기화
    UpdateHp();
}



void PrintBattle(int iNum) // 몬스터 고유번호 받아오기
{
    monFace.img[0] = fopen("img/mon1.txt","rt");
    monFace.img[1] = fopen("img/mon2.txt","rt");
    monFace.img[2] = fopen("img/mon3.txt","rt");
    monFace.img[3] = fopen("img/mon4.txt","rt");
    monFace.img[4] = fopen("img/mon5.txt","rt");
    system("clear");
    while(fgets(monFace.gnt, 50, monFace.img[iNum-1]) != 0) 
    {
        printf("%s", monFace.gnt);
    }
    fclose(monFace.img[iNum-1]);
    printf("---------------------------------------------------------------------------------------------\n");
    printf("(%s)%s HP:%d/%d  MP:%d/%d  DMG:%d    ", userS.name,user_mon[selNum.selUser].name, user_mon[selNum.selUser].hp,user_mon[selNum.selUser].max_hp,user_mon[selNum.selUser].mp,user_mon[selNum.selUser].max_mp,user_mon[selNum.selUser].power);
    printf("(NPC)%s HP:%d/%d  MP:%d/%d  DMG:%d\n", devmon[selNum.selNpc].name, devmon[selNum.selNpc].hp,devmon[selNum.selNpc].max_hp, devmon[selNum.selNpc].mp,devmon[selNum.selNpc].max_mp, devmon[selNum.selNpc].power);
    printf("---------------------------------------------------------------------------------------------\n");
}
void PrintVic(int iNum) 
{
    monFace.img[0] = fopen("img/mon1.txt","rt");
    monFace.img[1] = fopen("img/mon2.txt","rt");
    monFace.img[2] = fopen("img/mon3.txt","rt");
    monFace.img[3] = fopen("img/mon4.txt","rt");
    monFace.img[4] = fopen("img/mon5.txt","rt");
    system("clear");
    while(fgets(monFace.gnt, 50, monFace.img[iNum-1]) != 0) 
    {
        printf("%s", monFace.gnt);
    }
    fclose(monFace.img[iNum-1]);
    printf("---------------------------------------------\n");
    printf("%s HP:%d  MP:%d  DMG:%d SDMG:%d\n", devmon[selNum.selNpc].name, devmon[selNum.selNpc].max_hp, devmon[selNum.selNpc].max_mp, devmon[selNum.selNpc].power,devmon[selNum.selNpc].sk_power);
    printf("---------------------------------------------\n");
}


void Attack01(int atNum,int dfNum, DevMon* atmon, DevMon* dfmon)
{
    int event = rand() % 100 + 1;
    PrintBattle(atmon[atNum].iNum);
    printf("%s 의 공격시도!\n", atmon[atNum].name);
    sleep(1);
    if(event <= 20)
    {
        dfmon[dfNum].hp -= (atmon[atNum].power * 2);
        if(dfmon[dfNum].hp <= 0)
            dfmon[dfNum].hp = 0;
        PrintBattle(atmon[atNum].iNum);
        printf("%s!!\n", atmon[atNum].pName);
        printf("크리티컬 히트!! %s에게 %d의 치명타를 입혔다\n", dfmon[dfNum].name, (atmon[atNum].power * 2));
        sleep(2);
    }
    else
    {
        dfmon[dfNum].hp -= atmon[atNum].power;
        if(dfmon[dfNum].hp <= 0)
            dfmon[dfNum].hp = 0;
        PrintBattle(atmon[atNum].iNum);
        printf("%s! %s에게 %d의 데미지를 입혔다\n", atmon[atNum].pName, dfmon[dfNum].name, atmon[atNum].power);
        sleep(2);
    }
}

void Attack02(int atNum,int dfNum, DevMon* atmon, DevMon* dfmon)
{
    PrintBattle(atmon[atNum].iNum);
    printf("%s 의 특수공격!\n", atmon[atNum].name);
    sleep(1);
    dfmon[dfNum].hp -= (atmon[atNum].sk_power);
    atmon[atNum].mp -= 50;
    if(dfmon[dfNum].hp <= 0)
        dfmon[dfNum].hp = 0;
    PrintBattle(atmon[atNum].iNum);
    printf("%s!!\n", atmon[atNum].skpName);
    printf("공격성공! %s에게 %d의 데미지를 입혔다\n", dfmon[dfNum].name, (atmon[atNum].power * 2));
    sleep(2);
}


void NpcAttack(void)
{
    int event;
    if (devmon[selNum.selNpc].hp == 0)
        return;
    else if(devmon[selNum.selNpc].mp >= 50)
    {
        event = rand() % 100 + 1;
        if(event <= 80)
        {
            Attack01(selNum.selNpc, selNum.selUser, devmon, user_mon);
        }
        else
        {
            Attack02(selNum.selNpc, selNum.selUser, devmon, user_mon);
        }
    }
    else
    {
        Attack01(selNum.selNpc, selNum.selUser, devmon, user_mon);
    } 
}


void BattleActSel(int num)
{
    if(num == 1)
    {
        Attack01(selNum.selUser, selNum.selNpc, user_mon, devmon);
        NpcAttack();
    }
    else if (num == 2)
    {
        Attack02(selNum.selUser, selNum.selNpc, user_mon, devmon);
        NpcAttack();
    }
    else
    {

    }
}
int BattleMonSel(int num) // 
{   
    int i;
    int selNum = 0;
    while(1)
    {
        if(num > 1)
        {   
            system("clear");
            for(i=0; i<num; i++)
            {
                printf("%d) %s HP:%d/%d MP:%d/%d DMG:%d SDMG:%d \n", i+1,user_mon[i].name,user_mon[i].hp,user_mon[i].max_hp,user_mon[i].mp,user_mon[i].max_mp,user_mon[i].power,user_mon[i].sk_power);
            }
            printf("\n\n 몇 번 몬스터로 싸울까? : ");
            scanf("%d",&selNum);
            selNum -= 1;
            if(user_mon[selNum].hp == 0)
            {
                printf("\n체력이 없습니다. 다시 골라주세요\n");
                sleep(1);
            }
            else if(selNum >= CountMon(user_mon) || selNum < 0)
            {
                printf("잘못된 입력!!\n");
                sleep(1);
                continue;
            }
            else
                break;
        }
        else
        {
            selNum = 0;
            break;
        }
    }
    return selNum;
}
void BattleVictory(void)
{
    int choice;
    int i;
    PrintVic(devmon[selNum.selNpc].iNum);
    printf("내 개발몬으로 영입할까? 1)예 2)아니오 :");
    scanf("%d", &choice);
    if(choice == 1)
    {
        while(1)
        {
            if(CountMon(user_mon) == 3)
            {
                int selMon;
                system("clear");
                for(i=0; i<CountMon(user_mon); i++)
                { 
                    printf("   %d) %s HP:%d/%d MP:%d/%d DMG:%d SDMG:%d \n", i+1,user_mon[i].name,user_mon[i].hp,user_mon[i].max_hp,user_mon[i].mp,user_mon[i].max_mp,user_mon[i].power,user_mon[i].sk_power);
                }
                printf("\n\n 몇 번 몬스터를 교체할까? : ");
                scanf("%d", &selMon);
                selMon -= 1;
                if(selMon == 0)
                {
                    printf("\n\n시작 개발몬은 변경 불가능합니다.\n");
                    sleep(1);
                }
                else
                {
                    AddTeam(user_mon, devmon, selMon);
                    AddTeam(devmon, user_mon, selNum.selNpc);
                    user_mon[CountMon(user_mon)-1].hp = user_mon[CountMon(user_mon)-1].max_hp;
                    devmon[CountMon(devmon)-1].hp = devmon[CountMon(devmon)-1].max_hp;
                    system("clear");
                    for(i=0; i<CountMon(user_mon); i++)
                    { 
                        printf("   %d) %s HP:%d/%d MP:%d/%d DMG:%d SDMG:%d \n", i+1,user_mon[i].name,user_mon[i].hp,user_mon[i].max_hp,user_mon[i].mp,user_mon[i].max_mp,user_mon[i].power,user_mon[i].sk_power);
                    }
                    printf("\n\n동료 교체 성공! 버려진 개발몬은 애타게 나를 바라봅니다....\n");
                    sleep(2);
                    break;
                }      
            }
            else
            {
                AddTeam(devmon, user_mon, selNum.selNpc);
                system("clear");
                user_mon[CountMon(user_mon)-1].hp = user_mon[CountMon(user_mon)-1].max_hp;
                for(i=0; i<CountMon(user_mon); i++)
                {
                    printf("\n   %d) %s HP:%d/%d MP:%d/%d DMG:%d SDMG:%d \n", i+1,user_mon[i].name,user_mon[i].hp,user_mon[i].max_hp,user_mon[i].mp,user_mon[i].max_mp,user_mon[i].power,user_mon[i].sk_power);
                }
                printf("\n\n동료 영입 성공!\n");
                sleep(2);
                break;
            }
        }
    }
    else
    {
        devmon[selNum.selNpc].hp = devmon[selNum.selNpc].max_hp;
        devmon[selNum.selNpc].mp = devmon[selNum.selNpc].max_mp;
        return;
    }
}


void BattleCore(void)
{
    system("clear");
    selNum.selNpc = rand() % CountMon(devmon);
    int userNum = CountMon(user_mon);
    int selAct;
    int btQuit = 1;
    int cnt = 1;
    int event;
    
    while(btQuit == 1)
    {   
        selNum.selUser = BattleMonSel(userNum);
        while(cnt > 0)
        {
            UpdateHp();
            if(userS.total_hp == 0)
            {
                printf("\n\n\n\n     전투에서 패배했다...\n");
                sleep(2);
                btQuit = 0;
                break;
            }
            else if(user_mon[selNum.selUser].hp == 0)
                break;
            else if(devmon[selNum.selNpc].hp == 0)
            {
                system("clear");
                printf("\n\n\n\n     전투에서 승리했다..!!!\n");
                sleep(2);
                BattleVictory();
                btQuit = 0;
                break;
            }
            PrintBattle(devmon[selNum.selNpc].iNum);
            if(cnt == 1)
                printf("야생의 %s이(가) 나타났다!\n", devmon[selNum.selNpc].name);
            printf("\n 어떻게 할까? \n");
            printf("1)일반 공격  2)특수 공격  3)아이템 창  4)도망가기 : ");
            scanf("%d", &selAct);
            if(selAct < 1 || selAct > 4)
            {
                printf("잘못된 입력!!\n");
                sleep(1);
                continue;
            }
            else if(selAct == 2 && user_mon[selNum.selUser].mp < 50)
            {
                printf("마나가 모자랍니다.\n");
                sleep(1);
                continue;
            }
            else if(selAct == 4)
            {
                event = rand() % 100 + 1;
                if(event <= 10)
                {
                    
                    printf("\n\n ***** 탈출 성공! *****\n\n");
                    sleep(1);
                    btQuit = 0;
                    break;
                }
                else
                {
                    printf("\n\n ***** 탈출 실패... *****\n");
                    printf(" ***** 턴 넘어감 *****\n\n");
                    sleep(1);
                    NpcAttack();
                    continue;
                }
            }
            BattleActSel(selAct);
            cnt++;
        }
    }
      
}






// void PrintBattle()
// {
//     while(fgets(monFace.gnt, 30, monFace.img[user_mon[selNum.selUser].iNum]) != 0)
//     {
//         printf(monFace.gnt);
//     }
//     printf("-----------------------------------------------------\n");
//     printf("(%s)%s HP: %d/%d  MP: %d/%d  DMG: %d\n", userS.name,user_mon[selNum.selUser].name, user_mon[selNum.selUser].hp,user_mon[selNum.selUser].max_hp,user_mon[selNum.selUser].mp,user_mon[selNum.selUser].max_mp,user_mon[selNum.selUser].power);
//     printf("-----------------------------------------------------\n");
//     while(fgets(monFace.gnt, 30, monFace.img[mon[selNum.selNpc].iNum]) != 0)
//     {
//         printf(monFace.gnt);
//     }
//     printf("-----------------------------------------------------\n");
//     printf("(NPC)%s HP: %d/%d  MP: %d/%d  DMG: %d\n", mon[selNum.selNpc].name, mon[selNum.selNpc].hp,mon[selNum.selNpc].max_hp, mon[selNum.selNpc].mp,mon[selNum.selNpc].max_mp, mon[selNum.selNpc].power);
//     printf("-----------------------------------------------------\n");
// }



// 선택창
// "어떤 행동을 하시겠습니까? 1) 공격 2) 특수공격 3) 아이템사용 4)도망가기 "

// 1번 입력시
// 내 개발몬의 공격력만큼 상대 hp를 깎고
// 그 수치를 출력함
// 상대방도 특정 행동 하고
// 결과 수치 출력
// 엔터누르면 다시 선택창으로

// 2번 입력시
// 내 개발몬의 특공 만큼 내 mp 감소 상대 hp를 깍고
// 그 수치를 출력함
// 엔터 누르면 다시 선택창으로

// 3번입력시
// 내가 소유한 아이템 리스트 보여주고
// ("어떤 아이템을 고르시겠습니까? (숫자로 입력)")
// 숫자 입력하면 그 아이템 사라지면서 효과발동
// 내턴은 넘어가고 상대방이 행동

// 4번 입력시
// 10% 확률로 전투에서 벗어나서 함수 종료

// 매번 내가 행동을 선택할 때마다 상대방의 행동도 정해진다
// 내 행동이 이루어진 다음 상대방의 행동이 진행된다
// 상대방의 체력이 0이 되면 전투 승리 후 종료
// 내 체력이 0이되면 함수나가고 게임 종료


// 궁금한점...
// 매개변수로 뭘 받아와야 할까? 일단 받아와야겠지?
// 상대 몬스터가 결정되는 시점은? 이 함수 밖에서 정해지고 들어오는건가
// 함수 초기에 정하는 건가? 밖에서 정해지고 그걸 매개변수로 받나?
// 상대 방의 행동은? 공격, 특수공격만 하나? 도망가기도 할까?


// 내 아이템 리스트 -> 실제로 데이터가 바뀌어야함
// 그 아이템의 효과는 따로 함수로 만들어놓고 사용시 작동되게 해야되나?
// 아이템별로 함수를 따로 만들어야 되겠군..?
// 근데 아이템이 배열에 들어가는 순서는 랜덤인데?
// 그 배열에서 사용자의 숫자 입력만으로 어떤 아이템인지 파악하게 할 수 있나?
// 그 아이템 리스트도 계속 변할테니 반복문으로 만들어서 한줄 한줄 출력해야 되겠구나!!


// 승리 후에 팀 영입...
// 몬스터를 팀으로 만드시겠습니까?

// 상대 몬스터 그림, 정보

// 내 몬스터 리스트
// y or n
// y일 경우 내 몬스터 마리수를 확인해서 최대 수이면 교체할 몬스터 선택하게
// 선택한 몬스터는 다시 전체 몬스터 배열로 들어가야함... (렙업 다르게 하면 안되겠네?)


// 

