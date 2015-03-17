#include <stdio.h>

struct Data {
    int hp;
    int maxhp;
};

void save_data(struct Data);
void read_data();

int main(int argc, char *argv[]){
    struct Data data = {10, 20};
    save_data(data);
    read_data();
    return 0;
}

void save_data(struct Data data)
{
    FILE * fp = fopen("data.save", "w");
    char temp[32];
    sprintf(temp, "%d", data.hp);
    fputs(temp, fp);
    fputs(" ", fp);
    sprintf(temp, "%d", data.maxhp);
    fputs(temp, fp);
    fclose(fp);
}

void read_data()
{
    FILE *fp = fopen("data.save", "r");
    char temp[32];
    /* copy 3 - 1 chars */
    fgets(temp, 3, fp);
    struct Data data;
    data.hp = atoi(temp);
    /* read 4 - 1 chars */
    fgets(temp, 4, fp);
    data.maxhp = atoi(temp);
    printf("hp: %d; maxhp: %d\n", data.hp, data.maxhp);
    fclose(fp);
}
