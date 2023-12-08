#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define NUM 5 //개발몬 숫자

typedef struct //개발몬 정보
{
	char* name;
	int iNum;
	char* pName; 
	char* skpName;
	int hp, max_hp, mp, max_mp, power, sk_power;
}DevMon;
DevMon init_mon = { "0",-1 };
DevMon devmon[NUM + 1] = { {"수비니",0,"코드검사","과제내주기"},{"승버미",1,"코드공격","무한질문"},{"광서니",2,"교재로후려치기","기습질문"},{"뀨비",3,"무한질문","뀨등어소환"},{"보노보노",4,"변수공격","구조체포인터던지기"},{"0",-1} }; //맨 끝 버퍼
DevMon boss[1] = {"개발원장",99,"런타임 에러","취업 실패 기우제",50000,50000,1000,1000,0,3000};  // 보스 정보 추가

typedef struct // 유저 정보
{
	char name[20];
	char pre_pos;
	int level, xp, hour;
	int xpos, ypos;
	int total_hp, max_hp;
}UserInfo;
UserInfo userS = { "",'s',1,0,0,0,16,0,0 };
DevMon user_mon[4] = { {"0",-1},{"0",-1},{"0",-1},{"0",-1} };

// typedef struct //아이템
// {
//     char name[20];
//     int iNum;
//     int fig; //아이템 수치
//     int count;
// } Item;
// Item mash[4] = { {"얼음",0,0,},{"주먹밥",1,100},{"커피",2,50},{"0",-1} };
// Item user_item[6] = { {"0",-1,},{"0",-1,} ,{"0",-1,},{"0",-1,} ,{"0",-1,} ,{"0",-1} };
typedef struct //아이템
{
    char name[20];
    int iNum;
    int fig; //아이템 수치  // 이게 필요없어지긴 했네요...
    char* script;
    int count;
} Item;
Item init_item = {"0",-1,};
Item mash[4] = {{"얼음",0,0,"상대방의 턴을 한턴 넘긴다",},{"주먹밥",1,100,"체력 50%% 회복",},{"커피",2,50,"마나 50%% 회복",},{"0",-1}}; 
Item user_item[6]= { {"0",-1,},{"0",-1,} ,{"0",-1,},{"0",-1,} ,{"0",-1,} ,{"0",-1}};

typedef struct //이미지 출력
{
	FILE* img[NUM];
	char imgarr[10000];
}ImgList;
ImgList character;

typedef struct //선택된 인덱스
{
	int selUser, selNpc;
}SelNum;
SelNum selNum;
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

//버퍼 비우기
void ClearBuffer(void);

//맵 출력 함수
void PrintingMap(void);

//맵 이동 함수(올바른 길 가면 0반환, 그 외 1 반환) -별도의 입력값 검사 필요 x
int Move(int user);

//랜덤 스폰 함수 (급식실에서 회복했을때 랜덤 이동)
void RandomSpawn(void);

//리스폰 함수(죽으면 구급차로 스폰)
void ReSpawn(void);

//아이템 랜덤 스폰(맵에 스폰될 아이템 개수 입력받음)
void ItemSpawn(int inum);

//아이템 갯수 세는 함수
int CountItem(Item* item);

//아이템 get(userS.pre_pos값 입력 받음 혹은 아이템 지정 문자)
void GetItem(char map);



//개발몬 수 세는 함수(배열 이름 입력받음)
int CountMon(DevMon* mon);

//팀 영입 함수(mon1->mon2) idx=mon1인덱스
void AddTeam(DevMon* mon1, DevMon* mon2, int idx);

//유저 hp정보 갱신
void UpdateHp(void);

//Hp 전체 회복 (배열 이름 입력 받음)
void HealALLHp(DevMon* mon);

//mon리스트의 idx번 멤버 amount만큼 회복
void HealHp(DevMon* mon, int idx,int amount);

//mon리스트의 idx번 개발몬 Hp amount 만큼 깎임
void MinusHp(DevMon* mon, int idx, int amount);

//mon리스트 전체 개발몬 Hp amount 만큼 깎일때
void MinusALLHp(DevMon* mon, int amount);

//레벨업 함수
void LevelUp(DevMon* mon);

//mon 리스트 출력
void PrintingMon(DevMon* mon);

//이미지 출력 함수(imglist구조체 변수, 이미지 인덱스 입력 받음)
void PrintingImg(ImgList character, int idx);

//개발몬 선택(mon 리스트에서 선택한 멤버의 인덱스 반환)
int ChooseMon(DevMon* mon,ImgList character);

//개발몬 초기 능력치 설정
void init_play(void);

void PrintBattle(ImgList character, int iNum)
{
    system("clear");
    PrintingImg(character, iNum);
    printf("---------------------------------------------------------------------------------------------\n");
    printf("(%s)%s HP:%d/%d  MP:%d/%d  DMG:%d    ", userS.name, user_mon[selNum.selUser].name, user_mon[selNum.selUser].hp, user_mon[selNum.selUser].max_hp, user_mon[selNum.selUser].mp, user_mon[selNum.selUser].max_mp, user_mon[selNum.selUser].power);
    printf("(NPC)%s HP:%d/%d  MP:%d/%d  DMG:%d\n", devmon[selNum.selNpc].name, devmon[selNum.selNpc].hp, devmon[selNum.selNpc].max_hp, devmon[selNum.selNpc].mp, devmon[selNum.selNpc].max_mp, devmon[selNum.selNpc].power);
    printf("---------------------------------------------------------------------------------------------\n");
}

//Mp 전체 회복
void HealALLMp(DevMon* mon)
{
    for (int i = 0;i < CountMon(mon);i++) mon[i].mp = mon[i].max_mp;
}

//Hp 전체 회복 (배열 이름 입력 받음)
void HealALLHp(DevMon* mon)
{
    for (int i = 0;i < CountMon(mon);i++) mon[i].hp = mon[i].max_hp;
    if (mon == user_mon) userS.total_hp = userS.max_hp; //유저 개발몬일때 정보 갱신
}

//전투 화면 출력(이미지 리스트랑 몬스터 고유번호 입력)
// void PrintBattle(ImgList character, int iNum) 
// {
//     system("clear");
//     PrintingImg(character, iNum);
//     printf("---------------------------------------------------------------------------------------------\n");
//     printf("(%s)%s HP:%d/%d  MP:%d/%d  DMG:%d    ", userS.name, user_mon[selNum.selUser].name, user_mon[selNum.selUser].hp, user_mon[selNum.selUser].max_hp, user_mon[selNum.selUser].mp, user_mon[selNum.selUser].max_mp, user_mon[selNum.selUser].power);
//     printf("(NPC)%s HP:%d/%d  MP:%d/%d  DMG:%d\n", devmon[selNum.selNpc].name, devmon[selNum.selNpc].hp, devmon[selNum.selNpc].max_hp, devmon[selNum.selNpc].mp, devmon[selNum.selNpc].max_mp, devmon[selNum.selNpc].power);
//     printf("---------------------------------------------------------------------------------------------\n");
// }

// 이겼을때 영입할 포켓몬 이미지, 정보 출력
void PrintVic(ImgList character,int iNum)
{
    system("clear");
    PrintingImg(character, iNum);
    printf("---------------------------------------------\n");
    printf("%s HP:%d  MP:%d  DMG:%d SDMG:%d\n", devmon[selNum.selNpc].name, devmon[selNum.selNpc].max_hp, devmon[selNum.selNpc].max_mp, devmon[selNum.selNpc].power, devmon[selNum.selNpc].sk_power);
    printf("---------------------------------------------\n");
}

//전투할 몬스터 선택(선택한 유저몬 인덱스 반환)
int BattleMonSel(void) 
{
    int user = 0;

    if (CountMon(user_mon) > 1)
    {
        while (1)
        {
            sleep(1);
            system("clear");
            PrintingMon(user_mon);
            printf("\n\n 몇 번 몬스터로 싸울까? : ");
            scanf("%d", &user);
            user--;
            if (user >= 0 && user < CountMon(user_mon))
            {
                if (user_mon[user].hp == 0)
                {
                    printf("\n체력이 없습니다. 다시 골라주세요\n");
                    continue;
                }
                else break;
            }
            else
            {
                printf("잘못된 입력입니다! \n");
                continue;
            }
        }
    }
    else sleep(1);
    return user;
}
void PrintBoss(ImgList character) // 보스배틀시 보스 출력
{
    system("clear");
    FILE* bossImg = NULL;
    bossImg = fopen("txt/boss.txt", "r");
    fread(character.imgarr, 1, 9999, bossImg);
    printf("%s\n", character.imgarr);
    fclose(bossImg);
    printf("---------------------------------------------------------------------------------------------\n");
    printf("(%s)%s HP:%d/%d  MP:%d/%d  DMG:%d    ", userS.name, user_mon[selNum.selUser].name, user_mon[selNum.selUser].hp, user_mon[selNum.selUser].max_hp, user_mon[selNum.selUser].mp, user_mon[selNum.selUser].max_mp, user_mon[selNum.selUser].power);
    printf("(Boss)%s HP:%d/%d  MP:%d/%d  DMG:???\n", boss[0].name, boss[0].hp, boss[0].max_hp, boss[0].mp, boss[0].max_mp);
    printf("---------------------------------------------------------------------------------------------\n");
}
void PrintBossUser(ImgList character, int iNum) // 보스배틀시 유저 출력
{
    system("clear");
    PrintingImg(character, iNum);
    printf("---------------------------------------------------------------------------------------------\n");
    printf("(%s)%s HP:%d/%d  MP:%d/%d  DMG:%d    ", userS.name, user_mon[selNum.selUser].name, user_mon[selNum.selUser].hp, user_mon[selNum.selUser].max_hp, user_mon[selNum.selUser].mp, user_mon[selNum.selUser].max_mp, user_mon[selNum.selUser].power);
    printf("(Boss)%s HP:%d/%d  MP:%d/%d  DMG:???\n", boss[0].name, boss[0].hp, boss[0].max_hp, boss[0].mp, boss[0].max_mp);
    printf("---------------------------------------------------------------------------------------------\n");
}
//일반 공격 함수(이미지 리스트,공격몬 인덱스,방어몬 인덱스,공격몬,방어몬)
void Attack01(ImgList character,int atNum, int dfNum, DevMon* atmon, DevMon* dfmon) // 보스 프린트 수정
{
    int event = rand() % 100 + 1;
    if (userS.pre_pos == 'p' && atmon == boss)
        PrintBoss(character);
    else if (userS.pre_pos == 'p')
        PrintBossUser(character, atmon[atNum].iNum);
    else
        PrintBattle(character,atmon[atNum].iNum); //전투화면 출력
    printf("%s 의 공격시도!\n", atmon[atNum].name);
    sleep(1);
    if (event <= 20)
    {
        dfmon[dfNum].hp -= (atmon[atNum].power * 2);
        if (dfmon[dfNum].hp <= 0) dfmon[dfNum].hp = 0;
        if (userS.pre_pos == 'p' && atmon == boss)
            PrintBoss(character);
        else if (userS.pre_pos == 'p')
            PrintBossUser(character, atmon[atNum].iNum);
        else
            PrintBattle(character,atmon[atNum].iNum);
        printf("%s!!\n", atmon[atNum].pName);

        system("clear");
        FILE * critical = NULL;
        memset(character.imgarr, 0, sizeof(character.imgarr));
        critical = fopen("txt/critical.txt", "r");
        fread(character.imgarr, 1, 9999, critical);
        printf("%s\n", character.imgarr);
        fclose(critical);

        printf("크리티컬 히트!! %s에게 %d의 치명타를 입혔다\n", dfmon[dfNum].name, (atmon[atNum].power * 2));
        sleep(1);
    }
    else
    {
        dfmon[dfNum].hp -= atmon[atNum].power;
        if (dfmon[dfNum].hp <= 0) dfmon[dfNum].hp = 0;
        if (userS.pre_pos == 'p' && atmon == boss)
            PrintBoss(character);
        else if (userS.pre_pos == 'p')
            PrintBossUser(character, atmon[atNum].iNum);
        else
            PrintBattle(character,atmon[atNum].iNum);;
        printf("%s! %s에게 %d의 데미지를 입혔다\n", atmon[atNum].pName, dfmon[dfNum].name, atmon[atNum].power);
        sleep(1);
    }
}

//특수 공격 함수(이미지 리스트,공격몬 인덱스,방어몬 인덱스,공격몬,방어몬)
void Attack02(ImgList character,int atNum, int dfNum, DevMon* atmon, DevMon* dfmon) // 보스 프린트 수정
{
    if (userS.pre_pos == 'p' && atmon == boss)
        PrintBoss(character);
    else if (userS.pre_pos == 'p')
        PrintBossUser(character, atmon[atNum].iNum);
    else
        PrintBattle(character,atmon[atNum].iNum);
    printf("%s 의 특수공격!\n", atmon[atNum].name);
    sleep(1);
    dfmon[dfNum].hp -= (atmon[atNum].sk_power); atmon[atNum].mp -= (userS.level*30);  // 마나 소모량 레벨비례 증가
    if (dfmon[dfNum].hp <= 0)dfmon[dfNum].hp = 0;
    if (userS.pre_pos == 'p' && atmon == boss)
        PrintBoss(character);
    else if (userS.pre_pos == 'p')
        PrintBossUser(character, atmon[atNum].iNum);
    else
        PrintBattle(character,atmon[atNum].iNum);
    printf("%s!!\n", atmon[atNum].skpName);
    printf("공격성공! %s에게 %d의 데미지를 입혔다\n", dfmon[dfNum].name, (atmon[atNum].sk_power));
    sleep(1);
}

//NPC 공격 함수
void NpcAttack(ImgList character)
{
    int event;
    if (devmon[selNum.selNpc].hp == 0)
        return;
    else if (devmon[selNum.selNpc].mp >= 50)
    {
        event = rand() % 100 + 1;
        if (event <= 80)
        {
            Attack01(character,selNum.selNpc, selNum.selUser, devmon, user_mon);
        }
        else
        {
            Attack02(character,selNum.selNpc, selNum.selUser, devmon, user_mon);
        }
    }
    else
    {
        Attack01(character,selNum.selNpc, selNum.selUser, devmon, user_mon);
    }
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

void ItemIce(void) // 아이템 1번 턴넘기기
{
    printf("%s 아이템 사용!! %s\n\n", mash[0].name, mash[0].script);
    mash[0].count = 1;
    sleep(2);
}

void ItemHpUp(void) // 아이템 2번 회복포션
{
    printf("%s 아이템 사용!! %s \n\n", mash[1].name, mash[1].script);
    user_mon[selNum.selUser].hp += (user_mon[selNum.selUser].max_hp / 2);
    if (user_mon[selNum.selUser].hp > user_mon[selNum.selUser].max_hp)
        user_mon[selNum.selUser].hp = user_mon[selNum.selUser].max_hp;
    sleep(2);
    if (mash[0].count == 1){
            mash[0].count = 0;
            PrintBattle(character,devmon[selNum.selNpc].iNum);
            printf("\n\n %s 얼음효과!! 공격 불가능 \n", devmon[selNum.selNpc].name);
            sleep(1);
    }
    else{
        NpcAttack(character);
    }
}

void ItemMpUp(void) // 아이템 3번 마나회복포션
{
    printf("%s 아이템 사용!! %s \n\n", mash[2].name, mash[2].script);
    user_mon[selNum.selUser].mp += (user_mon[selNum.selUser].max_mp / 2);
    if (user_mon[selNum.selUser].mp > user_mon[selNum.selUser].max_mp)
        user_mon[selNum.selUser].mp = user_mon[selNum.selUser].max_mp;
    sleep(2);
    if (mash[0].count == 1){
            mash[0].count = 0;
            PrintBattle(character,devmon[selNum.selNpc].iNum);
            printf("\n\n %s 얼음효과!! 공격 불가능 \n", devmon[selNum.selNpc].name);
            sleep(1);
    }
    else{
        NpcAttack(character);
    }
}

void BossItemHpUp(void) // 보스전 아이템 2번
{
    printf("%s 아이템 사용!! %s \n\n", mash[1].name, mash[1].script);
    user_mon[selNum.selUser].hp += (user_mon[selNum.selUser].max_hp / 2);
    if (user_mon[selNum.selUser].hp > user_mon[selNum.selUser].max_hp)
        user_mon[selNum.selUser].hp = user_mon[selNum.selUser].max_hp;
    sleep(2);
}

void BossItemMpUp(void) // 보스전 아이템 3번
{
    printf("%s 아이템 사용!! %s \n\n", mash[2].name, mash[2].script);
    user_mon[selNum.selUser].mp += (user_mon[selNum.selUser].max_mp / 2);
    if (user_mon[selNum.selUser].mp > user_mon[selNum.selUser].max_mp)
        user_mon[selNum.selUser].mp = user_mon[selNum.selUser].max_mp;
    sleep(2);
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
int ItemYorN(void) // 아이템 사용할껀지 판단하는 함수 // fgets 로 변경
{
    char cho[2];
    while(1){
        printf("진짜 사용 하시겠습니까? (y or n) : ");
        fgets(cho, 2, stdin);
        ClearBuffer();
        printf("\n");
        if(cho[0] == 'y')
            return cho[0];
        else if(cho[0] == 'n')
            return cho[0];
        else{
            printf("잘못된 입력!\n");
            continue;
        }            
    }
}
int ItemUse(void) // 아이템 사용시 발동되는 함수 // 보스전을 위해 변경
{
    char cho[2];
    int idx;
    int i = 1;
    while(i == 1){
        PrintItem();
        fputs("몇번 아이템을 고르시겠습니까? (돌아가기 = x): ",stdout);
        fgets(cho,sizeof(cho),stdin);
        ClearBuffer();
        // printf("\n");
        switch(cho[0]){
            case '1': idx = 0; break;
            case '2': idx = 1; break;
            case '3': idx = 2; break;
            case '4': idx = 3; break;
            case '5': idx = 4; break;
            case 'x': i = 0; idx = 6; break;
            default:  idx = 5;  break; 
        }
        if(idx >= CountItem(user_item)){
            if (idx == 6)
                return 1;
            printf("잘못된 입력\n");
            sleep(1);
            continue;
        }
        else if(user_item[idx].iNum == 0)
        {
            cho[0] = ItemYorN();
            if(cho[0] == 'y'){
                ItemIce();
                ItemRemove(idx);
                return 0;
            }
            else if(cho[0] == 'n')
                continue;
        }
        else if(user_item[idx].iNum == 1)
        {
            cho[0] = ItemYorN();
            if(cho[0] == 'y'){
                if(userS.pre_pos == 'p')
                    BossItemHpUp();
                else
                    ItemHpUp();
                ItemRemove(idx);
                return 0;
            }
            else if(cho[0] == 'n')
                continue;
        }
        else if(user_item[idx].iNum == 2)
        {
            cho[0] = ItemYorN();
            if(cho[0] == 'y'){
                if(userS.pre_pos == 'p')
                    BossItemMpUp();
                else
                    ItemMpUp();
                ItemRemove(idx);
                return 0;
            }
            else if(cho[0] == 'n')
                continue;
        }
    }
}

//공격동작 선택
void BattleActSel(ImgList character,int num)
{
    // if (num == 1)
    // {
    //     Attack01(character,selNum.selUser, selNum.selNpc, user_mon, devmon);
    //     NpcAttack(character);
    // }
    // else if (num == 2)
    // {
    //     Attack02(character,selNum.selUser, selNum.selNpc, user_mon, devmon);
    //     NpcAttack(character);
    // }
    if(num == 1)
    {
        Attack01(character,selNum.selUser, selNum.selNpc, user_mon, devmon);
        if (mash[0].count == 1){
            mash[0].count = 0;
            PrintBattle(character,devmon[selNum.selNpc].iNum);
            printf("\n\n %s 얼음효과!! 공격 불가능 \n", devmon[selNum.selNpc].name);
            sleep(1);
        }
        else if( devmon[selNum.selNpc].hp == 0 ){  // 얼음효과 쓰고나서 상대방 죽였을때 프린트 안하게
            mash[0].count = 0;
        }
        else{
            NpcAttack(character);
        }
        
    }
    else if (num == 2)
    {
        Attack02(character,selNum.selUser, selNum.selNpc, user_mon, devmon);
        if (mash[0].count == 1){
            mash[0].count = 0;
            PrintBattle(character,devmon[selNum.selNpc].iNum);
            printf("\n\n %s 얼음효과!! 공격 불가능 \n", devmon[selNum.selNpc].name);
            sleep(1);
        }
        else if( devmon[selNum.selNpc].hp == 0 ){ // 얼음효과 쓰고나서 상대방 죽였을때 프린트 안하게
            mash[0].count = 0;
        }
        else{
            NpcAttack(character);
        }
    }
    else if (num == 3) // 아이템 사용 기능 추가
    {
        ItemUse();
    }
}

//배틀에 승리했을 때
void BattleVictory(ImgList character)
{
    int choice, i;
    while(1)
    {
        PrintVic(character,devmon[selNum.selNpc].iNum);
        printf("내 개발몬으로 영입할까? 1)예 2)아니오 :");
        scanf("%d", &choice);
        if (choice == 1)
        {
            int quit = 1;
            while (quit == 1)
            {
                if (CountMon(user_mon) == 3)
                {
                    int selMon, idx;
                    PrintVic(character,devmon[selNum.selNpc].iNum);
                    for (i = 0; i < CountMon(user_mon); i++)
                    {
                        printf("   %d) %s HP:%d/%d MP:%d/%d DMG:%d SDMG:%d \n", i + 1, user_mon[i].name, user_mon[i].hp, user_mon[i].max_hp, user_mon[i].mp, user_mon[i].max_mp, user_mon[i].power, user_mon[i].sk_power);
                    }
                    printf("\n\n 몇 번 몬스터를 교체할까? (취소 : x): ");
                    ClearBuffer();
                    selMon = getchar();
                    switch(selMon){
                        case '1': idx = 0; break;
                        case '2': idx = 1; break;
                        case '3': idx = 2; break;
                        case 'x': idx = 5; quit = 0; break;
                        default: printf("잘못된 입력!!"); idx = 5; break; 
                    }
                    if (idx == 0)
                    {
                        printf("\n\n시작 개발몬은 변경 불가능합니다. \n");
                        sleep(1);
                    }
                    else if(idx > 3)
                    {
                        continue;
                    }
                    else
                    {
                        AddTeam(user_mon, devmon, idx);
                        AddTeam(devmon, user_mon, selNum.selNpc);
                        user_mon[CountMon(user_mon) - 1].hp = user_mon[CountMon(user_mon) - 1].max_hp;
                        user_mon[CountMon(user_mon) - 1].mp = user_mon[CountMon(user_mon) - 1].max_mp;

                        devmon[CountMon(devmon) - 1].hp = devmon[CountMon(devmon) - 1].max_hp;
                        devmon[CountMon(devmon) - 1].mp = devmon[CountMon(devmon) - 1].max_mp;

                        printf("\n동료 교체 성공! 버려진 개발몬은 애타게 나를 바라봅니다....\n");
                        sleep(1);

                        system("clear");
                        FILE * recruit = NULL;
                        memset(character.imgarr, 0, sizeof(character.imgarr));
                        recruit = fopen("txt/recruit.txt", "r");
                        fread(character.imgarr, 1, 9999, recruit);
                        printf("%s\n", character.imgarr);
                        fclose(recruit);

                        printf("\n동료 영입 성공! \n");

                        printf("\n변경된 내 개발몬 목록 \n");
                        for (i = 0; i < CountMon(user_mon); i++)
                        {
                            printf("   %d) %s HP:%d/%d MP:%d/%d DMG:%d SDMG:%d \n", i + 1, user_mon[i].name, user_mon[i].hp, user_mon[i].max_hp, user_mon[i].mp, user_mon[i].max_mp, user_mon[i].power, user_mon[i].sk_power);
                        }
                        sleep(1);
                        return;
                        break;
                    }
                }
                else
                {
                    AddTeam(devmon, user_mon, selNum.selNpc);
                    user_mon[CountMon(user_mon) - 1].hp = user_mon[CountMon(user_mon) - 1].max_hp;
                    user_mon[CountMon(user_mon) - 1].mp = user_mon[CountMon(user_mon) - 1].max_mp;


                    system("clear");
                    FILE * recruit = NULL;
                    memset(character.imgarr, 0, sizeof(character.imgarr));
                    recruit = fopen("txt/recruit.txt", "r");
                    fread(character.imgarr, 1, 9999, recruit);
                    printf("%s\n", character.imgarr);
                    fclose(recruit);

                    printf("\n동료 영입 성공! \n");
                    printf("\n변경된 내 개발몬 목록 \n");
                    for (i = 0; i < CountMon(user_mon); i++)
                    {
                        printf("\n   %d) %s HP:%d/%d MP:%d/%d DMG:%d SDMG:%d \n", i + 1, user_mon[i].name, user_mon[i].hp, user_mon[i].max_hp, user_mon[i].mp, user_mon[i].max_mp, user_mon[i].power, user_mon[i].sk_power);
                    }
                    sleep(1);
                    return;
                    break;
                }
            }
        }
        else if(choice==2)
        {
            devmon[selNum.selNpc].hp = devmon[selNum.selNpc].max_hp;
            devmon[selNum.selNpc].mp = devmon[selNum.selNpc].max_mp;
            break;
        }
        else
        {
            printf("잘못된 입력입니다. \n");
            sleep(1); system("clear"); 
        }
    }
}


void BattleCore(ImgList character)
{
    system("clear");
    selNum.selNpc = rand() % CountMon(devmon);
    int userNum = CountMon(user_mon);
    int selAct;
    int btQuit = 1;
    int cnt = 1;
    int event;

    printf("배틀이 진행됩니다. \n");
    FILE* battlescene = NULL;
    memset(character.imgarr, 0, sizeof(character.imgarr));
    battlescene = fopen("txt/battlescene.txt", "r");
    fread(character.imgarr, 1, 9999, battlescene);
    printf("%s\n", character.imgarr);
    fclose(battlescene);

    while (btQuit == 1)
    {
        selNum.selUser = BattleMonSel();
        while (cnt > 0)
        {
            UpdateHp();
            if (userS.total_hp == 0)
            {
                system("clear");
                FILE * defeat = NULL;
                memset(character.imgarr, 0, sizeof(character.imgarr));
                defeat = fopen("txt/defeat.txt", "r");
                fread(character.imgarr, 1, 9999, defeat);
                printf("%s\n", character.imgarr);
                fclose(defeat);

                printf("전투에서 패배했다...\n");
                sleep(1);
                btQuit = 0;
                break;
            }
            else if (user_mon[selNum.selUser].hp == 0)
                break;
            else if (devmon[selNum.selNpc].hp == 0)
            {
                system("clear");
                FILE * vic = NULL;
                memset(character.imgarr, 0, sizeof(character.imgarr));
                vic = fopen("txt/vic.txt", "r");
                fread(character.imgarr, 1, 9999, vic);
                printf("%s\n", character.imgarr);
                fclose(vic);

                printf("\n\n\n\n     전투에서 승리했다..!!!\n");
                sleep(1);
                BattleVictory(character);
                btQuit = 0;
                break;
            }
            PrintBattle(character,devmon[selNum.selNpc].iNum);
            if (cnt == 1)
                printf("야생의 %s이(가) 나타났다!\n", devmon[selNum.selNpc].name);
            printf("\n 어떻게 할까? \n");
            printf("1)일반 공격  2)특수 공격  3)아이템 창  4)도망가기 : ");
            scanf("%d", &selAct);
            if (selAct < 1 || selAct > 4)
            {
                printf("잘못된 입력!!\n");
                sleep(1);
                continue;
            }
            else if (selAct == 2 && user_mon[selNum.selUser].mp < (userS.level*30))
            {
                printf("마나가 모자랍니다.\n");
                sleep(1);
                continue;
            }
            else if (selAct == 4)
            {
                event = rand() % 100 + 1;
                if (event <= 10)
                {
                    system("clear");
                    FILE * escape = NULL;
                    memset(character.imgarr, 0, sizeof(character.imgarr));
                    escape = fopen("txt/scape.txt", "r");
                    fread(character.imgarr, 1, 9999, escape);
                    printf("%s\n", character.imgarr);
                    fclose(escape);

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
                    NpcAttack(character);
                    continue;
                }
            }
            else if(selAct == 3 && CountItem(user_item) == 0)
            { // 아이템 갯수 확인 기능 추가
            	printf("아이템이 없습니다 정신차리세요.\n");
            	sleep(1);
            	continue;
            }
            BattleActSel(character,selAct);
            cnt++;
        }
    }
    UpdateHp();
}

//퀴즈단 지갑 털기 //클래스 위치 받기(생산: 0, 드론: 1, iot: 2)
void QuestionMon(int cnum);

void PrintBoss(ImgList character) // 보스배틀시 보스 출력
{
    system("clear");
    FILE* bossImg = NULL;
    bossImg = fopen("txt/boss.txt", "r");
    fread(character.imgarr, 1, 9999, bossImg);
    printf("%s\n", character.imgarr);
    fclose(bossImg);
    printf("---------------------------------------------------------------------------------------------\n");
    printf("(%s)%s HP:%d/%d  MP:%d/%d  DMG:%d    ", userS.name, user_mon[selNum.selUser].name, user_mon[selNum.selUser].hp, user_mon[selNum.selUser].max_hp, user_mon[selNum.selUser].mp, user_mon[selNum.selUser].max_mp, user_mon[selNum.selUser].power);
    printf("(Boss)%s HP:%d/%d  MP:%d/%d  DMG:???\n", boss[0].name, boss[0].hp, boss[0].max_hp, boss[0].mp, boss[0].max_mp);
    printf("---------------------------------------------------------------------------------------------\n");
}
void PrintBossUser(ImgList character, int iNum) // 보스배틀시 유저 출력
{
    system("clear");
    PrintingImg(character, iNum);
    printf("---------------------------------------------------------------------------------------------\n");
    printf("(%s)%s HP:%d/%d  MP:%d/%d  DMG:%d    ", userS.name, user_mon[selNum.selUser].name, user_mon[selNum.selUser].hp, user_mon[selNum.selUser].max_hp, user_mon[selNum.selUser].mp, user_mon[selNum.selUser].max_mp, user_mon[selNum.selUser].power);
    printf("(Boss)%s HP:%d/%d  MP:%d/%d  DMG:???\n", boss[0].name, boss[0].hp, boss[0].max_hp, boss[0].mp, boss[0].max_mp);
    printf("---------------------------------------------------------------------------------------------\n");
}



void BossUserAttack(void)
{
    if(userS.total_hp == 0)
        return;
    int i;
    char sel[2];
    int quit = 1;
    ClearBuffer();
    for(i=0; i<CountMon(user_mon); i++)
    {
        selNum.selUser = i;
        if (user_mon[selNum.selUser].hp > 0 && boss[0].hp > 0)
        {
            while(quit == 1)
            {
                PrintBossUser(character, user_mon[selNum.selUser].iNum);
                printf("** 사용자 턴 **\n");
                printf("\n 어떻게 할까? \n");
                printf("1)일반 공격  2)특수 공격  3)아이템 창 : ");
                fgets(sel,2,stdin);
                ClearBuffer();
                if(sel[0] == '1')
                {
                    Attack01(character,selNum.selUser, 0, user_mon, boss);
                    break;
                }
                else if(sel[0] == '2')
                {
                    if(user_mon[selNum.selUser].mp < (userS.level*30))
                    {
                        printf("마나가 없습니다...\n");
                        sleep(1);
                    }
                    else
                    {
                        (character,selNum.selUser, 0, user_mon, boss);
                        break;
                    }
                }
                else if(sel[0] == '3')
                {
                    quit = ItemUse();
                }
                else
                {
                    printf("잘못된 입력!!");
                    sleep(1);
                }
            }
        }
    }
}
void BossAttack(void)
{
    if(boss[0].hp == 0)
        return;
    int event;
    event = rand() % 1923 + 100;
    boss[0].power = event;
    while(1)
    {
        event = rand() % CountMon(user_mon);
        if (user_mon[event].hp == 0)
            continue;
        else
            selNum.selUser = event;
            break;
    }
    PrintBoss(character);
    if (mash[0].count == 1){
        mash[0].count = 0;
        printf("\n\n %s 얼음효과!! 공격 불가능 \n", boss[0].name);
        sleep(1);
        return;
    }
    printf("** 보스 턴 **\n");
    sleep(2);
    
    if(boss[0].hp <= 5000)
    {
        event = rand() % 100 + 1;
        if(event <= 30)
        {
            boss[0].hp += 5000;
            PrintBoss(character);
            printf("%s의 아이스티 마시기!! 체력 5000 회복!!", boss[0].name);
            sleep(2);
        }
        else
        {   
            if(boss[0].mp >= (userS.level*30))
            {
                event = rand() % 100 + 1;
                if(event <= 80)
                    Attack01(character,0,selNum.selUser,boss,user_mon);
                else
                    Attack02(character,0,selNum.selUser,boss,user_mon);
            }
            else
                Attack01(character,0,selNum.selUser,boss,user_mon);
        }
    }
    else
    {
        if(boss[0].mp >= (userS.level*30)) // 보스토 어택2 함수를 공유하기 때문에 레벨비례로 할 수 밖에...
            {
                event = rand() % 100 + 1;
                if(event <= 80)
                    Attack01(character,0,selNum.selUser,boss,user_mon);
                else
                    Attack02(character,0,selNum.selUser,boss,user_mon);
            }
        else
            Attack01(character,0,selNum.selUser,boss,user_mon);
    }
}
void BadEnd(int* quit)
{
    char cho[2];
    system("clear");
    printf("\n\n    보스전 패배!!! \n");
    sleep(2);
    while(1)
    {
        printf("\n\n다시 도전 하시겠습니까? (y or n) : ");
        fgets(cho, 2, stdin);
        if(cho[0] == 'y')
        {
            printf("\n\n 부족했던 복습을 하러 다시 개발원으로...\n");
            sleep(1);
            return;
        }
        else if(cho[0] == 'n')
        {   
            printf("\n\n 수료실패!! 취업실패!! \n\n 당신은 또다시 방구석으로 돌아가 백수가 되었습니다... \n\n bad ending....");
            sleep(2);
            *quit = 0;
            return;
        }
        else
            continue;
    }
}
void HappyEnd()
{
    // 여기 쿠파 쓰러지는 그림이나 당하는 그림 있으면 좋을듯
    printf("\n\n 보스가 쓰러졌다!!\n");
    sleep(2);
    system("clear");
    printf("\n\n 성공적으로 스펙을 쌓은 당신은 개발원을 졸업했다 \n\n 포트폴리오도 완벽하다...!");
    sleep(2);
    system("clear");
    printf("\n\n 광주인력 개발원을 다니고~ 나의 성공시대 시작됬다~♩ \n\n 광주 인력 개발원을 다니고~ 내인생이 달라졌다~~♬");
    sleep(2);
    system("clear");
    printf("\n\n 플레이 해주셔서 감사합니다.\n");
}

void BossBattleCore(int* quit)
{
    system("clear");
    int turn = rand() % 2;
    FILE* bossImg = NULL;
    bossImg = fopen("txt/boss.txt", "r");
    fread(character.imgarr, 1, 9999, bossImg);
    printf("%s\n", character.imgarr);
    fclose(bossImg);
    printf("---------------------------------------------\n");
    printf("(Boss)%s HP:%d/%d  MP:%d/%d  DMG:???\n", boss[0].name, boss[0].hp, boss[0].max_hp, boss[0].mp, boss[0].max_mp);
    printf("---------------------------------------------\n");
    printf("\n\n ***** 보스전 시작 *****\n");
    sleep(2);
    while(1)
    {
        UpdateHp();
        if(userS.total_hp == 0)
        {
            BadEnd(quit);
            break;
        }
        else if(boss[0].hp == 0)
        {
            HappyEnd();
            *quit = 0;
            break;
        }

        if(turn == 0)
        {
            PrintBoss(character);
            printf("\n\n ***** 선공 주사위 굴림 유저 승 *****\n");
            printf(" ***** 유저 선공 *****\n");
            sleep(1);
            BossUserAttack();
            BossAttack();
        }
        else
        {
            PrintBoss(character);
            printf("\n\n ***** 선공 주사위 굴림 보스 승 *****\n");
            printf(" ***** 보스 선공 *****\n");
            sleep(1);
            BossAttack();
            BossUserAttack();       
        }
    }
}


int main(void)
{
    srand((unsigned int)time(NULL));
    //캐릭터 이미지 리스트
    // ImgList character = { {fopen("txt/devmon00.txt","r"),fopen("txt/devmon01.txt", "r"),fopen("txt/devmon02.txt", "r"),fopen("txt/devmon03.txt", "r"),fopen("txt/devmon04.txt", "r")}, };
    int user; //입력 받는 곳
    int choose = 0;
    int idx, event;
    int mainQuit = 1; // 메인 함수에 와일문 끄는 변수 추가

    init_play(); //개발몬 능력치 설정
    // devmon[0].power = 300; //치트키

    FILE* start = NULL;
    start = fopen("txt/start.txt", "r");
    fread(character.imgarr, 1, 9999, start);
    printf("%s\n", character.imgarr);
    fclose(start);

    printf("당신의 이름은? >");
    scanf("%s", userS.name);
    printf("%s님 환영합니다. \n", userS.name);
    sleep(1);

    //초기 개발몬 선택
    idx = ChooseMon(devmon,character);
    AddTeam(devmon, user_mon, idx);
    user_mon[0].hp = 10000;
    user_mon[0].power = 10000;
    system("clear");

    PrintingImg(character,idx);
    printf("%s과 함께합니다. 개발원에 입장합니다. \n ", user_mon[0].name);
    sleep(1);

    ItemSpawn(5);
    map[userS.xpos][userS.ypos] = 'X';

    while (mainQuit == 1)
    {
        if (userS.total_hp == 0) ReSpawn();

        if (userS.hour > 3)
        {
            FILE * unlk = NULL;
            memset(character.imgarr, 0, sizeof(character.imgarr));
            unlk = fopen("txt/unlk.txt", "r");
            fread(character.imgarr, 1, 9999, unlk);
            printf("%s\n", character.imgarr);
            fclose(unlk);
            
            map[23][19] = '2'; printf("(공지)교수실 문이 열렸습니다. \n");
        }
        system("clear");
        PrintingMap(); //맵 출력
        
        printf("획득한 아이템: %s %s %s %s %s\n", user_item[0].name, user_item[1].name, user_item[2].name,user_item[3].name,user_item[4].name);
        printf("위(w) 왼쪽(a) 아래(s) 오른쪽(d) >");

        ClearBuffer();
        user = getchar();
        printf("\n");

        //플레이어 이동
        choose = Move(user);
        if (choose == 1) continue;
        userS.hour++; event = rand() % 100;
        system("clear");
        PrintingMap(); //맵 출력

        if (userS.pre_pos == 's')
        {
            printf("게임을 종료하시겠습니까? (y/n)\n");
            ClearBuffer();
            user = getchar();
            if (user == 'y') break;
            else continue;
        }
        //복도, 길('0') 이벤트 (event가 0~29일때 발생)
        else if (userS.pre_pos == '0' && event < 3)
        {
            BattleCore(character);
        }

        //교실('c') 이벤트 (event가 0~19일때 발생) //퀴즈단 만나 퀴즈 풀기
        else if (userS.pre_pos == 'c' && event < 20)
        {
            QuestionMon(0); //생산 교실 이벤트
            sleep(1);
        }
        else if (userS.pre_pos == 'd' && event < 20)
        {
            QuestionMon(1); //드론 교실 이벤트
            sleep(1);
        }
        else if (userS.pre_pos == 'e' && event < 20)
        {
            QuestionMon(2); //iot 교실 이벤트
            sleep(1);
        }

        else if (userS.pre_pos == 'i' || userS.pre_pos == 'r' || userS.pre_pos == 'f')
        {
            GetItem(userS.pre_pos);
            userS.pre_pos = '0';
            sleep(1);
        }

        //급식실('h')
        else if (userS.pre_pos == 'q')
        {
            HealALLHp(user_mon);
            HealALLMp(user_mon);
            
            system("clear");
            FILE * heal = NULL;
            memset(character.imgarr, 0, sizeof(character.imgarr));
            heal = fopen("txt/heal.txt", "r");
            fread(character.imgarr, 1, 9999, heal);
            printf("%s\n", character.imgarr);
            fclose(heal);

            printf("체력이 모두 회복됩니다. \n");
            printf("잠시후 랜덤 스폰됩니다. \n");
            sleep(1);
            RandomSpawn();
        }

        //교수실('p')
        else if (userS.pre_pos == 'p')
        {
            printf("교수실에 들어왔다! \n"); //교수실 이벤트 발생
            sleep(1);
            BossBattleCore(&mainQuit);
        }
    }
    return 0;
}





//버퍼 비우기
void ClearBuffer(void)
{
    while (getchar() != '\n');
}

//맵 출력 함수
void PrintingMap(void)
{
    int x = 0, y = 0;

    printf("-----------------------------------------------------------------\n");
    printf("user:%s total_HP:%d Hour:%d Level:%d Xp:", userS.name, userS.total_hp, userS.hour, userS.level);
    for (x = 0;x < 10 - userS.xp / 50;x++) printf("O "); //경험치 구현( 50당 한칸)
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


//맵 이동 함수(올바른 길 가면 0반환, 그 외 1 반환) -별도의 입력값 검사 필요 x
int Move(int user)
{
    int choose = 0;
    if (userS.pre_pos == 'q') //급실실에서 이동할때 랜덤스폰
    {
        RandomSpawn();
        return 1;
    }
    map[userS.xpos][userS.ypos] = userS.pre_pos;
    if (user == 'w'||user == 'W')
    {
        userS.xpos--;
        if (map[userS.xpos][userS.ypos] == '1')
        {
            userS.xpos++; choose = 1;
        }
    }
    else if (user == 'a'||user == 'A')
    {
        userS.ypos--;
        if (map[userS.xpos][userS.ypos] == '1')
        {
            userS.ypos++; choose = 1;
        }
    }
    else if (user == 's'||user == 'S')
    {
        userS.xpos++;
        if (map[userS.xpos][userS.ypos] == '1')
        {
            userS.xpos--; choose = 1;
        }
    }
    else if (user == 'd'||user == 'D')
    {
        userS.ypos++;
        if (map[userS.xpos][userS.ypos] == '1' || map[userS.xpos][userS.ypos] == '3')
        {
            userS.ypos--; choose = 1;
        }
    }
    else choose = 1;
    userS.pre_pos = map[userS.xpos][userS.ypos];
    map[userS.xpos][userS.ypos] = 'X';
    return choose;
}

//랜덤 스폰 함수 (급식실에서 회복했을때 랜덤 이동)
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

    FILE * ambulance = NULL;
    memset(character.imgarr, 0, sizeof(character.imgarr));
    ambulance = fopen("txt/ambulance.txt", "r");
    fread(character.imgarr, 1, 9999, ambulance);
    printf("%s\n", character.imgarr);
    fclose(ambulance);
    
    printf("체력이 모두 소진되었습니다. 구급차로 이동합니다. \n");
    map[userS.xpos][userS.ypos] = userS.pre_pos;
    userS.pre_pos = 'q';
    userS.xpos = 12; userS.ypos = 2; //구급차 위치
    map[userS.xpos][userS.ypos] = 'X';

    // FILE * heal = NULL;
    // memset(character.imgarr, 0, sizeof(character.imgarr));
    // heal = fopen("txt/heal.txt", "r");
    // fread(character.imgarr, 1, 9999, heal);
    // printf("%s\n", character.imgarr);
    // fclose(heal);

    HealALLHp(user_mon);//hp 전체 회복
    HealALLMp(user_mon);
    sleep(1);
}

//아이템 랜덤 스폰(맵에 스폰될 아이템 개수 입력받음)
void ItemSpawn(int inum)
{
    int xpos = rand() % 25, ypos = rand() % 25;
    int event;
    for (int i = 0;i < inum;i++)
    {
        event = rand() % 3;
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
            map[xpos][ypos] = 'r'; //주먹밥
            break;
        case 2:
            map[xpos][ypos] = 'f'; //커피
            break;
        }
    }
}

//아이템 갯수 세는 함수
int CountItem(Item* item)
{
    int idx = 0;
    while (item[idx].iNum != -1) idx++; //개발몬 수 세기
    return idx;
}

//아이템 get(userS.pre_pos값 입력 받음 혹은 아이템 지정 문자)
void GetItem(char map)
{
    int idx = CountItem(user_item);
    if (idx == 5)
    {
        FILE * full = NULL;
        memset(character.imgarr, 0, sizeof(character.imgarr));
        full = fopen("txt/full.txt", "r");
        fread(character.imgarr, 1, 9999, full);
        printf("%s\n", character.imgarr);
        fclose(full);

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
        FILE * acq = NULL;
        memset(character.imgarr, 0, sizeof(character.imgarr));
        acq = fopen("txt/acq.txt", "r");
        fread(character.imgarr, 1, 9999, acq);
        printf("%s\n", character.imgarr);
        fclose(acq);

        printf("%s를 획득했다! \n", user_item[idx].name);
    }
}

//개발몬 수 세는 함수(배열 이름 입력받음)
int CountMon(DevMon* mon)
{
    int idx = 0;
    while (mon[idx].iNum != -1) idx++; //개발몬 수 세기
    return idx;
}

//팀 영입 함수(mon1->mon2) idx=mon1인덱스
void AddTeam(DevMon* mon1, DevMon* mon2, int idx)
{
    //mon1의 idx번째 멤버를 mon2에 추가
    int uidx = CountMon(mon2); //mon2에 추가될 자리 인덱스

    mon2[uidx] = mon1[idx]; //mon1의 idx번째 개발몬 정보 mon2에 복사

    //빠져나간 멤버 리스트에서 제거 ->배열 요소 제거 함수로 따로 구현해도 될듯!
    for (int i = idx;i < CountMon(mon1) - 1;i++)
    {
        mon1[i] = mon1[i + 1];
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

// //Mp 전체 회복
// void HealALLMp(DevMon* mon)
// {
//     for (int i = 0;i < CountMon(mon);i++) mon[i].mp = mon[i].max_mp;
// }

// //Hp 전체 회복 (배열 이름 입력 받음)
// void HealALLHp(DevMon* mon)
// {
//     for (int i = 0;i < CountMon(mon);i++) mon[i].hp = mon[i].max_hp;
//     if (mon == user_mon) userS.total_hp = userS.max_hp; //유저 개발몬일때 정보 갱신
// }

//mon리스트의 idx번 멤버 amount만큼 회복
void HealHp(DevMon* mon, int idx, int amount)
{
    mon[idx].hp += amount;
    if (mon == user_mon) userS.total_hp += amount;
}

//mon리스트의 idx번 개발몬 Hp amount 만큼 깎임
void MinusHp(DevMon* mon, int idx, int amount)
{
    mon[idx].hp -= amount;
    if (mon[idx].hp < 1) mon[idx].hp = 0;
    if (mon == user_mon) userS.total_hp -= amount;
}

//mon리스트 전체 개발몬 Hp amount 만큼 깎일때
void MinusALLHp(DevMon* mon, int amount)
{
    int idx = CountMon(mon);
    for (int i = 0;i < idx;i++)
        MinusHp(mon, i, amount);
    if (userS.total_hp < 1) userS.total_hp = 0;
}

//레벨업 함수
void LevelUp(DevMon* mon)
{
    printf("레벨업을 했다!!! \n");

    for (int i = 0;i < CountMon(mon);i++)
    {
        mon[i].max_hp += 100; mon[i].max_mp += 50;
        mon[i].power += 20; mon[i].sk_power += 20;
    } HealALLHp(mon); HealALLMp(mon);
    if (mon == user_mon)
    {
        system("clear");
        FILE * lvup = NULL;
        memset(character.imgarr, 0, sizeof(character.imgarr));
        lvup = fopen("txt/lvup.txt", "r");
        fread(character.imgarr, 1, 9999, lvup);
        printf("%s\n", character.imgarr);
        fclose(lvup);

        userS.level++; userS.xp = 0;
        UpdateHp();
    }
}

//퀴즈단 지갑 털기 //클래스 위치 받기(생산: 0, 드론: 1, iot: 2)
void QuestionMon(int cnum) 
{
    srand((unsigned int)time(NULL)); //난수 한 번 더 초기화
    char* teacher[3] = { "류청걸","최하문","리북녘" }; //퀴즈단: iot-리북녘, 드론-최하문, 생산-류청걸
    //산수 문제로!
    int num1, num2, cal;
    int answer, qcount = 0;
    int correct = 0;

    system("clear");
    FILE * quiz = NULL;
    memset(character.imgarr, 0, sizeof(character.imgarr));
    quiz = fopen("txt/quiz.txt", "r");
    fread(character.imgarr, 1, 9999, quiz);
    printf("%s\n", character.imgarr);
    fclose(quiz);

    printf("%s 교수님을 마주쳤다! \n", teacher[cnum]);
    sleep(1);
    printf("%s) 문제를 다 맞추면 아이스티를 사주도록 하지 \n", teacher[cnum]);
    while (qcount < 3)
    {
        correct = 0;
        sleep(1);
        system("clear");
        PrintingMap(); //-> 교수 얼굴 출력으로 바꿀것
        num1 = rand() % 100 + 1, num2 = rand() % 100 + 1;
        cal = rand() % 3;

        printf("%d번째 문제를 내겠다! \n", qcount + 1);

        switch (cal)
        {
        case 0:
            printf("%d + %d = ?\b", num1, num2);
            scanf("%d", &answer);
            if (answer == num1 + num2) correct = 1;
            break;
        case 1:
            printf("%d - %d = ?\b", num1, num2);
            scanf("%d", &answer);
            if (answer == num1 - num2) correct = 1;
            break;
        case 2:
            printf("%d x %d = ?\b", num1, num2);
            scanf("%d", &answer);
            if (answer == num1 * num2) correct = 1;
            break;
        }

        sleep(1);
        system("clear");
        //퀴즈 맞추면 하나당 경험치 획득
        if (correct == 1)
        {
            FILE * o = NULL;
            memset(character.imgarr, 0, sizeof(character.imgarr));
            o = fopen("txt/o.txt", "r");
            fread(character.imgarr, 1, 9999, o);
            printf("%s\n", character.imgarr);
            fclose(o);

            printf("맞췄다!! \n");
            userS.xp += 50; qcount++;
            printf("경험치가 50만큼 올랐습니다. \n");
            if (userS.xp > 500) //xp 500당 레벨업
            {
                LevelUp(user_mon);
                LevelUp(devmon);
            }
            continue;
        }
        else //틀리면 hp -50%
        {
            FILE * x = NULL;
            memset(character.imgarr, 0, sizeof(character.imgarr));
            x = fopen("txt/x.txt", "r");
            fread(character.imgarr, 1, 9999, x);
            printf("%s\n", character.imgarr);
            fclose(x);

            printf("틀렸어!!! 공부 다시 하고 와!\n");
            MinusALLHp(user_mon, (userS.total_hp * 0.5) / CountMon(user_mon));
            return; //함수 종료(플레이어 위치 변화 없음)
        }
    }
    //다 맞췄을 시 Hp회복, 
    HealALLHp(user_mon);

    sleep(1);
    system("clear");
    FILE * heal = NULL;
    memset(character.imgarr, 0, sizeof(character.imgarr));
    heal = fopen("txt/heal.txt", "r");
    fread(character.imgarr, 1, 9999, heal);
    printf("%s\n", character.imgarr);
    fclose(heal);

    printf("체력이 모두 회복되었다! \n");
}

//mon 리스트 출력
void PrintingMon(DevMon* mon)
{
    for (int i = 0;i < CountMon(mon);i++) //개발몬 리스트 출력
    {
        printf("%d)", i + 1);
        printf("name: %s hp: %d mp: %d ", mon[i].name, mon[i].hp, mon[i].mp);
        printf("power: %d sk_power: %d\n", mon[i].power, mon[i].sk_power);
    }
}

//개발몬 이미지 출력 함수(imglist구조체 변수, 이미지 인덱스 입력 받음)
void PrintingImg(ImgList character,int idx)
{
    character.img[0]=fopen("txt/devmon00.txt", "r");
    character.img[1]=fopen("txt/devmon01.txt", "r");
    character.img[2]=fopen("txt/devmon02.txt", "r");
    character.img[3]=fopen("txt/devmon03.txt", "r");
    character.img[4]=fopen("txt/devmon04.txt", "r");
    if (character.img[idx] == NULL) return;
    memset(character.imgarr, 0, sizeof(character.imgarr));
    fread(character.imgarr, 1, 9999, character.img[idx]);
    printf("%s\n", character.imgarr);
    fclose(character.img[idx]);
}

//개발몬 선택(mon 리스트에서 선택한 멤버의 인덱스 반환)
int ChooseMon(DevMon* mon,ImgList character)
{
    int choose = 0, idx = 0; //선택 트리거, 인덱스 넘버
    int user; //입력 인자
    
    while (choose != 1)
    {
        system("clear");

        printf("함께할 개발몬을 선택해주세요> \n");
        PrintingImg(character,idx);

        printf("--------------------------------------------------------------------------------\n");
        printf("이름: %s\t HP: %-5d MP: %-5d 공격력: %-5d 특수공격력: %-5d \n", mon[idx].name, mon[idx].hp, mon[idx].mp, mon[idx].power, mon[idx].sk_power);
        printf("--------------------------------------------------------------------------------\n");
        printf("%s을 선택하시겠습니까?(선택: Y/다음으로: N): ", mon[idx].name);
        ClearBuffer();
        user = getchar();
        // y-> 해당 개발몬 정보 저장 / n-> 다음 개발몬 정보 출력 

        //입력값 검사
        if (user == 'y' || user == 'Y') choose = 1;
        else if (user == 'n' || user == 'N') idx = (idx + 1) % CountMon(mon);
        else
        {
            printf("잘못된 입력입니다. 다시 선택해주세요. \n");
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