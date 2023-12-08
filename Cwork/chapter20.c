#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int RspResult(int num1, int num2);
void BaseballResult(int* arr1,int* arr2,int* arr3);

int main(void)
{
    srand(time(0));


    // 도전 01
    // int spinArr[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    // int tempArr[4][4]; // 기존의 모습을 담을 배열
    // int x,y,cnt,times;
    // for(times = 0; times < 4; times++)
    // {
    //     cnt = 3; // 배열을 90도로 돌리기 위한 고정값
    //     for(x=0; x<4; x++)
    //     {
    //         for(y=0; y<4; y++)
    //         {
    //             printf("%3d",spinArr[x][y]);
    //             tempArr[x][y] = spinArr[x][y]; // 원래 형태 프린트 한후 저장하기
    //         }
    //         printf("\n");
    //     }
    //     for(x=0; x<4; x++)
    //     {
    //         for(y=0; y<4; y++)
    //         {
    //             spinArr[y][cnt] = tempArr[x][y]; // 형태를 바꿔서 원래 배열에 집어넣는 과정
    //         }
    //         cnt--;
    //     }
    //     printf("\n");
    // }

    //도전 02
    int input_; //받아올 자연수 
    int cnt; //진행할 턴수 
    int x; // 각 턴마다 배열에서 움직이는 수
    int y; // 출력할때 쓸 변수

    printf("얼마나 큰 달팽이가 보고 싶나요 (자연수 입력) : ");
    scanf("%d", &input_);
    int arr[input_][input_];
    int writeNum = 1; // 1씩 증가하며 배열에 입력될 수
    // int numTarget = (input_ * input_);
   
    for(cnt = 0;cnt<input_/2;cnt++)
    {
        int checkNum = (input_-1)-cnt;
        for(x = cnt; x < checkNum; x++)
        {
            arr[cnt][x] = writeNum;
            writeNum++;
        }
        for(x = cnt; x < checkNum; x++)
        {
            arr[x][checkNum] = writeNum;
            writeNum++;
        }
        for(x = checkNum; x > cnt; x--)
        {
            arr[checkNum][x] = writeNum;
            writeNum++;
        }
        for(x = checkNum; x > cnt; x--)
        {
            arr[x][cnt] = writeNum;
            writeNum++;
        }
        if(cnt == (input_/2)-1 && input_ % 2 != 0)
        {
            arr[input_/2][input_/2] = writeNum;
        }       
    }
    for(x=0; x<input_; x++)
    {
        for(y=0; y<input_; y++)
            printf("%4d", arr[x][y]);
        printf("\n");
    }
    printf("\n\n");



    // //도전 03
    // int i;
    // printf("난수의 범위: 0부터 %d까지 \n", RAND_MAX);
    // for(i=0; i<5; i++)
    // {
    //     printf("난수 출력: %d \n", rand() % 100);
    // }

    // //도전 04
    // int dice_01, dice_02;
    
    // dice_01 = rand() % 6 + 1;
    // dice_02 = rand() % 6 + 1;
    // printf("주사위 1의 결과 : %d\n주사위 2의 결과 : %d\n", dice_01, dice_02);

    // 도전 05
    // int input_; // 입력받을 숫자
    // int cpu; // 컴퓨터가 내는 가위바위보
    // int result; // 가위바위보 승패
    // int result2[2] = {0,}; // 게임 결과 저장
    // char* rsp[3] = {"가위","바위","보"}; // 결과 보여줄 때 써먹어야징
    // char* ment[3] = {"이겼습니다","비겼습니다","당신은 패배하였습니다"};
    // while(1)
    // {
    //     printf("가위바위보 게임! 1)가위 2)바위 3)보 (숫자로입력) : ");
    //     scanf("%d", &input_);
    //     cpu = rand() % 3 + 1;
    //     result = RspResult(input_, cpu);
    //     printf("당신은 %s 선택 컴퓨터는 %s 선택, %s!\n", rsp[input_-1], rsp[cpu-1], ment[result]);
    //     if(result == 2)
    //         break;
    //     result2[result] += 1;
    // }
    // printf("게임의 결과 : %d승 %d무\n\n", result2[0],result2[1]);

    // // 도전 06
    // int i;
    // int cpuNum[3] = {}; // 컴퓨터 넘버
    // int inputNum[3] = {}; // 입력 넘버
    // int result[2] = {0,}; // 야구 게임 결과 저장 0번 ball 1번 strike
    // int cnt = 1; // 야구 게임 도전 라운드
    // for(i=0; i<3; i++)
    // {
    //     cpuNum[i] = rand() % 10;
    //     if(cpuNum[i] == cpuNum[i-1] || cpuNum[i] == cpuNum[i-2]) // 중복 방지 이렇게밖에 안되나...?
    //         i--;
    // }
    // for(i=0; i<3; i++)
    // {
    //     printf("%d\n", cpuNum[i]);
    // }
    // while(1)
    // {
    //     printf("3개의 숫자 선택 (띄어쓰기로 구분): ");
    //     scanf("%d %d %d", &inputNum[0], &inputNum[1], &inputNum[2]);
    //     if(inputNum[0] == inputNum[1] || inputNum[0] == inputNum[2] || inputNum[1] == inputNum[2])
    //     {
    //         printf("동일한 수를 입력하지 마세요\n");
    //         continue;
    //     }
    //     else
    //     {
    //         BaseballResult(inputNum, cpuNum, result);
    //         printf("%d번째 도전 결과 : %d strike, %d ball \n", cnt, result[0], result[1]);
    //         if(result[0] == 3)
    //         {
    //             printf("게임종료. %d번째 도전만에 성공!\n\n", cnt);
    //             break;
    //         }
    //         cnt++;
    //     }
    // }



    return 0;
}








void BaseballResult(int* arr1,int* arr2,int* arr3)
{
    int x, y;
    int ball = 0, strike = 0;
    for(x=0; x<3; x++)
    {
        for(y=0; y<3; y++)
        {
            if(arr1[x] == arr2[y] && x == y)
                strike++;
            else if(arr1[x] == arr2[y])
                ball++;
        }
    }
    arr3[0] = strike;
    arr3[1] = ball;
}



int RspResult(int num1, int num2)
{
    int result;
    if(num1 > num2)
        result = 0;
    else if(num1 == 1 && num2 == 3)
        result = 0;
    else if(num1 == num2)
        result = 1;
    else
        result = 2;
    return result;
}

