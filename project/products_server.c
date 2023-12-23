#include <stdio.h> //입출력
#include <stdlib.h> //문자열 변환, 의사 난수 생성
#include <unistd.h> //표준 심볼 상수 및 자료형
#include <string.h> //문자열 상수
#include <arpa/inet.h> //주소변환
#include <sys/socket.h> //소켓 연결
#include <netinet/in.h> //IPv4 전용 기능
#include <pthread.h> //쓰레드 사용
#include <locale.h>

#define BUF_SIZE 1024                  // 버퍼 사이즈
#define MAX_CLNT 256

void error_handling(char* message);
void* handle_clnt(void* arg);               // C클라이언트 파일 쓰레드 통신
void* handle_2022(void* arg);               
void* send_py(void* arg);                 // 파이썬 클라이언트 통신

// 임계영역 구성할 전역변수
int clnt_cnt = 0;               // 현재 연결된 클라이언트 수
int clnt_socks[MAX_CLNT];       // 클라이언트 소켓 디스크립터 저장
int socks_2022[11];             // 2022년도 클라이언트와 접속한 소켓을 저장하기 위한 배열
pthread_mutex_t mutx;           // 뮤텍스 생성을 위한 변수 선언

int main(){

    int serv_sock, clnt_sock;                   // 서버 소켓, 클라이언트 소켓
    struct sockaddr_in serv_adr, clnt_adr;      // 서버 소켓 주소, 클라이언트 소켓 주소
    int clnt_adr_sz;                            // 클라이언트 소켓 주소 정보의 크기
    pthread_t t_id;                             // 쓰레드 생성에 사용될 쓰레드 변수

    // 뮤텍스 초기화 (뮤텍스 변수 전달)
    pthread_mutex_init(&mutx, NULL);

    // 서버 소켓 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    // 한글 깨져서 넣어줌
    setlocale(LC_ALL, "en_US.UTF-8");

    // 주소 초기화 및 설정
    memset(&serv_adr, 0, sizeof(serv_adr));         // serv_adr 변수의 메모리를 모두 0으로 초기화
    serv_adr.sin_family = AF_INET;                  // IPv4 주소 사용
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);   // 소켓이 모든 네트워크 인터페이스에 들어오는 패킷을 수신
    serv_adr.sin_port = htons(8888);             // 서버 포트 번호 설정 8888

    // 주소 할당 및 연결요청 대기
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))== -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5)==-1)
        error_handling("listen() error");


    // 클라이언트 연결 수락
    while(1){
    
        clnt_adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

        pthread_mutex_lock(&mutx);      // 뮤텍스 LOCK: 다른 쓰레드가 자원에 접근X

        // 연결된 클라이언트의 정보를 배열에 저장
        clnt_socks[clnt_cnt++] = clnt_sock;     // 새로운 연결이 형성될 때마다 변수 clnt_cnt 배열 clnt_socks에 해당 정보를 등록
        
        pthread_mutex_unlock(&mutx);    // 뮤텍스 LOCK 해제

        // 클라이언트에 서비스를 제공하기 위한 쓰레드 생성
        if (clnt_sock <= 20)
        {
            pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
            pthread_detach(t_id);
        }

        // if(clnt_sock <= 31)   // 2022년 클라이언트를 따로 시도해봤으나 원하는대로 작동되지 않음
        // {
        //     socks_2022[0] = clnt_sock;
        //     pthread_create(&t_id, NULL, handle_2022, (void*)&clnt_sock);
        //     pthread_detach(t_id);
        // }

        // 파이썬 통신 쓰레드 생성
        else
        {
            pthread_create(&t_id, NULL, send_py, (void*)&clnt_sock);
            pthread_detach(t_id);
        }
        
    }

    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


// C클라이언트 파일 쓰레드
void* handle_clnt(void* arg){           // arg: (void*)&clnt_sock
    int clnt_sock = *((int*)arg);       // 클라이언트와의 통신에 사용되는 소켓 디스크립터
    int str_len = 0;                 // 클라이언트로부터 수신한 메시지의 길이를 저장
    char msg[BUF_SIZE];                 // 클라이언트로부터 수신한 메시지를 저장할 문자열 배열
    char name[50];
    FILE* fname;


    // new파일 생성
    pthread_mutex_lock(&mutx);          // 뮤텍스 LOCK: 다른 쓰레드가 자원에 접근X
    if (clnt_cnt == 1){
        sprintf(name, "%d_2013_busan.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 2){
        sprintf(name, "%d_2013_chungbuck.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 3){
        sprintf(name, "%d_2013_daegu.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 4){
        sprintf(name, "%d_2013_daejeon.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 5){
        sprintf(name, "%d_2013_gangwon.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 6){
        sprintf(name, "%d_2013_gwangju.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 7){
        sprintf(name, "%d_2013_gyeonggi.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 8){
        sprintf(name, "%d_2013_jeju.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 9){
        sprintf(name, "%d_2013_jeonju.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 10){
        sprintf(name, "%d_2013_seoul.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    //================================================
    // 14년도 파일
    else if (clnt_cnt == 11){
        sprintf(name, "%d_2014_busan.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 12){
        sprintf(name, "%d_2014_chungbuk.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }

    else if (clnt_cnt == 13){
        sprintf(name, "%d_2014_daegu.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }

    else if (clnt_cnt == 14){
        sprintf(name, "%d_2014_daejeon.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 15){
        sprintf(name, "%d_2014_gangwon.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 16){
        sprintf(name, "%d_2014_gwangju.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 17){
        sprintf(name, "%d_2014_gyeonggi.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 18){
        sprintf(name, "%d_2014_jeju.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 19){
        sprintf(name, "%d_2014_jeonju.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    else if (clnt_cnt == 20){
        sprintf(name, "%d_2014_seoul.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }

    while((str_len = read(clnt_sock, msg, sizeof(msg))) != 0){            // 파일의 끝에 도달한 경우 0이 아닌 값 반환
        msg[str_len] = '\0';
        fputs(msg, fname);
        printf("%s", msg);
    }
    fclose(fname);
    pthread_mutex_unlock(&mutx);        // 뮤텍스 LOCK 해제

    
    close(clnt_sock);
    return NULL;
}

// 2022년 C클라이언트 파일 쓰레드 (동작 안함)
void* handle_2022(void* arg)
{
    int clnt_sock = *((int*)arg);   
    int str_len = 0;               
    char msg[BUF_SIZE];         
    char name[50];
    FILE* fname;

    pthread_mutex_lock(&mutx);    
    if (clnt_cnt == 21){
        sprintf(name, "%d_2022_busan.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }

    while((str_len = read(clnt_sock, msg, sizeof(msg))) != 0){    
        msg[str_len] = '\0';
        fputs(msg, fname);
        printf("%s", msg);
    }
    fclose(fname);
    pthread_mutex_unlock(&mutx);   
    return NULL;
}

// 파이썬과 통신하는 쓰레드
void* send_py(void* arg)
{
    int clnt_sock=*((int*)arg);
    char buf[256];      
    char* buf_send[8];

    char num;
    read(clnt_sock, &num, sizeof(num));
    pthread_mutex_lock(&mutx);
    if (num == 'a')
    {
        printf("%c", num);
        FILE* fp = fopen("1_2013_busan.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'b')
    {
        printf("%c", num);
        FILE* fp = fopen("2_2013_chungbuck.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'c')
    {
        FILE* fp = fopen("3_2013_daegu.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'd')
    {
        FILE* fp = fopen("4_2013_daejeon.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'e')
    {
        FILE* fp = fopen("5_2013_gangwon.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'f')
    {
        FILE* fp = fopen("6_2013_gwangju.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'g')
    {
        FILE* fp = fopen("7_2013_gyeonggi.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'h')
    {
        FILE* fp = fopen("8_2013_jeju.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'i')
    {
        FILE* fp = fopen("9_2013_jeonju.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'j')
    {
        FILE* fp = fopen("10_2013_seoul.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'k')
    {
        FILE* fp = fopen("11_2014_busan.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'l')
    {
        FILE* fp = fopen("12_2014_chungbuk.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'm')
    {
        FILE* fp = fopen("13_2014_daegu.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'n')
    {
        FILE* fp = fopen("14_2014_daejeon.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'o')
    {
        FILE* fp = fopen("15_2014_gangwon.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'p')
    {
        FILE* fp = fopen("16_2014_gwangju.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'q')
    {
        FILE* fp = fopen("17_2014_gyeonggi.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'r')
    {
        FILE* fp = fopen("18_2014_jeju.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 's')
    {
        FILE* fp = fopen("19_2014_jeonju.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 't')
    {
        FILE* fp = fopen("20_2014_seoul.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    else if (num == 'A') // 2022년 테스트를 위해 만들었지만 여기서 특정 소켓으로 데이터 전송하는 데에 실패...
    {
        printf("%c", num);
        write(socks_2022[0], &num, 1);
        FILE* fp = fopen("1_2022_busan.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                buf_send[i] = ptr;
                send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                send(clnt_sock,",",1,0);
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }

    shutdown(clnt_sock, SHUT_WR);
    shutdown(clnt_sock, SHUT_RD);
    pthread_mutex_unlock(&mutx);
    return NULL;
}