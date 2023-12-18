#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/socket.h>

#define BUF_SIZE 100

void error_handling(char* message);
void read_childproc(int sig);

int main(int argc, char* argv[]){

    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    struct sigaction act;
    socklen_t adr_sz;
    
    pid_t pid;
    int fds[2];
    int str_len, state;
    char buf[BUF_SIZE];

    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    act.sa_handler=read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);
    // 시그널을 이용하여 좀비 프로세스 없애는 과정

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    // 주소정보 구조체 초기화 과정

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    pipe(fds);
    pid=fork();

    if (pid == 0)
    {
        FILE* fp = fopen("echomsg.txt", "wt");
        char msgbuf[BUF_SIZE];
        int i, len;

        for(i=0; i<10; i++)
        {
            len = read(fds[0], msgbuf, BUF_SIZE);
            fwrite((void*)msgbuf, 1, len, fp); // 이곳은 단순히 서버와 통신하고 있는 프로세스로부터 정보를 받아와서 파일에 저장하는 일만 하는중
        }
        fclose(fp);
        return 0;
    }

    while(1)
    {
        adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
        
        if(clnt_sock == -1)
            continue;
        else{
            puts("new client connected...");
        }

        pid = fork();
        if(pid == -1)
        {
            close(clnt_sock);
            continue;
        }
        if(pid == 0)
        {
            close(serv_sock); // 복사된 자식프로세스의 서버소켓을 닫아주는 과정 (결국 리슨은 부모에서 하기때문에)
            
            while((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
            {
                write(clnt_sock, buf, str_len);
                write(fds[1], buf, str_len);
            }

            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        }
        else
            close(clnt_sock);
        
    }
    close(serv_sock);
    return 0;
}

void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    printf("removed proc id: %d \n", pid);
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}