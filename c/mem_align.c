#include <stdio.h>
#include <assert.h>
#include <string.h>

int global_var = 0;

typedef struct {
    int _age;
    /* memory align, sex will take 4 bytes */
    char sex;
    int grade;
} Student;

typedef struct {
    int _age;
    char sex;
    char level;
    char field[4];
} Teacher;

void test_struct_size()
{
    /* 12 12 */
    printf("size of struct Student: %d\n"
            "size of struct Teacher: %d\n",
            sizeof(Student), sizeof(Teacher));
    assert(sizeof(Student) == sizeof(Teacher));
}

void test_struct_memset()
{
    Student s;
    memset(&s, 0, sizeof(s));
    assert(s._age == 0);
    assert(s.sex == '\0');
    assert(s.grade == 0);
}

int main(int argc, char * argv[])
{
    test_struct_size();
    test_struct_memset();
    return 0;
}
