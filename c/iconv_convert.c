
#include <iconv.h>
#include <string.h>
#include <stdio.h>

char * convert_enc(char *src_enc, char *dest_enc, const char * src_string)
{
#define UTF8_STR_LEN 1024

    static char out_string[UTF8_STR_LEN], *sin, *sout;
    int  in_len, out_len, ret;
    iconv_t c_pt;

    if ((c_pt = iconv_open(dest_enc, src_enc)) == (iconv_t)-1)
    {
        printf("iconv open failed!\n");
        return NULL;
    }
    /* iconv(c_pt, NULL, NULL, NULL, NULL); */
    in_len  = strlen(src_string) + 1;
    out_len = UTF8_STR_LEN;
    sin = (char *)src_string;
    sout = out_string;
    ret = iconv(c_pt, &sin, (size_t *)&in_len, &sout, (size_t *)&out_len);
    if (ret == -1)
    {
        return NULL;
    }
    iconv_close(c_pt);
    return out_string;
}

int main(int argc, char *argv[])
{
    char src_string[512];

    /* read @src_string from file iconv_convert.txt */
    FILE *fp = fopen("iconv_convert.txt", "r");
    fgets(src_string, 512, fp);
    fclose(fp);
    printf("source string: %s\n", src_string);

    /* size_t is defined in <stddef.h>, it is "long unsigned int" */
    /* size_t input_len, output_len; */

    /* iconv_t cd = iconv_open("UTF8", "GB2312"); */
    /* if(cd == (iconv_t)-1){ */
    /*     printf("Open iconv failed, exit!\n"); */
    /*     return -1; */
    /* } */

    /* input_len = strlen(src_string) + 1; */
    /* output_len = 1023; */

    /* convert @input_len bytes data from @src_string according to @cd, put
       up to @output_len bytes data into @dest_string*/
    /* iconv(cd, &src_string, &input_len, &dest_string, &output_len); */
    /* iconv_close(cd); */

    char *result = convert_enc("GBK", "UTF8", src_string);
    if(result){
        printf("Converted String: %s\n", result);
        return 0;
    }
    else
        return -1;
}
