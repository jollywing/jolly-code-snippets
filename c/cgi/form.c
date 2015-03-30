
/* create: 2012-11-28 */
/* update: 2012-11-28 */

/* make: gcc -o form form.c */
/* # cp form /srv/http/cgi-bin/ */
/* http://localhost/cgi-bin/form */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void decode_value(const char *key, char *value, int size)
{
    int i= 0, j= 0, length = 0;
    char *pos1 = NULL, *pos2 = '\0';
    char code1 = '\0', code2 = '\0';

    strcpy(value, "");
    if ((pos1 = strstr(getenv("QUERY_STRING"), key)) != NULL) {
        for (i = 0; i < strlen(key); i ++)
            pos1 ++;

        if ((pos2 = strstr(pos1, "&")) != NULL) {
            length = pos2 - pos1;
        }
        else
            length = strlen(pos1);

        for(i=0, j=0; i < length; i++, j++){
            if (j < size) {
                if (pos1[i] == '%') {
                    i++;
                    code1 = pos1[i];
                    i++;
                    code2 = pos1[i];
                    if(code1 == '2' && code2 == '0')
                        value[j] = ' ';
                    if(code1 == '2' && code2 == '1')
                        value[j] = '!';
                }
                else if(pos1[i] == '+')
                    value[j] = ' ';
                else
                    value[j] = pos1[i];
            }
        }
        if (j < size) value[j] = '\0';
        else value[size - 1] = '\0';
    }
}

int main(int argc, char *argv[])
{
    printf("Content-type:text/html\n\n<html><body bgcolor=\"lightblue\">\n");
    char value[256];
    strncpy(value, getenv("QUERY_STRING"), 255);
    printf("QUERY STRING: %s<BR>\n", value);
    printf("<form>\n");

    decode_value("ITEM1=", value, 255);
    if(strlen(value) > 0)
        printf("<input type=\"TEXT\" name=\"ITEM1\" value=\"%s\"/>\n", value);
    else
        printf("<input type=\"TEXT\" name=\"ITEM1\"/>\n");

    decode_value("ITEM2=", value, 255);
    if(strlen(value) > 0)
        printf("<input type=\"TEXT\" name=\"ITEM2\" value=\"%s\"/>\n", value);
    else
        printf("<input type=\"TEXT\" name=\"ITEM2\"/>\n");

    printf("<input type=\"SUBMIT\"/>");
    printf("</form></body></html>\n");
    return 0;
}
