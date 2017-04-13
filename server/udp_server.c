
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define SERVER_PORT 6666
#define MAX_SIZE 1024

void UDP_answer(int sockfd)
{
	struct sockaddr_in addr;
	int i,n;
	unsigned int addrlen;
	char msg[MAX_SIZE];
    int ret;
	while(1)
	{
		n=recvfrom(sockfd, msg, MAX_SIZE, 0, (struct sockaddr *)&addr,&addrlen);
		msg[n]=0;
        fprintf(stdout,"server received:%s\n",msg);
		n=strlen(msg);
		//for(i=0;i<n;i++)
		//	msg[i]=toupper(msg[i]);
		ret = sendto(sockfd, msg, n, 0, (struct sockaddr *)&addr, addrlen);
        if(0 >ret)
            printf("sento failed!\n");
	}
}

int main(void)
{
	int sockfd;
    int on;
	struct sockaddr_in addr;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&addr,sizeof(struct sockaddr_in));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	addr.sin_port=htons(SERVER_PORT);

    if((setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)
    {
        perror("setsockopt");
        return -1;
    }

	if(bind(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_in))<0)
	{
		perror("bind");
		exit(1);
	}
	UDP_answer(sockfd);
	close(sockfd);
	return 0;
}


