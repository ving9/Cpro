#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char* message);

int main(int argc, char* argv[]){

    int sock;
    struct sockaddr_in serv_adr;
    char message[BUF_SIZE];
    int str_len, recv_len, recv_cnt;

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
    
    while(1){
        fputs("Input message(Q to quit) : ", stdout);
        fgets(message, BUF_SIZE, stdin); // 여기서 넘어가려며 엔터를 쳐야되니 message의 길이는 최소 1

        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        str_len = write(sock, message, strlen(message)); // strlen = 마지막 널문자를 제외한 길이 만큼 message에 있는 정보를 sock이라는 클라이언트 소켓에 보내겠다.
        // 아하 write함수는 비트의 크기만큼 보내기 때문에 문자열의 길이만큼 보내면 마지막 널문자는 보내지지 않음
        // 결국 30자를 입력하면 보내지는건 개행 문자 포함 29문자
        // 아...그래서 다시 읽을때 BUF_SIZE-1 해주는구나
        recv_len = 0;
        // str_len = read(clnt_sock, message, BUF_SIZE) 서버에서 수신하는 과정 (엔터까지 포함한 message)

        while(recv_len<str_len)
        {   // 서버에서 송신하는 과정 write(clnt_sock, message, str_len);
            recv_cnt = read(sock, &message[recv_len], BUF_SIZE-1); // 왜 buf_size-1 까지만 읽을까? 마지막에는 널문자 들어와야 하니까...!
            // 2번 인자가 저렇게 되어있는 이유는 한번더 실행되었을때 읽었던 곳 다음부터 읽어오려고 (배열은 0부터 시작하니 자동으로 +1된 효과)
            // 이렇게 와일문을 구성 해놓으면 끝까지 다 못읽었을때 read로 recv_cnt가 str_len 될때까지 읽기 때문
            if(recv_cnt == -1)
                error_handling("read() error!");
            recv_len += recv_cnt;
        }
        message[recv_len] = 0; // 이것은 통신해서 주고받은 것이니까 마지막에 널문자 없음
        printf("Message from server: %s\n", message);

        // write(sock, message, strlen(message));
        // str_len = read(sock, message, BUF_SIZE-1);
        // message[str_len] = 0;
        // printf("Message from server : %s", message);
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