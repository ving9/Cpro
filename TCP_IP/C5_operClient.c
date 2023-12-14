#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

void error_handling(char* message);

int main(int argc, char* argv[]){

    int sock;
    char opmsg[BUF_SIZE];
    int result, i;
    unsigned int opnd_cnt;
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

    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) // 1번인자 서버소켓이, 2,3번인자 서버에 접속하겠다는 의미
        error_handling("connect() error!");
    else
        puts("Connected..........");

    fputs("Operand count : ", stdout);
    scanf("%d", &opnd_cnt);
    opmsg[0]=(char)opnd_cnt;

    for(i=0; i<opnd_cnt; i++)
    {
        printf("Operand %d : ", i+1);
        scanf("%d", (int*)&opmsg[i*OPSZ+1]); // 사용자에게 연산할 숫자 입력 받는 과정
    }
    fgetc(stdin);
    fputs("Operator : ", stdout);
    scanf("%c", &opmsg[opnd_cnt*OPSZ+1]);
    write(sock, opmsg, opnd_cnt*OPSZ+2); // 왜?? 왜 +2까지 보내는거야 // 16 바이트 opnd_cnt*OPSZ+1 이 배열 인덱스에 마지막 연산자 넣었으니까 당연히.. 바이트는 배열0번부터 세니까

    read(sock, &result, RLT_SIZE); // 서버에서 보낸 결과값 수신

    printf("Operation result: %d \n", result);
    close(sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}