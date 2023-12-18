#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig){ // 시그널 핸들러
    if(sig == SIGALRM)
        puts("Time out!");
    alarm(2); // 최초 알람 발생 이후에 반복 시켜주기 위해서
}
void keycontrol(int sig){
    if(sig == SIGINT)
        puts("CTRL+C pressed");
}

int main(int argc, char* argv[]){

    int i;
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    for(i=0;i<3;i++){
        puts("wait...");
        sleep(100);
    }

    return 0;
}