/**
 * This a program emulate `ls` on Unix.
 * It should be much weaker than `ls`
 * @AUTHOR: jollywing@foxmail.com
 * @date: 2015-03-12 Thu
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int file_num = 0;

void fake_ls(const char *path, size_t lvl)
{
    struct dirent * item;
    int i;

    /* open dir */
    DIR * dstream = opendir(path);
    /* If error, exit the function */
    if(!dstream) {
        printf("open %s failed, maybe %s does not exist, "
                "or it is not a directory, "
                "or you have not enough priviledge.\n",
                path, path);
        exit(1);
    }
    /* read item from dir stream one by one, util the end of dir stream */
    while(1) {
        item = readdir(dstream);
        /* if item is NULL, may reach the end of dstream or may produce an error */
        if (!item) {
            break;
        }
        /* if the item is a regular file, print it */

        char file_name[256] = "";

        if(strcmp(item->d_name, ".") && strcmp(item->d_name, "..")){
                for(i = 0; i < lvl; i++){
                    strcat(file_name, "\t");
                }
                strcat(file_name, item->d_name);

            if (item->d_type == DT_DIR){
                strcat(file_name, "/");
                printf("%s\n", file_name);

                char new_path[256];
                strcpy(new_path, path);
                if(path[strlen(path) - 1] != '/')
                    strcat(new_path, "/");
                strcat(new_path, item->d_name);
                fake_ls(new_path, lvl + 1);
            }
            else {
                file_num ++;
                printf("%s\n", file_name);
            }
        }
    }
    closedir(dstream);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return 0;
    }
    fake_ls(argv[1], 0);
    printf("%d files in total.\n", file_num);
    return 0;
}
