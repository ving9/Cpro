#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
void error_handling(char *message);

int main(int argc, char *argv[]){
    int i;
    struct hostent *host;
    if(argc!=2){
        printf("Usage : %s <addr> \n", argv[0]);
        exit(1);
    }

    host = gethostbyname(argv[1]);
    if(!host)
        error_handling("gethost... error");

    printf("Official name: %s \n", host->h_name);
    
    for(i=0; host->h_aliases[i]; i++)
        printf("Aliases %d : %s \n", i+1, host->h_aliases[i]);

    printf("Address type : %s \n",
    (host->h_addrtype == AF_INET) ? "AF_INET" :"AF_INET6");

    for(i=0; host->h_addr_list[i]; i++)
        printf("IP addr %d : %s \n", i+1,
        inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
        // in_addr은 ipv4 ip(32비트정수형)를 저장하기 위한 구조체
        // 반면 hostent 구조체는 여러가지 주소정보를 받기위해 설계 되있으므로
        // h_addr_list 안에는 일단 char형 포인터 배열이 들어있다
        // 저렇게 호출하면 32비트 정수가 나오니까 inet_ntoa 함수로 문자열로 바까줌

    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}