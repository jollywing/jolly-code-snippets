
#ifndef __RIO_H__
#define __RIO_H__

#define RIO_BUFSIZE 8192

typedef struct{
	int rio_fd;
	int rio_cnt;           /* unread bytes in internal buf. */
	char *rio_bufptr;     /* next unread byte in internal buf. */
	char rio_buf[RIO_BUFSIZE];
}rio_t;

void rio_readinitb(rio_t *rp, int fd);

void rio_readinitb(rio_t *rp, int fd);
ssize_t rio_readlineb(rio_t *rp, char *usrbuf, size_t maxlen);
ssize_t rio_readnb(rio_t *rp, char *usrbuf, size_t n);

ssize_t rio_writen(int fd, void *usrbuf, size_t n);
ssize_t rio_readn(int fd, void *usrbuf, size_t n);

#endif
