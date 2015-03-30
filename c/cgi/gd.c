
/* create: 2012-11-30 */
/* update: 2012-11-30 */

/* make: gcc -o gd gd.c -lgd */
/* # cp gd /srv/http/cgi-bin/ */
/* http://localhost/cgi-bin/gd?TEXT=somecontents */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gd.h>
#include <gdfonts.h>

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
    int text = 0;
    int background = 0;
    int height = 50;
    int width = 0;
    int x = 0, y = 0;
    int size = 30;
    int string_rectangle[8];
    double angle = 0.0;
    char value[255] = "";
    char font[256] = "/usr/share/fonts/TTF/DejaVuSansMono.ttf";
    char *err = NULL;
    gdImagePtr im_out = NULL;

    decode_value("TEXT=", value, 255);
    // call gdImageStringFT with NULL image to obtain size
    err = gdImageStringFT(NULL, &string_rectangle[0],
                          0, font, size, angle, 0, 0, value);
    x = string_rectangle[2] - string_rectangle[6] + 6;
    y = string_rectangle[3] - string_rectangle[7] + 6;

    /* width = strlen(value) * 10 + 5; */
    /* im_out = gdImageCreate(width, height); */
    im_out = gdImageCreate(x, y);
    
    background = gdImageColorAllocate(im_out, 255, 0, 255);
    text = gdImageColorAllocate(im_out, 0, 0, 255);

    /* get starting position */
    x = 3 - string_rectangle[6];
    y = 3 - string_rectangle[7];

    gdImageFilledRectangle(im_out, 0, 0, x - 1, y - 1, background);
    /* gdImageString(im_out, gdFontGetSmall(), 10, 10, value, text); */
    err = gdImageStringFT(im_out, &string_rectangle[0],
                          text, font, size, angle, x, y, value);
    
    printf("Content-type:image/gif\n\n");
    gdImageGif(im_out, stdout);
    gdImageDestroy(im_out);
    return 0;
}
