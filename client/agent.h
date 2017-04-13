/*************************************************************************
	> File Name: agent.h
	> Auth:yiheng
	> Mail:danzuji@gmail.com
	> Created Time: Mon 20 Feb 2017 02:10:11 PM CST
 ************************************************************************/

#ifndef _AGENT_H
#define _AGENT_H

#define MAX_SIZE 1024
#define PORT     6666
#define SERVER_IP "127.0.0.1"

typedef struct agent_info {
    struct sockaddr_in addr;
    int sockfd;
    pthread_mutex_t  mutex;
    pthread_mutexattr_t mutex_attr;
    pthread_t recv_tid;
    pthread_t transmit_tid;
}agent_dev_t;

int client_init();
int client_sent(char *data, int len);
void client_exit();

#endif
