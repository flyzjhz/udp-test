
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
#include "msg_queue.h"

int main(int argc,char **argv)
{
    int ret;
    int count = 0;
    char buf[MAX_SIZE];
    char run = 1;

#if 0  //list test
    add_msg("11111", 1);
    add_msg("22222", 2);
    add_msg("33333", 3);
    list_for_each_msg();
    del_msg();
    printf("xxxxxxxxxxx\n");
    del_msg();
    printf("uuuuuuuuu");
    list_for_each_msg();
    destroy_msg_list();
    printf("aaaaa\n");
    list_for_each_msg();
    printf("ppppp\n");
#endif

#if 1
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
#endif
    return 0;
}


