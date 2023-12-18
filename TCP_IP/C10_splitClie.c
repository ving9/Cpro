#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char* message);
void read_routine(int sock, char* buf);
void write_routine(int sock, char* buf);

int main(int argc, char*argv[]){

    int sock;
    pid_t pid;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_adr;

    if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");

    pid = fork();
    if(pid==0)
        write_routine(sock, buf);
    else
        read_routine(sock, buf);
    
    close(sock);
    return 0;
}

void read_routine(int sock, char* buf)
{
    while(1)
    {
        int str_len = read(sock, buf, BUF_SIZE);
        if(str_len == 0)
            return;
        buf[str_len] = 0;
        printf("Message from server: %s\n", buf);
    }
}

void write_routine(int sock, char* buf)
{
    while(1)
    {
        fgets(buf, BUF_SIZE, stdin);
        if(!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) // 두 문자열 비교해서 같으면 0 아니면 0아닌값
        {
            shutdown(sock, SHUT_WR); // 지금 fd를 복사해온 상태기 때문에 이 함수를 나가서 close(sock) 을 만난다고 해도 EOF가 전달된다고 확답할 수 없음
            // (부모의 fd도 살아 있을 수 있기 때문이다) 그래서 명시적으로 EOF를 전달해 준다고 생각하라
            return;
        }
        write(sock, buf, strlen(buf));
    }
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}