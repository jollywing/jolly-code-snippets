#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "rio.h"

/* without buffer */
ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while(nleft > 0){
        nread = read(fd, bufp, nleft);
        if(nread < 0){
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        /* EOF */
        /* todo: how many byte readed before EOF */
        if(nread == 0)
            break;

        bufp += nread;
        nleft = nleft - nread;
    }
    return n - nleft;
}

/* without buffer */
ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwrite;
    char *bufp = usrbuf;

    while(nleft > 0){
        nwrite = write(fd, usrbuf, nleft);
        if(nwrite < 0){
            if(errno == EINTR)  /* interrupted by sig handler return */
                nwrite = 0;
            else
                return -1;
        }
        nleft -= nwrite;
        bufp += nwrite;
    }
    return n;
}

/* with buffer */
void rio_readinitb(rio_t *rp, int fd)
{
	rp->rio_fd = fd;
	rp->rio_cnt = 0;
	rp->rio_bufptr = rp->rio_buf;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
	int cnt; 
	
    /* If internal buffer empty, read data and fill buffer */
	while (rp->rio_cnt <= 0)
	{
		rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
		printf("Content: %s\n", rp->rio_buf);
		printf("bytes count: %d\n", rp->rio_cnt);
		
		if (rp->rio_cnt < 0)
        {
            if (errno != EINTR)
                return -1;
        }
		else if (rp->rio_cnt == 0)
			return 0;
		else
			rp->rio_bufptr = rp->rio_buf; /* reset buffer ptr */
	}
	
    /* select the minimum between n and rio_cnt */
	cnt = n;
	if (rp->rio_cnt < n)
		cnt = rp->rio_cnt;
    /* return cnt bytes of data */
    /* printf("rp->rio_bufptr = %c;", *(rp->rio_bufptr)); */
	memcpy(usrbuf, rp->rio_bufptr, cnt);
	rp->rio_bufptr += cnt;
	rp->rio_cnt -= cnt;
	return cnt;
} 

ssize_t rio_readlineb(rio_t *rp, char *usrbuf, size_t maxlen)
{
	int n, rc;
	char c, *bufp = usrbuf;

	for (n = 1; n < maxlen; n++)
	{
		if ((rc = rio_read(rp, &c, 1)) == 1)
        {
            printf("%c", c);
            *(bufp++) = c;
            if (c == '\n')
            {
                n--;
                break;
            }
					
        } else if (rc == 0) {   /* EOF */
            if (n == 1)
                return 0;
            else
            {
                n--;
                break;
            }

        }
        else
            return -1;

	}

	*bufp = 0;
	return n;
}

ssize_t rio_readnb(rio_t *rp, char *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while(nleft > 0){
        nread = rio_read(rp, usrbuf, nleft);
        if(nread < 0){
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }

    return (n - nleft);
}

void test_rio(void)
{	
    rio_t rio;
	int fd = open("demo.txt", O_RDWR, 0);
	char usrbuf[256];
	rio_readinitb(&rio, fd);
	int count = rio_readlineb(&rio, usrbuf, 256);
	printf("the line has %d letters\n", count);
    printf("%s\n", usrbuf);
}
