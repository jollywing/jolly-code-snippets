#include <openssl/md5.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/* due to using MD5 functions, you should
   add '-lcrypto' when you compile it. */

unsigned char * md5(const char * message, unsigned char * digest)
{
    return MD5(message, strlen(message), digest);
}

unsigned char md5_multi_step(const char *message,
        unsigned char *digest)
{
    MD5_CTX c;
    if(!MD5_Init(&c)) return -1;
    if(!MD5_Update(&c, message, strlen(message))) return -1;
    if(!MD5_Final(digest, &c)) return -1;
    return 0;
}

int main(int argc, char *argv[])
{
    unsigned char digest1[32];
    unsigned char digest2[32];
    const unsigned char * src = "He threw a magical dart at me. "
            "I felt hot pain on my chest, then I fell on the ground.";
    memset(digest1, 0, 32);
    md5(src, digest1);
    printf("MD5 result: %s\n", digest1);

    memset(digest2, 0, 32);
    if (md5_multi_step(src, digest2) == 0) {
        printf("md5_multi_step result: %s\n", digest2);
        assert(strcmp(digest1, digest2) == 0);
    }
    else return -1;

    return 0;
}
