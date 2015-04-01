/*
bind 绑定127.0.0.1 仅本机可以连接
端口设为0，内核选择端口
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int MAXLINE = 1024;

int main()
{
	int listenfd,connfd;
	struct sockaddr_in serveraddr;
	char buff[MAXLINE];
	time_t ticks;

	listenfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(13);

	bind(listenfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

	listen(listenfd,1024);

	for(;;)
	{
		connfd = accept(listenfd,(struct sockaddr *)NULL,NULL);

		ticks = time(NULL);

		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));

		close(connfd);
	}
}
