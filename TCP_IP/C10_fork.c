#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int gval = 10;
int main(int argc, char* argv[])
{
    pid_t pid;
    int lval = 20;
    gval++, lval+=5;

    pid = fork();
    if(pid == 0) // 만약 자식 프로세스라면
        gval+=2, lval+=2;
    else{ // 만약 부모 프로세스라면
        gval-=2, lval-=2;
        printf("CHild Process Id: %d \n", pid);
        sleep(30);
    }

    
    if(pid == 0)
        printf("Child Proc : [%d, %d] \n", gval, lval);
    else
        printf("Parent Proc : [%d, %d] \n", gval, lval);
    return 0;
}