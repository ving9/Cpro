#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    int status;
    pid_t pid = fork();

    if(pid==0)
    {
        sleep(15);
        return 24;
    }
    else
    {
        while(!waitpid(-1, &status, WNOHANG)) 
        // 헤더파일 sys/wait.h 에 선언된 상수 WNOHANG 때문에
        // 종료된 자식 프로세스가 없으면 계속 0을 반환
        // 따라서 !0 은 참이 되므로 와일문이 계속 돌아간다
        {
            sleep(3);
            puts("sleep 3sec.");
        }
        
        if(WIFEXITED(status))
            printf("Child send %d \n", WEXITSTATUS(status));
    }

    return 0;
}