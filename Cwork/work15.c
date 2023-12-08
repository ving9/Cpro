#include <stdio.h>
int RemainDay(int year, int month);

int main(void)
{
    int year = 1900; // 1월 1일이 무슨 요일인지 알고 있는 년도
    int yearTarget = 2000;
    int month;
    int daycheck = 2; // 1일요일 2월요일 3화요일 .... 7토요일
    int cnt = 0; // 매 월 1일이 일요일일때 갯수를 세는 변수
    int remain; // 매 월을 7로 나누고 난 나머지
    
    for(; year <= yearTarget; year++)
    {
        for(month = 1; month <= 12; month++)
        {
            if(daycheck == 1 && year != 1900)
            {
                cnt++;
                printf("%d년의 %d월은 1일이 일요일입니다\n", year, month);
            }
            remain = RemainDay(year, month); // 윤년을 계산하여 매 월을 7로 나눈 나머지를 결과값으로 주는 함수 
            daycheck += remain;
            if(daycheck > 7)
                daycheck -= 7;
        }
    }
    year = 1901;
    printf("%d년부터 %d년까지 매월 1일이 일요일인 경우는 총 %d번 입니다\n\n", year, yearTarget, cnt);


    return 0;
}



int RemainDay(int year, int month) 
{
    int remain;
    if(month == 4 || month == 6 || month == 9 || month == 11)
        remain = 2;
    else if (month == 2)
    {
        if(year % 100 == 0 && year % 400 == 0)
            remain = 1;
        else if(year % 4 == 0)
            remain = 1;
        else
            remain = 0;       
    }
    else
        remain = 3;
    
    return remain;
}