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
void* send_py(void* arg);                    // 파이썬 클라이언트 통신


// 임계영역 구성할 전역변수
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
    memset(&serv_adr, 0, sizeof(serv_adr));         // serv_adr 변수의 메모리를 모두 0으로 초기화
    serv_adr.sin_family = AF_INET;                  // IPv4 주소 사용
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);   // 소켓이 모든 네트워크 인터페이스에 들어오는 패킷을 수신
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
        // if (clnt_cnt <= 3)
        // {
        //     pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);

        //     // 종료된 쓰레드가 메모리에서 완전히 소멸
        //     // 쓰레드 생성 후 바로 detach 함수 호출하여 위 쓰레드가 종료되면 자동으로 메모리에서 해제
        //     pthread_detach(t_id);
        // }

        // 파이썬 연결
        pthread_create(&t_id, NULL, send_py, (void*)&clnt_sock);
        pthread_detach(t_id);

    }

    // close(serv_sock);
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
            return 0;
        }
    }
    else if (clnt_cnt == 2){
        sprintf(name, "%d_2013_chungbuck.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 3){
        sprintf(name, "%d_2013_daegu.csv", clnt_cnt);
        fname = fopen(name, "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 4){
        fname = fopen("2013대전.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 5){
        fname = fopen("2013강원.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 6){
        fname = fopen("2013광주.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 7){
        fname = fopen("2013경기.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 8){
        fname = fopen("2013제주.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 9){
        fname = fopen("2013전주.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 10){
        fname = fopen("2013서울.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    //================================================
    // 14년도 파일
    else if (clnt_cnt == 11){
        fname = fopen("2014부산.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 12){
        fname = fopen("2014충북.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }

    else if (clnt_cnt == 13){
        fname = fopen("2014대구.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }

    else if (clnt_cnt == 14){
        fname = fopen("2014대전.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 15){
        fname = fopen("2014강원.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 16){
        fname = fopen("2014광주.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 17){
        fname = fopen("2014경기.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 18){
        fname = fopen("2014제주.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 19){
        fname = fopen("2014전주.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
        }
    }
    else if (clnt_cnt == 20){
        fname = fopen("2014서울.csv", "w");
        if (fname == NULL){
            printf("파일오픈 실패! \n");
            return 0;
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


void* send_py(void* arg)
{
    int clnt_sock=*((int*)arg);
    char buf[1024];      
    char* buf_send[1024];

    char num;
    read(clnt_sock, &num, sizeof(num));

    pthread_mutex_lock(&mutx);
    if (num == 'd')
    {
        
        FILE* fp = fopen("1_2013_busan.csv", "rb");
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(buf, sizeof(buf), fp);//받는다
            char *ptr = strtok(buf,",");//자른다 쉼표기준으로
            for (int i = 0; i < 3; i++) 
            {
                if (i==0 || i==1 || i==2) // 문자열내의 0,1,5,14 번 뽑는다
                {
                    buf_send[i] = ptr;
                    send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
                    send(clnt_sock,",",1,0);
                }
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
        }
        fclose(fp);
    }
    // else if (num == 'b')
    // {
    //     FILE* fp = fopen("seoule13.csv", "rb");
  
    //     while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
    //     {
    //         fgets(buf, sizeof(buf), fp);//받는다
    //         char *ptr = strtok(buf,",");//자른다 쉼표기준으로
    //         for (int i = 0; i < 4; i++) // 문자열 15번 반복
    //         {
    //             buf_send[i] = ptr;
    //             if (i==0 || i==2 || i==3) // 문자열내의 0,2,3 번 뽑는다
    //             {
    //                 send(clnt_sock, buf_send[i], strlen(buf_send[i]), 0); // 출력한것들 보낸다 한 줄씩
    //                 send(clnt_sock,",",1,0);
    //             }
    //             ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
    //         }
    //     }
    //     fclose(fp);
    // }



    shutdown(clnt_sock, SHUT_WR);
    close(clnt_sock);
    pthread_mutex_unlock(&mutx);
    return NULL;
}