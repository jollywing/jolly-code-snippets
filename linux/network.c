
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>

void test_addr_convert()
{
    struct in_addr ip;
    const char * addr_str = "128.2.194.242";
    /* ip.s_addr in network byte order */
    inet_aton(addr_str, &ip);
    /* convert to local byte order */
    unsigned int ip_bin = ntohl(ip.s_addr);
    printf("The value of ip %s is: %.6x\n", addr_str, ip_bin);

    ip.s_addr = htonl(ip_bin);
    char * result_str = inet_ntoa(ip);
    printf("The ip %.6x represents: %s\n", ip_bin, result_str);
}

void test_dns_entry(const char *dn)
{
    /* given a domain name, for example: www.baidu.com */
    /* get host entry */
    struct hostent *he;
    /*
    struct hostent {
        char * h_name; // official domain name;
        char ** h_aliases; // domain name aliases;
        int h_addrtype; //AF_INET;
        int h_length; // length of an address, in bytes
        char ** h_addr_list; // in_addr structs
    }
    */
    he = gethostbyname(dn);
    /* print host entry */
    printf("Offical domain name: %s\n", he->h_name);
    char ** pp;
    for(pp = he->h_aliases; *pp != 0; pp ++)
        printf("aliase: %s\n", *pp);
    
    struct in_addr ip;
    for(pp = he->h_addr_list; *pp != 0; pp++){
        ip.s_addr = *((unsigned int *)*pp);
        printf("address: %s\n", inet_ntoa(ip));
    }
}

int main(int argc, char *argv[])
{
    test_addr_convert();
    test_dns_entry("www.baidu.com");
    test_dns_entry("music.baidu.com");
    test_dns_entry("baidu.com");
    test_dns_entry("localhost");
    return 0;
}
