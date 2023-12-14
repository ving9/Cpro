#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char* argv[]){

    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    

    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_adr_sz = sizeof(clnt_adr);

    for(i=0; i<5; i++){
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); // 서버가 실행되면 여기에서 클라이언트가 커넥트 하기 전까지 블로킹 상태
        // 클라이언트와 소통할 소켓
        if (clnt_sock == -1) // 연결 실패 알려줌
            error_handling("accept() error");
        else
            printf("Connected client %d \n", i+1);
        while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0){ // 클라이언트와 연결되고 나서 여기서 멈춰있게된다
        // clnt_sock을 통해 수신한 데이터를 message에 저장하는거야 buf_size 만큼
        // 서버쪽에서 q를 입력하는 순간 close()가 작동되고
        // EOF(엔드오브파일) 메세지가 전송되며 수신함수는 0을 배출한다
        // str_len = write(sock, message, strlen(message)) 이렇게 보냈으니 마지막에 널문자 없음
            write(clnt_sock, message, str_len);
            // message에 있는 데이터를 str_len만큼 보냄... 
            printf("%d\n", str_len);
        }
        printf("%d\n", str_len);
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}