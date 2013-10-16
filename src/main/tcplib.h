/*
 * tcplib.h
 *
 *  Created on: 2013. 10. 15.
 *      Author: sugusbs
 */

#ifndef TCPLIB_H_
#define TCPLIB_H_

#define MAXLINE 10

void err_sys(const char* x)
{
	perror(x);
	exit(1);
}

void err_quit(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

ssize_t writen(int fd, const void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;

	while(nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) <= 0) {
			//if (nwritten < 0 && errno == EINTR) {
			if (nwritten < 0) {
				nwritten = 0;
			} else {
				return (-1);
			}
		}

		nleft -= nwritten;
		ptr += nwritten;
	}
	return (n);
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n, rc;
	char c, *ptr;

	ptr = vptr;

	for (n = 1; n < maxlen; n++) {
		again:
			if ((rc = read(fd, &c, 1)) == 1) {
				*ptr++ = c;
				if (c == '\n') {
					break;
				} else if (rc == 0) {
					*ptr = 0;
					return (n-1);
				} else {
					/*if (errno == EINTR) {
						goto again;
					}*/
					return (-1);
				}
			}
	}

	*ptr = 0;
	return (n);
}

void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

	again:
		while ((n = read(sockfd, buf, MAXLINE)) > 0) {
			//writen(sockfd, buf, n);
			write(sockfd, buf, n);
			printf("Received message : %s\n", buf);
		}

//		if (n < 0 && errno == EINTR) {
//			goto again;
//		} else if (n < 0) {
//			err_sys("str_echo: read error");
//		}
}

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];

	while(fgets(sendline, MAXLINE, fp) != NULL ) {
		//writen(sockfd, sendline, strlen(sendline));
		write(sockfd, sendline, strlen(sendline));

		/*if (readline(sockfd, recvline, MAXLINE) == 0) {
			err_quit("str_cli: server terminated prematurely");
		}*/

		if (read(sockfd, recvline, MAXLINE) > 0) {
			printf("echo: ");
			fputs(recvline, stdout);
		}
	}
}


#endif /* TCPLIB_H_ */
