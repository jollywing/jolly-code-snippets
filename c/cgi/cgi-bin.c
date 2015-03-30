
/* create: 2012-11-27 */
/* update: 2012-11-27 */

/* make: gcc -o table cgi-bin.c */
/* # cp table /srv/http/cgi-bin/ */
/* http://localhost/cgi-bin/table?color1:color2 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *token = NULL;
    char color1[256] = "";
    char color2[256] = "";
    int i,j;
    
    token = strtok(argv[1], ":");
    strcpy(color1, token);
    /* continue parsing the same string, the first param uses NULL*/
    token = strtok(NULL, ":");
    strcpy(color2, token);
    
    printf("Content-type:text/html\n\n"
           "<html>\n");
    printf("<body bgcolor=\"%s\"> </body>\n", color1);
    printf("<center>\n");
    printf("<table bgcolor=\"%s\" border=\"2\">\n", color2);
    for (i = 1; i <= 9; i++) {
        printf("<tr>\n");
        for (j = 1; j <= 9; j++) {
            printf("<td>row = %d, cell = %d </td>\n", i, j);
        }
        printf("</tr>\n");
    }
    printf("</table>\n");
    printf("</body>\n");
    printf("</html>\n");
    return 0;
}
