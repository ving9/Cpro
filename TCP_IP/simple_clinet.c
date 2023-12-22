#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <locale.h>
#define BUF_SIZE 10240
void error_handling(char *message);
int main(int argc, char *argv[])
{
    int sd;
    FILE *fp,*fp1;
    char str_tmp1[BUF_SIZE];
    char str_tmp[BUF_SIZE]; // 파일 열고 넣을 배열
    char *str[BUF_SIZE]; // 파일 오픈 후 문자열 저장할 배열
    char *str1[BUF_SIZE];
    char Max,Min,Average,Price; // 최소 최대 평균 예상가격
    char buf[BUF_SIZE]; // read용
    int read_cnt;// read용
    struct sockaddr_in serv_adr;

    if(argc !=3)
    {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }
    fp = fopen("13busan.csv", "rt");//파일 열기
    fp1 = fopen("14busan.csv","rt");
    sd = socket(PF_INET,SOCK_STREAM,0);
    setlocale(LC_ALL, "en_US.UTF-8");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    connect(sd,(struct sockaddr*)&serv_adr,sizeof(serv_adr)); // 연결

    while (!feof(fp))
    {   
        while (!feof(fp)) // fp 파일의 끝이 아니라면 반복
        {
            fgets(str_tmp, sizeof(str_tmp), fp);//받는다
            char *ptr = strtok(str_tmp,",");//자른다 쉼표기준으로
            for (int i = 0; i < 15; i++) // 문자열 15번 반복
            {
                str[i] = ptr;
                if (i==0 || i==1 || i==5 || i==14) // 문자열내의 0,1,5,14 번 뽑는다
                {
                    printf("%s,",str[i]); 
                    send(sd, str[i], strlen(str[i]), 0); // 출력한것들 보낸다 한 줄씩
                    send(sd,",",1,0);
                }
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
            send(sd,"\n",1,0);
            printf("\n");
            break;
        }
    }
    char *test = "a";
    send(sd,test,1,0);

    while (!feof(fp1)) // fp1 끝 아니라면 반복
    {   
        while (!feof(fp1)) // fp1 파일의 끝이 아니라면 반복
        {
            fgets(str_tmp1, sizeof(str_tmp1), fp1);//받는다
            char *ptr1 = strtok(str_tmp1,",");//자른다 쉼표기준으로
            for (int i = 0; i < 15; i++) // 문자열 15번 반복
            {
                str1[i] = ptr1;
                if (i==0 || i==1 || i==5 || i==14) // 문자열내의 0,1,5,14 번 뽑는다
                {
                    printf("%s,",str1[i]); 
                    send(sd, str1[i], strlen(str1[i]), 0); // 출력한것들 보낸다 한 줄씩
                    send(sd,",",1,0);
                }
                ptr1 = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
            send(sd,"\n",1,0);
            printf("\n");
            break;
        }
    }
    puts("13,14 busan data send finish"); //파일 끝났는지 확인용
    fclose(fp);
    fclose(fp1);
    close(sd);
    return 0;
}
void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n', stderr);
    exit(1);
}