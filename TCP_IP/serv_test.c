// 쓰레드 수정중

#include <stdio.h> //입출력
#include <stdlib.h> //문자열 변환, 의사 난수 생성
#include <unistd.h> //표준 심볼 상수 및 자료형
#include <string.h> //문자열 상수
#include <arpa/inet.h> //주소변환
#include <sys/socket.h> //소켓 연결
#include <netinet/in.h> //IPv4 전용 기능
#include <pthread.h> //쓰레드 사용
#include <locale.h>

#define BUF_SIZE 1024                   // 버퍼 사이즈
#define MAX_CLNT 256

// 필요한 함수
void error_handling(char* message);         // 오류처리
void* handle_clnt(void* arg);               // C클라이언트 파일 쓰레드


// 임계영역 구성할 전역변수
// C 클라이언트
int clnt_cnt = 0;               // 현재 연결된 클라이언트 수
int clnt_socks[MAX_CLNT];       // 클라이언트 소켓 디스크립터 저장


pthread_mutex_t mutx;                   // 뮤텍스 생성을 위한 변수 선언


int main(int argc, char* argv[]){
    argc = 2;
    argv[1] = "8889";

    int serv_sock, clnt_sock;                   // 서버 소켓, 클라이언트 소켓
    struct sockaddr_in serv_adr, clnt_adr;      // 서버 소켓 주소, 클라이언트 소켓 주소
    int clnt_adr_sz;                            // 클라이언트 소켓 주소 정보의 크기
    
    pthread_t t_id;                             // 쓰레드 생성에 사용될 쓰레드 변수

    if (argc!=2){
        printf("Usage: %s <port>\n", argv[0]);      // argv[0]: 포트번호
        exit(1);                                    // 비정상적인 종료
    }

    // 뮤텍스 초기화 (뮤텍스 변수 전달)
    pthread_mutex_init(&mutx, NULL);

    // 서버 소켓 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    // 한글 깨져서 넣어줌
    setlocale(LC_ALL, "en_US.UTF-8");

    // 주소 초기화 및 설정
    memset(&serv_adr, 0, sizeof(serv_adr));               // serv_adr 변수의 메모리를 모두 0으로 초기화
    serv_adr.sin_family = AF_INET;                        // IPv4 주소 사용
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);         // 소켓이 모든 네트워크 인터페이스에 들어오는 패킷을 수신
    serv_adr.sin_port = htons(atoi(argv[1]));             // 서버 포트 번호 설정 8888

    // 주소 할당 및 연결요청 대기
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))== -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5)==-1)
        error_handling("listen() error");



    // ===========================================================
    // 클라이언트 연결 수락
    while(1){
    
        clnt_adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);


        /******************/
        /* 임계 영역 개크게시작 */
        pthread_mutex_lock(&mutx);      // 뮤텍스 LOCK: 다른 쓰레드가 자원에 접근X

        // 연결된 클라이언트의 정보를 배열에 저장
        clnt_socks[clnt_cnt++] = clnt_sock;     // 새로운 연결이 형성될 때마다 변수 clnt_cnt 배열 clnt_socks에 해당 정보를 등록
        
        pthread_mutex_unlock(&mutx);    // 뮤텍스 LOCK 해제
        /* 임계영역 개크게종료 */
        /******************/


        // 클라이언트에 서비스를 제공하기 위한 쓰레드 생성
        // 1~10
        pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);

        // 종료된 쓰레드가 메모리에서 완전히 소멸
        // 쓰레드 생성 후 바로 detach 함수 호출하여 위 쓰레드가 종료되면 자동으로 메모리에서 해제
        pthread_detach(t_id);
    }

    close(serv_sock);
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
    int str_len = 0, i;                 // 클라이언트로부터 수신한 메시지의 길이를 저장
    char msg[BUF_SIZE];                 // 클라이언트로부터 수신한 메시지를 저장할 문자열 배열

    char name[10];                      // 13년도 파일
    FILE* fname;

    char name2[10];                     // 14년도 파일
    FILE* fname2;

    char name3[10];                      // 전체파일
    FILE* fname3;




    // new파일 생성
    pthread_mutex_lock(&mutx);          // 뮤텍스 LOCK: 다른 쓰레드가 자원에 접근X
    if (clnt_cnt == 1){
        fname = fopen("부산2013.csv", "w");                   //13년
        fname2 = fopen("부산2014.csv", "w");                 //14년
        fname3 = fopen("부산.csv", "w");                 //전체

        if (fname == NULL || fname2 == NULL || fname3 == NULL){
            printf("파일오픈 실패! \n");
            return -1;
        }
    }
    pthread_mutex_unlock(&mutx);        // 뮤텍스 LOCK 해제

    // char* ptr = strchr(msg, "2013");

    // 0번째 요소 뽑아서 비교하고 그 행을 파일에 넣기
    // while((str_len = read(clnt_sock, msg, sizeof(msg))) != 0){            // 파일의 끝에 도달한 경우 0이 아닌 값 반환
    //     msg[str_len] = '\0';
    //     if (strcmp(msg, "2013") == 0){       // 문자열 비교하고 같으면 0 반환
    //         fputs(msg, fname);               // fname 파일에 msg 버퍼 넣기
    //         printf("%s", msg);
    //     }
    //     else{
    //         fput(msg, fname2);               // fname 파일에 msg 버퍼 넣기
    //         printf("%s", msg);
    //     }
    // }


    pthread_mutex_lock(&mutx);          // 뮤텍스 LOCK: 다른 쓰레드가 자원에 접근X
    while((str_len = read(clnt_sock, msg, sizeof(msg))) != 0){
        if (msg == "a"){
            break;
        }
        msg[str_len] = '\0';
        fputs(msg, fname);
        // printf("%s", msg);
    }
    pthread_mutex_unlock(&mutx);        // 뮤텍스 LOCK 해제


    // char separation[BUF_SIZE]; // 파일 열고 넣을 배열
    // char separation_1[BUF_SIZE]; // 파일 열고 넣을 배열


    // pthread_mutex_lock(&mutx);          // 뮤텍스 LOCK: 다른 쓰레드가 자원에 접근X

    // while (!feof(fname3)) // fp 파일의 끝이 아니라면 반복
    // {
    //     while(fgets(separation, sizeof(separation), fname3) != NULL){   // 한줄읽음
    //         // if (strncmp(separation, "2013", 4) == 0){
    //         //     fprintf(fname, separation_1[i]);
    //         //     fprintf(fname, ",");
    //         // }
    //         // else if (strncmp(separation, "2014", 4) == 0){
    //         //     fprintf(fname2, separation_1[i]);
    //         //     fprintf(fname2, ",");
    //         // }
    //         for (int i = 0; i < 4; i++)
    //         {
    //             printf("%s", separation);
    //         }
    //     }
    //     fprintf(fname, "\n");
    // }

    // while (read(fname3, separation, sizeof(separation))){
    //     while (fgets(separation, sizeof(separation), fname3) != NULL){
    //         printf("%s", separation);
    //         if (strncmp(separation, "2013", 4) == 0){
    //             fprintf(fname, separation);
    //             // fprintf(fname, ",");
    //         }
    //     }
    // }    
    // pthread_mutex_unlock(&mutx);        // 뮤텍스 LOCK 해제
    

    // 13,14년도 분리
    // while (!feof(fname3)) // fp 파일의 끝이 아니라면 반복
    // {
    //     // read(clnt_sock, msg, sizeof(msg));
    //     fgets(separation, sizeof(separation), fname3);

    //     char *ptr = strtok(separation,",");
        
    //     for (int i = 0; i < 4; i++)
    //     {
    //         separation_1[i] = ptr;
    //         if (strncmp(separation_1[0], "2013", 4) == 0)
    //         {
    //             fprintf(fname, separation_1[i]);
    //             fprintf(fname, ",");
    //         }
    //         else if (strncmp(separation_1[0], "2014", 4) == 0)
    //         {
    //             fprintf(fname, separation_1[i]);
    //             fprintf(fname, ",");
    //         }
    //         ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
    //     }
    //     fprintf(fname, "\n");
    // }


        
        // fgets(separation, sizeof(separation), fname3);        // 전체 파일 배열에 넣음
        // // char *ptr = strtok(separation,"2013");    //자른다 쉼표기준으로

        // printf("\n");


    // while((str_len = read(clnt_sock, msg, sizeof(msg))) != 0){            // 파일의 끝에 도달한 경우 0이 아닌 값 반환
    //     msg[str_len] = '\0';
    //     if (i==0 || i==1 || i==5 || i==14) // 문자열내의 0,1,5,14 번 뽑는다
    //     {
    //         printf("%s,",str[i]); 
    //         send(sd, str[i], strlen(str[i]), 0); // 출력한것들 보낸다 한 줄씩
    //         send(sd,",",1,0);
    //     }
    //     fputs(msg, fname);
    //     printf("%s", msg);
    // }


    fclose(fname);
    fclose(fname2);
    fclose(fname3);
    close(clnt_sock);
    return NULL;
}