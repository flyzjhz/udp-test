/*************************************************************************
	> File Name: msg_queue.h
	> Auth:yiheng
	> Mail:danzuji@gmail.com
	> Created Time: Tue 21 Feb 2017 02:18:04 PM CST
 ************************************************************************/

#ifndef _MSG_QUEUE_H
#define _MSG_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "list.h"

typedef struct agent_msg
{
    char data[2048];
    int id;
    struct list_head list; 
}agent_msg_t;

int add_msg(char *data, int id);
int del_msg();
int list_for_each_msg();
int destroy_msg_list();
agent_msg_t *get_msg();
#endif
