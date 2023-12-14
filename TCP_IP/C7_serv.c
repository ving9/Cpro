#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[]){
    
    int serv_sd, clnt_sd;
    FILE *fp;
    char buf[BUF_SIZE];
    int read_cnt = 0;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    

    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    fp=fopen("C7_serv.c", "rb");
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);

    if(serv_sd == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if(listen(serv_sd, 5) == -1)
        error_handling("listen() error");

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sd = accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

    while(1)
    {
        read_cnt = fread((void*)buf, 1, BUF_SIZE, fp); // BUF_SIZE가 너무커서 그 크기 만큼 다 추출 안한다면? 그래서 파일의 끝에 도달한다면?

        if(read_cnt<BUF_SIZE) // 파일의 끝에 도달한만큼 서버로 보내준다
        {
            write(clnt_sd, buf, read_cnt);
            break;
        }
        write(clnt_sd, buf, BUF_SIZE); // BUF_SIZE 만큼 다 읽었으면 서버로 보내고 다시 반복
        // 결국 이렇게 보내다 보면 어느 순간에는 BUF_SIZE만큼 다 보내기 전에 파일이 끝날 것이므로
        // 파일이 끝나면 이프문으로 돌아가서 읽은데까지 보내고 종료함..
        // 
    }
    shutdown(clnt_sd, SHUT_WR);
    read(clnt_sd, buf, BUF_SIZE);
    printf("Message from client : %s \n", buf);

    fclose(fp);
    close(clnt_sd); close(serv_sd);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}