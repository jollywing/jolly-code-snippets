
/* create: 2012-11-29 */
/* update: 2012-11-29 */
/* make: gcc -o sql-test mysql.c -lmysqlclient */
/* # cp sql-test /srv/http/cgi-bin/ */
/* http://localhost/cgi-bin/sql-test */

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
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

int main(int argc, char *argv[], char *env[])
{
    char value1[255] = "";
    char value2[255] = "";
    char SQL[1024] = "";
    int rc = 0;
    
    MYSQL *conn = NULL;
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    
    printf("Content-type:text/html\n\n<html><body bgcolor=\"lightblue\">\n");
    strncpy(value1, getenv("QUERY_STRING"), 255);
    printf("QUERY STRING: %s <BR>\n", value1);
    printf("<form>\n");
    decode_value("ITEM1=", value1, 255);
    if(strlen(value1) > 0)
        printf("<input type=\"TEXT\" name=\"ITEM1\" value=\"%s\" />\n", value1);
    else
        printf("<input type=\"TEXT\" name=\"ITEM1\" />\n");
    
    decode_value("ITEM2=", value2, 255);
    if(strlen(value2) > 0)
        printf("<input type=\"TEXT\" name=\"ITEM2\" value=\"%s\" />\n", value2);
    else
        printf("<input type=\"TEXT\" name=\"ITEM2\" />\n");
    printf("<input type=\"SUBMIT\" />");
    
    printf("</form>\n");

    // open mysql database
    conn = mysql_init((MYSQL *)0);
    mysql_options(conn, MYSQL_READ_DEFAULT_GROUP, "mysqlcapi");
    mysql_real_connect(conn, "localhost", "", "", "test", 0, NULL, 0);
    if(strlen(value1) > 0 || strlen(value2) > 0) {
        sprintf(SQL, "insert into CIL values ('%s','%s')", value1, value2);
        rc = mysql_query(conn, SQL);
    }
    rc = mysql_query(conn, "select * from CIL");
    result = mysql_use_result(conn);
    while((row = mysql_fetch_row(result)) != NULL) {
        printf("item1 = %s; item2 = %s<br>\n", row[0], row[1]);
    }
    printf("</body></html>\n");
    mysql_free_result(result);
    mysql_close(conn);
    return 0;
}
