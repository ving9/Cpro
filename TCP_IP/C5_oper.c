#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4
void error_handling(char* message);
int calculate(int opnum, int opnds[], char oprator);

int main(int argc, char* argv[]){

    int serv_sock, clnt_sock;
    char opinfo[BUF_SIZE];
    int result, opnd_cnt, i;
    int recv_cnt, recv_len;
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
        opnd_cnt = 0;
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        read(clnt_sock, &opnd_cnt, 1); // 일단 여기서 1바이트 크기만 opnd_cnt로 가져온다 (클라이언트가 라이트 한거에서...)

        recv_len = 0;
        while((opnd_cnt*OPSZ+1)>recv_len)
        {
            recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE-1); // 클라이언트에서 라이트한 배열 끝까지 받는 과정
            recv_len += recv_cnt;
        }
        result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]); //계산하려고 넣어준다 매개1 받을 정수갯수, 매개2 저장된 정수들, 매개3 연산자
        write(clnt_sock, (char*)&result, sizeof(result)); // 결과값을 왜 char* 이걸로 형변환 해서 주는거지? 1바이트씩 주고싶어서?
        // 윈도우에서는 send 함수를 쓰는게 거기서 2번 매개변수가 무조건 (char*)형으로 받기때문에 습관적으로 쓴것
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}
int calculate(int opnum, int opnds[], char op)
{
    int result = opnds[0], i;
    switch(op){
        case '+':
            for(i=1; i<opnum; i++) result+=opnds[i];
            break;
        case '-':
            for(i=1; i<opnum; i++) result-=opnds[i];
            break;
        case '*':
            for(i=1; i<opnum; i++) result*=opnds[i];
            break;
    }
    return result;
}



void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}