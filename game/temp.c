#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define NUM 5 // 개발몬 숫자

//-----------------------------------------------------------------------------구조체 정의
typedef struct // 개발몬 정보
{
	char* name;
	int iNum; //고유 번호(인덱스 넘버)
    char* pName;
    char* skpName;
	int hp, max_hp, mp, max_mp;
	int power, sk_power;
} DevMon;
DevMon init_mon = {"0",-1, };
DevMon devmon[NUM+1] = { {"수비니",0,"코드검사","과제내주기"},{"승버미",1,"코드공격","무한질문"} ,{"광서니",2,"교재로후려치기","기습질문"},
{"뀨비",3,"무한질문","뀨등어소환"}, {"보노보노",4,"변수공격","구조체포인터"}, {"0",-1}}; //맨 끝 버퍼

typedef struct //유저 정보 저장
{
	char name[20];
	char pre_pos; //유저 기존 위치 저장
	int level, xp, hour;
	int xpos, ypos; 
	int total_hp, max_hp; 
} UserInfo;
UserInfo userS = { "",'s',1,0,0,0,16,0,0};
DevMon user_mon[4] = { {"0",-1,},{"0",-1,} ,{"0",-1,}, {"0",-1} };

typedef struct //아이템
{
    char name[20];
    int iNum;
    int fig; //아이템 수치
    char* script;
    int count;
} Item;
Item init_item = {"0",-1,};
Item mash[4] = {{"얼음",0,0,"상대방의 턴을 한턴 넘긴다",},{"주먹밥",1,100,"체력 100 회복",},{"커피",2,50,"마나 50 회복",},{"0",-1}}; 
Item user_item[6]= { {"0",-1,},{"0",-1,} ,{"0",-1,},{"0",-1,} ,{"0",-1,} ,{"0",-1}};

typedef struct //이미지 출력
{
    // FILE* img[NUM];char arr[100];
    char imgarr[10000];
    FILE * imgname[];
}ImgList;
ImgList character;
//-----------------------------------------------임시 구조체
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

//-----------------------------------------------------------------------------맵 설정
//맵 구현
char map[25][25] =
{
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', 's', '1', '1', '1', '1', '1', '1', '1', '1'}, //1은 벽
{'1', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', '1', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'}, //0은 복도
{'1', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', '1', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'}, //c가 교실 - 생산
{'1', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', '2', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'}, //d가 교실 - 드론
{'1', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', '1', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'}, //e가 교실 - iot
{'1', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', '1', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'}, //h가 급식실
{'1', '1', '1', '1', '1', '2', '1', '1', '1', '1', '1', '2', '1', '1', '1', '0', '0', '0', '2', 'd', 'd', 'd', 'd', 'd', '1'}, //p가 교수실
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'}, //2이 일반문
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'}, //3가 교수실 문
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'}, //q가 구급차
{'1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'}, //s가 시작위치
{'1', 'h', 'h', 'h', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'},
{'1', 'h', 'q', 'h', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2', 'd', 'd', 'd', 'd', 'd', '1'},
{'1', 'h', 'h', 'h', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', 'd', 'd', 'd', 'd', 'd', '1'},
{'1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '0', '0', '0', '0', '1', '1', '2', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '1', 'e', 'e', 'e', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '1', 'e', 'e', 'e', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '1', 'e', 'e', 'e', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '1', '1', '1', '2', '1', '1', '1', 'e', 'e', 'e', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1'},
{'1', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', '2', '0', '0', '0', '0', '0', '0', '0', '1', 'p', 'p', 'p', 'p', '1'},
{'1', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', '1', '0', '0', '0', '0', '0', '0', '0', '1', 'p', 'p', 'p', 'p', '1'},
{'1', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', '1', '0', '0', '0', '0', '0', '0', '0', '1', 'p', 'p', 'p', 'p', '1'},
{'1', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', '1', '0', '0', '0', '0', '0', '0', '0', '3', 'p', 'p', 'p', 'p', '1'},
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

//맵 출력 함수
void PrintingMap(void);

//맵 이동 함수
int Move(int user);

//랜덤 스폰 함수 -> 아이템 랜덤 스폰으로 이용해도 될 듯?
void RandomSpawn(void);

//리스폰 함수(죽으면 구급차로 스폰)
void ReSpawn(void);
//-----------------------------------------------------------------------------Item 설정
//아이템 랜덤 스폰(맵에 스폰될 아이템 개수 입력받음)
void ItemSpawn(int inum)
{
    int xpos = rand() % 25, ypos = rand() % 25;
    int event;
    for(int i=0;i<inum;i++)
    {
        event = rand()%3;
        while (map[xpos][ypos] != '0') //복도(길)에만 배치 되도록
        {
            xpos = rand() % 25; ypos = rand() % 25;
        }
        switch (event)
        {
        case 0:
            map[xpos][ypos] = 'i'; //얼음
            break;
        case 1:
            map[xpos][ypos] = 'r'; //밥
            break;
        case 2:
            map[xpos][ypos] = 'f'; //빵
            break;
        }
    }
}

//아이템 갯수 세는 함수
int CountItem(Item* item)
{
    int idx = 0;
    while(item[idx].iNum!=-1) idx++; //개발몬 수 세기
    return idx;
}

//아이템 get(userS.pre_pos값 입력 받음 혹은 아이템 지정 문자)
void GetItem(char map)
{
    int idx = CountItem(user_item);
    if(idx == 5) 
    {
        printf("아이템 창이 꽉찼습니다. \n");
        return;
    }
    else
    {
        switch (map)
        {
        case 'i':
            user_item[idx] = mash[0];
            break;
        case 'r':
            user_item[idx] = mash[1];
            break;
        case 'f':
            user_item[idx] = mash[2];
            break;
        }
        printf("%s를 획득했다! \n",user_item[idx].name);
    }
}
//-----------------------------------------------------------------------------DevMon 설정
//개발몬 수 세는 함수(배열 이름 입력받음)
int CountMon(DevMon* mon);

//팀 영입 함수(mon1->mon2) idx=mon1인덱스
void AddTeam(DevMon* mon1, DevMon* mon2, int idx);

//유저 hp정보 갱신
void UpdateHp(void);

//Hp 전체 회복 (배열 이름 입력 받음)
void HealALLHp(DevMon* mon);

//mon리스트의 idx번 멤버 amount만큼 회복
void HealHp(DevMon* mon, int amount, int idx);

//mon리스트의 idx번 개발몬 Hp amount 만큼 깎임
void MinusHp(DevMon* mon, int idx, int amount);

//mon리스트 전체 개발몬 Hp amount 만큼 깎일때
void MinusALLHp(DevMon* mon, int amount);

//레벨업 함수
void LevelUp(DevMon* mon)
{
    printf("레벨업을 했다!!! \n");
    
    for (int i = 0;i < CountMon(mon);i++)
    {
        mon[i].max_hp += 100; mon[i].max_mp += 50;
        mon[i].power += 20; mon[i].sk_power += 20;
    } HealALLHp(mon);
    if(mon==user_mon)
    {
        userS.level++; userS.xp = 0;
        UpdateHp();
    }
}

//mon 리스트 출력
void PrintingMon(DevMon* mon);

//개발몬 선택(mon 리스트에서 선택한 멤버의 인덱스 반환)
int ChooseMon(DevMon* mon);

//개발몬 초기 능력치 설정
void init_play(void);

//---------------------------------------------------------------------------전투, 퀴즈

//퀴즈단 지갑 털기 //수식 테스트
void QuestionMon(int cnum); //클래스 위치 받기(생산: 0, 드론: 1, iot: 2)

//================================================================================임시
void ClearBuffer(void)
{
    while (getchar() != '\n');
}

void PrintBattle(int iNum) // 몬스터 고유번호 받아오기
{
    monFace.img[0] = fopen("img/mon1.txt","rt");
    monFace.img[1] = fopen("img/mon2.txt","rt");
    monFace.img[2] = fopen("img/mon3.txt","rt");
    monFace.img[3] = fopen("img/mon4.txt","rt");
    monFace.img[4] = fopen("img/mon5.txt","rt");
    system("clear");
    while(fgets(monFace.gnt, 50, monFace.img[iNum]) != 0) 
    {
        printf("%s", monFace.gnt);
    }
    fclose(monFace.img[iNum]);
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
    while(fgets(monFace.gnt, 50, monFace.img[iNum]) != 0) 
    {
        printf("%s", monFace.gnt);
    }
    fclose(monFace.img[iNum]);
    printf("---------------------------------------------\n");
    printf("%s HP:%d  MP:%d  DMG:%d SDMG:%d\n", devmon[selNum.selNpc].name, devmon[selNum.selNpc].max_hp, devmon[selNum.selNpc].max_mp, devmon[selNum.selNpc].power,devmon[selNum.selNpc].sk_power);
    printf("---------------------------------------------\n");
}

void PrintItem(void) // 아이템 리스트 출력
{
    system("clear");
    printf("\n\n");
    int i;
    for(i=0; i<CountItem(user_item); i++){
        printf("%d번 %s : %s \n", i+1, user_item[i].name, user_item[i].script);
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
                    printf("\n\n시작 개발몬은 변경 불가능합니다. \n");
                    sleep(1);
                }
                else
                {
                    AddTeam(user_mon, devmon, selMon);
                    AddTeam(devmon, user_mon, selNum.selNpc);
                    user_mon[CountMon(user_mon)-1].hp = user_mon[CountMon(user_mon)-1].max_hp;
                    devmon[CountMon(devmon)-1].hp = devmon[CountMon(devmon)-1].max_hp;
                    printf("\n동료 교체 성공! 버려진 개발몬은 애타게 나를 바라봅니다....\n");
                    sleep(2);
                    system("clear");
                    for(i=0; i<CountMon(user_mon); i++)
                    { 
                        printf("   %d) %s HP:%d/%d MP:%d/%d DMG:%d SDMG:%d \n", i+1,user_mon[i].name,user_mon[i].hp,user_mon[i].max_hp,user_mon[i].mp,user_mon[i].max_mp,user_mon[i].power,user_mon[i].sk_power);
                    }
                    printf("\n동료 영입 성공! \n");
                    printf("\n변경된 내 개발몬 목록 \n");
                    sleep(1);
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
                printf("\n동료 영입 성공! \n");
                printf("\n변경된 내 개발몬 목록 \n");
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




void ItemIce(void) // 아이템 1번 턴넘기기
{
    printf("%s 아이템 사용!! %s\n\n", mash[0].name, mash[0].script);
    mash[0].count = 1;
    sleep(2);
}

void ItemHpUp(void) // 아이템 2번 회복포션
{
    printf("%s 아이템 사용!! %s \n\n", mash[1].name, mash[1].script);
    user_mon[selNum.selUser].hp += mash[1].fig;
    if (user_mon[selNum.selUser].hp > user_mon[selNum.selUser].max_hp)
        user_mon[selNum.selUser].hp = user_mon[selNum.selUser].max_hp;
    sleep(2);
    if (mash[0].count == 1){
            mash[0].count = 0;
            PrintBattle(devmon[selNum.selNpc].iNum);
            printf("\n\n %s 얼음효과!! 공격 불가능 \n", devmon[selNum.selNpc].name);
            sleep(1);
    }
    else{
        NpcAttack();
    }
}

void ItemMpUp(void) // 아이템 3번 마나회복포션
{
    printf("%s 아이템 사용!! %s \n\n", mash[2].name, mash[2].script);
    user_mon[selNum.selUser].mp += mash[2].fig;
    if (user_mon[selNum.selUser].mp > user_mon[selNum.selUser].max_mp)
        user_mon[selNum.selUser].mp = user_mon[selNum.selUser].max_mp;
    sleep(2);
    if (mash[0].count == 1){
            mash[0].count = 0;
            PrintBattle(devmon[selNum.selNpc].iNum);
            printf("\n\n %s 얼음효과!! 공격 불가능 \n", devmon[selNum.selNpc].name);
            sleep(1);
    }
    else{
        NpcAttack();
    }
}

void ItemRemove(int idx) // 유저 리스트에서 사용한 아이템 제거
{
    for (int i = idx;i < CountItem(user_item) - 1;i++)
    {
        user_item[i] = user_item[i + 1];
        // mon1[i].iNum--;
    }
    user_item[CountItem(user_item) - 1] = init_item;
}
void ItemUse(void) // 아이템 사용시 발동되는 함수
{
    int cho;
    int i;
    while(1){
        PrintItem();
        fputs("몇번 아이템을 고르시겠습니까? : ",stdout);
        scanf("%d", &cho);
        cho -= 1;
        if(cho < 0 || cho > CountItem(user_item)){
            puts("잘못된 입력!! 정확히 고르세요");
            sleep(1);
            continue;
        }
        else if(user_item[cho].iNum == 0)
        {
            ItemIce();
            ItemRemove(cho);
            break;
        }
        else if(user_item[cho].iNum == 1)
        {
            ItemHpUp();
            ItemRemove(cho);
            break;
        }
        else if(user_item[cho].iNum == 2)
        {
            ItemMpUp();
            ItemRemove(cho);
            break;
        }
    }
}


    
void BattleActSel(int num)   // 얼음효과 아이템 발동 추가
{
    if(num == 1)
    {
        Attack01(selNum.selUser, selNum.selNpc, user_mon, devmon);
        if (mash[0].count == 1){
            mash[0].count = 0;
            PrintBattle(devmon[selNum.selNpc].iNum);
            printf("\n\n %s 얼음효과!! 공격 불가능 \n", devmon[selNum.selNpc].name);
            sleep(1);
        }
        else{
            NpcAttack();
        }
        
    }
    else if (num == 2)
    {
        Attack02(selNum.selUser, selNum.selNpc, user_mon, devmon);
        if (mash[0].count == 1){
            mash[0].count = 0;
            PrintBattle(devmon[selNum.selNpc].iNum);
            printf("\n\n %s 얼음효과!! 공격 불가능 \n", devmon[selNum.selNpc].name);
            sleep(1);
        }
        else{
            NpcAttack();
        }
    }
    else if (num == 3) // 아이템 사용 기능 추가
    {
        ItemUse();
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
                printf("전투에서 패배했다...\n");
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
            else if(selAct == 3 && CountItem(user_item) == 0){ // 아이템 갯수 확인 기능 추가
                printf("아이템이 없습니다 정신차리세요.\n");
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
    UpdateHp();   
}


//--------------------------------------------------------------------------ㅡmain 함수
int main(void)
{
    srand((unsigned int)time(NULL));
    int user; //유저 입력 인자
    int idx, event; // 확률 변수
    int choose=0;



    init_play(); //개발몬 능력치 설정
    devmon[0].power=300; //치트키

    // printf("시작화면 \n");
    // FILE * start = NULL;
    // start = fopen("txt/start.txt", "r");
    // fread(character.imgarr, 1, 227, start);
    // printf("%s\n", character.imgarr);
    // fclose(start);
 
    printf("당신의 이름은? >");
    scanf("%s", userS.name); 
    printf("%s님 환영합니다. \n", userS.name);
    sleep(2);
    
    //초기 개발몬 선택
    idx = ChooseMon(devmon);
    AddTeam(devmon, user_mon, idx);
    system("clear");
    // printf("개발몬 얼굴 출력 \n");
    // if (idx == 0)
    // {
    //     FILE * devmon00 = NULL;
    //     devmon00 = fopen("txt/devmon00.txt", "r");
    //     fread(character.imgarr, 1, 9999, devmon00);
    //     printf("%s\n", character.imgarr);
    //     fclose(devmon00);
    // }

    // else if (idx == 1)
    // {
    //     FILE * devmon01 = NULL;
    //     devmon01 = fopen("txt/devmon01.txt", "r");
    //     fread(character.imgarr, 1, 9999, devmon01);
    //     printf("%s\n", character.imgarr);
    //     fclose(devmon01);

    // }

    // else if (idx == 2)
    // {
    //     FILE * devmon02 = NULL;
    //     devmon02 = fopen("txt/devmon02.txt", "r");
    //     fread(character.imgarr, 1, 9999, devmon02);
    //     printf("%s\n", character.imgarr);
    //     fclose(devmon02);
    // }
    printf("%s과 함께합니다. 개발원에 입장합니다. \n ", user_mon[0].name);
    sleep(2);

    ItemSpawn(5);
    map[userS.xpos][userS.ypos]='X';
    while (1)
    {
        if (userS.total_hp == 0) ReSpawn();
        
        // while(getchar()!='\n');
        system("clear");
        PrintingMap(); //맵 출력
        if(userS.hour==900)
        {
            map[23][19]='2'; printf("(공지)교수실 문이 열렸습니다. \n");
        } 
        printf("%s %s %s\n",user_item[0].name,user_item[1].name,user_item[2].name);

        printf("위(w) 왼쪽(a) 아래(s) 오른쪽(d) >");

        // scanf("%s", user); 
        user=getchar();
        // fgets(user,sizeof(user),stdin);
        printf("\n");
        while(getchar()!='\n');

        //입력값 검사
        if (user != 'w' && user != 'a' && user != 's' && user != 'd') continue;
        if(map[0][16]=='X'&&user=='w') continue;

        //플레이어 이동
        choose = Move(user); 
        if(choose == 1) continue; 
        userS.hour++; event = rand() % 100;

        if(userS.pre_pos == 's')
        {
            printf("게임을 종료하시겠습니까? (y/n)\n");
            scanf("%d",&user);
            if(user=='y') break;
            else continue;
        }
        //복도, 길('0') 이벤트 (event가 0~29일때 발생)
        else if (userS.pre_pos == '0' && event < 5)
        {
            printf("배틀이 진행됩니다. \n");
            // FILE * battlescene = NULL;
            // memset(character.imgarr, 0, sizeof(character.imgarr));
            // battlescene = fopen("txt/battlescene.txt", "r");
            // fread(character.imgarr, 1, 9999, battlescene);
            // printf("%s\n", character.imgarr);
            // fclose(battlescene);
            sleep(1);

            BattleCore();
        }

        //교실('c') 이벤트 (event가 0~19일때 발생) //퀴즈단 만나 퀴즈 풀기
        else if (userS.pre_pos == 'c' && event < 20)
        {
            QuestionMon(0); //생산 교실 이벤트
             sleep(2);
        }
        else if (userS.pre_pos == 'd' && event < 20)
        {
            QuestionMon(1); //드론 교실 이벤트
            sleep(2);
        }
        else if (userS.pre_pos == 'e' && event < 20)
        {
            QuestionMon(2); //iot 교실 이벤트
            sleep(2);
        }

        else if(userS.pre_pos=='i'||userS.pre_pos=='r'||userS.pre_pos=='f')
        {
            GetItem(userS.pre_pos);
            userS.pre_pos = '0';
            sleep(2);
        }

        //급식실('h')
        else if (userS.pre_pos == 'q')
        {
            HealALLHp(user_mon);
            printf("체력이 모두 회복됩니다. \n");
            printf("잠시후 랜덤 스폰됩니다. \n");
            sleep(2);
            RandomSpawn();
        }

        //교수실('p')
        else if (userS.pre_pos == 'p')
        {
            printf("교수실에 들어왔다! \n"); //교수실 이벤트 발생
            sleep(2);
        }
    }
    return 0;
}

//----------------------------------------------------------------------함수 리스트
//맵 출력 함수
void PrintingMap(void)
{
    int x = 0, y = 0;

    printf("-----------------------------------------------------------------\n");
    printf("user:%s total_HP:%d Hour:%d Level:%d Xp:", userS.name, userS.total_hp, userS.hour, userS.level);
    for(x=0;x<10-userS.xp/50;x++) printf("O "); //경험치 구현( 50당 한칸)
    for (x = 0;x < userS.xp / 50;x++) printf("X ");
    printf("\n");
    printf("-----------------------------------------------------------------\n");

   for(x = 0; x < 25; x++)
    {
        for(y = 0; y < 25; y++)
        {   
            if (map[x][y] == '0')
                printf("⬜ ");
            else if (map[x][y] == '1')
                printf("🧱 ");
            else if (map[x][y] == '2')
                printf("🚪 ");
            else if (map[x][y] == '3')
                printf("🔒 ");
            else if (map[x][y] == 'c')
                printf("🤖 ");
            else if (map[x][y] == 'd')
                printf("🛩️  ");
            else if (map[x][y] == 'e')
                printf("💻 ");
            else if (map[x][y] == 'h')
                printf("🏥 ");
            else if (map[x][y] == 'p')
                printf("👿 ");
            else if (map[x][y] == 'q')
                printf("🚑 ");
            else if (map[x][y] == 'X')
                printf("🫠  ");
            else if (map[x][y] == 's') 
                printf("🏫 ");
            else if (map[x][y] == 'i')
                printf("🧊 ");
            else if (map[x][y] == 'r')
                printf("🍙 ");
            else if (map[x][y] == 'f')
                printf("☕ ");
        }
        printf("\n");
    }
}

//맵 이동 함수
int Move(int user)
{
    int choose=0;
    map[userS.xpos][userS.ypos]=userS.pre_pos;
    if(user=='w')
    {
        userS.xpos--;
        if(map[userS.xpos][userS.ypos]=='1')
        {
            userS.xpos++; choose=1;
        }
    }
    else if(user=='a')
    {
        userS.ypos--;
        if(map[userS.xpos][userS.ypos]=='1')
        {
            userS.ypos++; choose=1;
        }
    }
    else if(user=='s')
    {
        userS.xpos++;
        if(map[userS.xpos][userS.ypos]=='1')
        {
            userS.xpos--; choose=1;
        }
    }
    else if(user=='d')
    {
        userS.ypos++;
        if(map[userS.xpos][userS.ypos]=='1'||map[userS.xpos][userS.ypos]=='3')
        {
            userS.ypos--; choose=1;
        }
    }
    userS.pre_pos = map[userS.xpos][userS.ypos];
    map[userS.xpos][userS.ypos] = 'X';
    return choose;
}

//랜덤 스폰 함수 -> 아이템 랜덤 스폰으로 이용해도 될 듯?
void RandomSpawn(void)
{
    map[userS.xpos][userS.ypos] = userS.pre_pos;
    userS.xpos = rand() % 25; userS.ypos = rand() % 25;
    while (map[userS.xpos][userS.ypos] != '0') //복도(길)에만 배치 되도록
    {
        userS.xpos = rand() % 25; userS.ypos = rand() % 25;
    }
    userS.pre_pos = '0';
    map[userS.xpos][userS.ypos] = 'X';
}

//리스폰 함수(죽으면 구급차로 스폰)
void ReSpawn(void)
{
    system("clear");
    printf("구급차 이미지 출력 \n");
    printf("체력이 모두 소진되었습니다. 구급차로 이동합니다. \n");
    map[userS.xpos][userS.ypos] = userS.pre_pos;
    userS.pre_pos = 'q';
    userS.xpos = 12; userS.ypos = 2; //구급차 위치
    map[userS.xpos][userS.ypos] = 'X';
    HealALLHp(user_mon);//hp 전체 회복
    sleep(3);
}

//개발몬 수 세는 함수(배열 이름 입력받음)
int CountMon(DevMon* mon)
{
    int idx = 0;
    while(mon[idx].iNum!=-1) idx++; //개발몬 수 세기
    return idx;
}

//팀 영입 함수(mon1->mon2) idx=mon1인덱스
void AddTeam(DevMon* mon1, DevMon* mon2, int idx)
{
    //mon1의 idx번째 멤버를 mon2에 추가
    int uidx = CountMon(mon2); //mon2에 추가될 자리 인덱스

    mon2[uidx] = mon1[idx]; //mon1의 idx번째 개발몬 정보 mon2에 복사
    // mon2[uidx].iNum = uidx; //고유번호 설정

    //빠져나간 멤버 리스트에서 제거 ->배열 요소 제거 함수로 따로 구현해도 될듯!
    for (int i = idx;i < CountMon(mon1) - 1;i++)
    {
        mon1[i] = mon1[i + 1];
        // mon1[i].iNum--;
    }
    mon1[CountMon(mon1) - 1] = init_mon; //빈자리 초기화

    UpdateHp();
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

//Hp 전체 회복 (배열 이름 입력 받음)
void HealALLHp(DevMon* mon)
{
    for (int i = 0;i < CountMon(mon);i++) mon[i].hp = mon[i].max_hp;
    if (mon == user_mon) userS.total_hp = userS.max_hp; //유저 개발몬일때 정보 갱신
}

//mon리스트의 idx번 멤버 amount만큼 회복
void HealHp(DevMon* mon, int amount, int idx)
{
    mon[idx].hp += amount;
    if (mon == user_mon) userS.total_hp += amount;
}

//mon리스트의 idx번 개발몬 Hp amount 만큼 깎임
void MinusHp(DevMon* mon, int idx, int amount)
{
    mon[idx].hp -= amount;
    if (mon == user_mon) userS.total_hp -= amount;
}

//mon리스트 전체 개발몬 Hp amount 만큼 깎일때
void MinusALLHp(DevMon* mon, int amount)
{
    if (userS.total_hp <= 1)
    {
        userS.total_hp = 0; return;
    }
    int idx = CountMon(mon);
    for (int i = 0;i < idx;i++)
    {
        MinusHp(mon, i, amount);
    }
}

//개발몬 전투 함수
//void BattleMon(void);

//퀴즈단 지갑 털기 //수식 테스트
void QuestionMon(int cnum) //클래스 위치 받기(생산: 0, 드론: 1, iot: 2)
{
    srand((unsigned int)time(NULL));
    //퀴즈단: iot-리북녘, 드론-최하문, 생산-류청걸
    char* teacher[3] = { "류청걸","최하문","리북녘" };
    //산수 문제로!
    int num1, num2, cal;
    int answer, qcount = 0;
    int correct=0;

    printf("%s 교수님을 마주쳤다! \n", teacher[cnum]);

    while (qcount < 3)
    {
        sleep(1);
        system("clear");
        PrintingMap(); //-> 교수 얼굴 출력으로 바꿀것
        num1 = rand() % 100 + 1, num2 = rand() % 100 + 1;
        cal = rand()%3;

        printf("%d번째 문제를 내겠다! \n", qcount + 1);

        switch(cal)
        {
            case 0:
                printf("%d + %d = ?\b", num1, num2);
                scanf("%d", &answer); 
                if(answer==num1+num2) correct=1;
                break;
            case 1:
                printf("%d - %d = ?\b", num1, num2);
                scanf("%d", &answer); 
                if(answer==num1-num2) correct=1;
                break;
            case 2:
                printf("%d * %d = ?\b", num1, num2);
                scanf("%d", &answer); 
                if(answer==num1*num2) correct=1;
                break;
        }

        
        //퀴즈 맞추면 하나당 경험치 획득
        if (correct==1)
        {
            printf("맞췄다!! \n");
            userS.xp += 50; qcount++;
            printf("경험치가 50만큼 올랐습니다. \n");
            if (userS.xp > 500) //xp 500당 레벨업 -->나중에 함수 만들어야함
            {
                LevelUp(user_mon);
                LevelUp(devmon);
            }
            
            continue;
        }
        else //틀리면 hp -50%
        {
            printf("틀렸어!!! 공부 다시 하고 와!\n");
            MinusALLHp(user_mon, (userS.total_hp * 0.5) / CountMon(user_mon));
            return; //함수 종료(플레이어 위치 변화 없음)
        }
    }
    //다 맞췄을 시 Hp회복, 
    if (qcount == 3)
    {
        HealALLHp(user_mon);
        printf("체력이 모두 회복되었다! \n");
    }
}

//mon 리스트 출력
void PrintingMon(DevMon* mon)
{
    // 각 개발몬의 얼굴/이름/능력치 출력(임시: 이름과 능력치 리스트로 출력)
    for (int i = 0;i < CountMon(mon);i++) //개발몬 리스트 출력
    {
        printf("%d)", i + 1);
        printf("name: %s hp: %d mp: %d ", mon[i].name, mon[i].hp, mon[i].mp);
        printf("power: %d sk_power: %d\n", mon[i].power, mon[i].sk_power);
    }
}

//개발몬 선택(mon 리스트에서 선택한 멤버의 인덱스 반환)
int ChooseMon(DevMon* mon)
{
    int choose = 0, idx = 0; //선택 트리거, 인덱스 넘버
    char user[2];

    while (choose != 1)
    {
        system("clear");

        //idx번 개발몬의 얼굴, 이름, 능력치를 출력해야함
        printf("함께할 개발몬을 선택해주세요> \n");
        // printf("%d번 개발몬 얼굴 \n",idx); //이미지 들어갈 곳
        // if (idx == 0)
        // {
        //     FILE * devmon00 = NULL;
        //     devmon00 = fopen("txt/devmon00.txt", "r");
        //     fread(character.imgarr, 1, 9999, devmon00);
        //     printf("%s\n", character.imgarr);
        //     memset(character.imgarr, 0, sizeof(character.imgarr));
        //     fclose(devmon00);
        // }
        // else if (idx == 1)
        // {
        //     FILE * devmon01 = NULL;
        //     devmon01 = fopen("txt/devmon01.txt", "r");
        //     fread(character.imgarr, 1, 9999, devmon01);
        //     printf("%s\n", character.imgarr);
        //     memset(character.imgarr, 0, sizeof(character.imgarr));
        //     fclose(devmon01);

        // }
        // else if (idx == 2)
        // {
        //     FILE * devmon02 = NULL;
        //     devmon02 = fopen("txt/devmon02.txt", "r");
        //     fread(character.imgarr, 1, 9999, devmon02);
        //     printf("%s\n", character.imgarr);
        //     memset(character.imgarr, 0, sizeof(character.imgarr));
        //     fclose(devmon02);
        // }

        printf("--------------------------------------------------------------------------------\n");
        printf("이름: %s\t HP: %-5d MP: %-5d 공격력: %-5d 특수공격력: %-5d \n",mon[idx].name,mon[idx].hp,mon[idx].mp,mon[idx].power,mon[idx].sk_power);
        printf("--------------------------------------------------------------------------------\n");
        printf("%s을 선택하시겠습니까?(선택: Y/다음으로: N): ",mon[idx].name); 

        while(getchar()!='\n');
        fgets(user,sizeof(user),stdin); // y-> 해당 개발몬 정보 저장 / n-> 다음 개발몬 정보 출력 

        //입력값 검사
        if (user[0] == 'y' || user[0] == 'Y') choose = 1;
        else if (user[0] == 'n' || user[0] == 'N') idx = (idx + 1) % CountMon(mon);
        else
        {
            printf("잘못된 입력입니다. 다시 선택해주세요. \n");
            // sleep(500);
            sleep(1);
            continue;
        }
    }
    return idx;
}

//개발몬 초기 능력치 설정
void init_play(void)
{
    for (int i = 0;i < NUM;i++)
    {
        devmon[i].hp = rand() % 100 + 200; devmon[i].max_hp = devmon[i].hp; //최소 몇 최대 몇
        devmon[i].mp = rand() % 50 + 50; devmon[i].max_mp = devmon[i].mp;
        devmon[i].power = rand() % 40 + 50;
        devmon[i].sk_power = rand() % 50 + 50;
    }
}