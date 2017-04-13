/*************************************************************************
	> File Name: msg_queue.c
	> Auth:yiheng
	> Created Time: Tue 21 Feb 2017 02:17:19 PM CST
 ************************************************************************/

#include "msg_queue.h"

static LIST_HEAD(msg_head);


int add_msg(char *data, int id)
{
    agent_msg_t *msg = malloc(sizeof(agent_msg_t));
    memset(msg->data, 0, sizeof(msg->data));
    if(NULL == msg)
    {
        printf("malloc msg failed!\n");
        return -1;
    }

   // printf("add:%x\n", msg);
    memcpy(msg->data, data,strlen(data));
    msg->id = id;
    list_add_tail(&msg->list, &msg_head);
}

int del_msg()
{
    agent_msg_t *msg, *tmp;
    list_for_each_entry_safe(msg, tmp, &msg_head, list )
    {
        list_del(&msg->list);
        free(msg);
        break;
    }
    return 0;
}

int list_for_each_msg()
{
    agent_msg_t *msg, *tmp;
    //list_for_each_entry_safe(msg, tmp, &msg_head, list)
    list_for_each_entry(msg, &msg_head, list)
    {
        //printf("%x\n", msg);
        printf("data:%s, id:%d\n", msg->data, msg->id);
    }
    return 0;
}

int destroy_msg_list()
{
    agent_msg_t *msg, *tmp;
    list_for_each_entry_safe(msg, tmp, &msg_head, list )
    {
        list_del(&msg->list);
        free(msg);
    }
    return 0;
}


agent_msg_t *get_msg()
{
    
    agent_msg_t *msg = NULL, *tmp;
    if(1 == list_empty(&msg_head))
        return NULL;
    printf("empty:%d\n", list_empty(&msg_head));
    list_for_each_entry_safe(msg, tmp, &msg_head, list )
    {
        list_del(&msg->list);
        break;
    }

    return msg;
}
