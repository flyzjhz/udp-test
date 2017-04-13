/*************************************************************************
	> File Name: client.c
	> Auth:yiheng
	> Created Time: Mon 20 Feb 2017 01:52:41 PM CST
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>

#include "agent.h"

static agent_dev_t agent;

void net_receive(void *arg)
{
    char buf[MAX_SIZE];
    int count;
    int i;
    struct sockaddr_in server;
    int addr_len = sizeof(struct sockaddr_in);
    char *p = buf;
    printf("%s\n", arg);
    while(1)
    {
        pthread_mutex_lock(&agent.mutex);
        p = buf;
        printf("waiting response from server\n");
        bzero(buf, MAX_SIZE);
        count = recvfrom(agent.sockfd, buf, MAX_SIZE, 0, (struct sockaddr*)&server, &addr_len);
        if(0 > count)
        {
            printf("received failed,continue\n");
            continue;
        }
        //buf[count]=0;
        printf("received from server:%d, %d\n", count, addr_len);
        for(i=0; i<count; i++)
            printf("%c", *p++);
        printf("\n");
        pthread_mutex_unlock(&agent.mutex);
    }
}

void transmit_msg(void *arg)
{

    printf("%s\n", arg);
    while(1)
    {
        
    }
}

void signal_hander(int sig)
{
    printf("sig num:%d\n", sig);
    client_exit();
}

int client_init()
{
    int ret;

    memset(&agent, 0, sizeof(agent));
    agent.sockfd = -1;
    agent.recv_tid = -1;
    agent.transmit_tid = -1;

    agent.sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == agent.sockfd)
    {
        perror("socket");
        return -1;
    }
    
    memset(&agent.addr, 0, sizeof(agent.addr));
    agent.addr.sin_family=AF_INET;
    agent.addr.sin_port=htons(PORT);
    if(inet_aton(SERVER_IP, &agent.addr.sin_addr)<0)
    {
        fprintf(stderr,"IP error:%s\n",strerror(errno));
        return -1;
    }

    /*
    if(bind(agent.sockfd, (struct sockaddr*)&agent.addr, sizeof(struct sockaddr)))
    {
        perror("bind");
        return -1;
    }
    */

    if(SIG_ERR == signal(SIGINT, signal_hander))
    {
        printf("SIGINT register error!\n");
        return -1;
    }

    ret = pthread_attr_init(&agent.mutex_attr);
    if(0 != ret)
    {
        printf("pthread_attr_init failed!\n");
        return -1;
    }
    pthread_attr_setdetachstate(&agent.mutex_attr, PTHREAD_CREATE_DETACHED); 
    pthread_mutex_init(&agent.mutex, &agent.mutex_attr);
    ret = pthread_create(&agent.recv_tid, &agent.mutex_attr, net_receive, (void *)( "phtread receive"));
    if(0 != ret)
    {
        printf("receive pthread_create failed!\n");
        return -1;
    }

    ret = pthread_create(&agent.transmit_tid, &agent.mutex_attr, transmit_msg, (void *)( "phtread transmit"));
    if(0 != ret)
    {
        printf("transmit pthread_create failed!\n");
        return -1;
    }
    return 0;
}

int client_sent(char *data, int len)
{
    int i;
    int count;
    char *p = data;
    //fgets(buf,MAX_SIZE,stdin);//input from keyboard to service
    if(NULL == data)
    {
        printf("data == NULL!!!\n");
        return -1;
    }
    count = sendto(agent.sockfd, data, len, 0, (struct sockaddr *)&agent.addr, sizeof(agent.addr));
    if(0 > count)
    {
        perror("sendto");
        return -1;
    }

    printf("sent to server:");
    for(i = 0; i<len; i++)
        printf("%c", *p++);
    printf("\n");
    return count;
}

void client_exit()
{
    int ret;


    if(-1 != agent.recv_tid)
    {
        ret =  pthread_kill(agent.recv_tid, 0);//test thread exist 
        if(ESRCH != ret)
        {
            pthread_kill(agent.recv_tid, SIGQUIT);
            printf("kill receive thread!\n");
            pthread_join(agent.recv_tid, NULL);
            agent.recv_tid = -1;
        }else
            printf("receive pthread is not exist!\n");
    }

    if(-1 != agent.transmit_tid)
    {
        ret =  pthread_kill(agent.transmit_tid, 0);//test thread exist 
        if(ESRCH != ret)
        {
            pthread_kill(agent.transmit_tid, SIGQUIT);
            printf("kill receive thread!\n");
            pthread_join(agent.transmit_tid, NULL);
            agent.transmit_tid = -1;
        }else
            printf("read pthread is not exist!\n");
    }

    if(-1 != agent.sockfd)
    {
        close(agent.sockfd);
        agent.sockfd =  -1;
        printf("socket closed!\n");
    }

    printf("exit...\n");
}
