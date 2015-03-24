// 编写类String的构造函数、析构函数和赋值函数，已知类String的原型为：

#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

class String
{
public:
    String(const char *str = NULL); // 普通构造函数
    String(const String &other); // 拷贝构造函数
    ~String(void); // 析构函数
    String & operator=(const String &other); // 赋值函数
private:
    char *m_data; // 用于保存字符串
};

String::String(const char *str)
{
    if(str == NULL){
        m_data = (char *)malloc(1);
        m_data[0] = '\0';
    }
    else {
        m_data = (char *)malloc(strlen(str) + 1);
        if(!m_data){
            exit(1);
        }
        strcpy(m_data, str);
    }
}

String::~String()
{
    cout << "Destructor is called." << endl;
    free(m_data);
}

String::String(const String &other)
{
    cout << "copy constructor is called." << endl;

    // if(m_data){
    //     free(m_data);
    // }
    m_data = (char *)malloc(strlen(other.m_data) + 1);
    strcpy(m_data, other.m_data);
}

String & String::operator=(const String &other)
{
    if(this == &other)
        return *this;

    if(m_data){
        free(m_data);
    }
    m_data = (char *)malloc(strlen(other.m_data) + 1);
    strcpy(m_data, other.m_data);
    return *this;
}

int main()
{
    String a("123");
    String b(a);
    String c = b;
    return 0;
}
