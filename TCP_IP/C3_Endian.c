#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){

    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host ordered port : %#x \n", host_port);
    // 메모리에는 반대 순서로 저장 되있지만
    // 출력은 바꿔서 출력
    printf("Network ordered port : %#x \n", net_port);
    // 메모리에는 제대로 저장 되있지만
    // 바꿔서 출력
    printf("Host ordered port : %#lx \n", host_addr);
    printf("Network ordered port : %#lx \n", net_addr);

    return 0;
}