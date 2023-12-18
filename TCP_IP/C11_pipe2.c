#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int fds[2];
    char str1[] = "Who are you?";
    char str2[] = "Thank you";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds);
    pid = fork();

    if(pid == 0)
    {
        write(fds[1], str1, sizeof(str1));
        sleep(2);  // 여기에 주석처리하면 자식이 보낸 메세지를 자식이 수신해버림
        read(fds[0], buf, BUF_SIZE);
        printf("Child proc output : %s \n", buf);
    }
    else
    {
        read(fds[0], buf, BUF_SIZE); // 부모는 여기서 하염없이 read를 기다리게 된다...
        printf("Parent proc output : %s \n", buf);
        write(fds[1], str2, sizeof(str2));
        sleep(3);
    }
    return 0;
}