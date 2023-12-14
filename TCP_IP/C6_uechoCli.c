#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char* argv[]){

    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t adr_sz;
    struct sockaddr_in serv_adr, from_adr;

    if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    while(1)
    {
        fputs("Insert message(q to quit) : ", stdout);
        fgets(message, sizeof(message), stdin);

        if(!strcmp(message,"q\n") || !strcmp(message, "Q\n")) // 0이 같을때니까
        // 0일때 ! 연산자 때문에 참이 되어 브레이크
            break;
        
        sendto(sock, message, strlen(message), 0,
        (struct sockaddr*)&serv_adr, sizeof(serv_adr));
        // 서버로 데이터를 전송하는중
        // 자기 자신의 IP와 PORT는 따로 설정 안해주면 sento 함수 호출할 때
        // 자동으로 설정된다
        // PORT 는 랜덤으로 할당

        adr_sz = sizeof(from_adr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0,
        (struct sockaddr*)&from_adr, &adr_sz);
        message[str_len] = 0;
        printf("%d\n\n", str_len);
        printf("Message from server : %s", message);
    }
    close(sock);
    return 0;
}



void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}