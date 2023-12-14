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
    socklen_t adr_sz; // 불필요해짐
    struct sockaddr_in serv_adr, from_adr; // from_adr 불필요 해짐

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

    connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

    while(1)
    {
        fputs("Insert message(q to quit) : ", stdout);
        fgets(message, sizeof(message), stdin);
        // 30자를 넘어가게치면??
        // 29개까지 문자 들어오고 마지막은 널문자되야함
        // 나머지는 그냥 입력 버퍼에 남아있음

        if(!strcmp(message,"q\n") || !strcmp(message, "Q\n")) // 0이 같을때니까
        // 0일때 ! 연산자 때문에 참이 되어 브레이크
            break;
        
        // sendto(sock, message, strlen(message), 0,
        // (struct sockaddr*)&serv_adr, sizeof(serv_adr));
        write(sock, message, strlen(message)); // 문자 4개를 쓰고 엔터를 치면 총 길이는 5 널문자포함 6 strlen으로 나오는건 5 보내지는건 문자4개랑 \n
        // 어차피 fgets에서 받을때 30문자 입력해도 마지막에 널문자 넣잖아?
        printf("%ld", strlen(message));


        // adr_sz = sizeof(from_adr);
        // str_len = recvfrom(sock, message, BUF_SIZE, 0,
        // (struct sockaddr*)&from_adr, &adr_sz);

        str_len = read(sock, message, sizeof(message));  // 최대 29바이트 까지만 받음 왜냐?
        // 그래야 인덱스로 불렀을때 최대 29가 되면서 오류가 안난다
        // 이건 오직 str_len이 30이 되버리는 상황을 막기 위한것
        // 근데 -1 안해도 알아서 29에서 짜르는데?
        // UDP라서..?
        printf("%d\n\n", str_len);
        message[str_len] = 0; // 이걸 안해주면 출력은 제대로 되지만 쓸데 없는 빈 공간도 전부다 출력되고 있는 상태임? // 쓰레기값이 안뜨는 것은 순전 운?
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