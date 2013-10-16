/*
 * tcpserver.c
 *
 *  Created on: 2013. 10. 15.
 *      Author: sugusbs
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <error.h>

#include "tcplib.h"

#define SERV_PORT 8001 // port
#define LISTENQ 8 // maximum number of client connections


int main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	//Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

		if ((childpid = fork()) == 0) {
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
}
