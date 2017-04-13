
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "agent.h"

int main(int argc,char **argv)
{
    int ret;
    int count = 0;
    char buf[MAX_SIZE];
    char run = 1;
    ret = client_init();
    if(-1 == ret)
    {
        printf("agent init failed\n");
        client_exit();
        return -1;
    }
    while(run)
    {
        fgets(buf, MAX_SIZE, stdin);
        count++;
        if(10 == count)
        {
            run = 0;
            break;
        }
        client_sent(buf, strlen(buf));
    }
        client_exit();
    return 0;
}


