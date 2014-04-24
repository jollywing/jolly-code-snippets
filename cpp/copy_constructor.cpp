
#include <iostream>
#include <string.h>

class Book {
private:
    char *_title;
    int _pages;
public:
    Book(const char *title, int pages) {
        _title = new char[256];
        strcpy(_title, title);
        _pages = pages;
    }

    // 拷贝构造器
    // (1) 一个对象以值的形式传入函数体时，（2）对象以值的形式从函数体返回时
    // （3）对象用另一个对象赋值时，会调用拷贝构造器。
    Book(const Book &b) {
        _title = new char[256];
        // 虽然_title和_pages是b的私有成员，但在Book内可以直接访问
        strcpy(_title, b._title);
        _pages = b._pages;
    }

    void dump() {
        std::cout << "Book " << _title << " has " << _pages << " pages.\n";
    }

    ~Book() {
        if(_title){
            std::cout << "_title released!" << std::endl;
            delete _title;
            _title = NULL;
        }
    }
};

int main(int argc, char *argv[]) {
    Book book1("God's road", 12);
    book1.dump();

    Book book2 = book1;
    book2.dump();

    // 对象赋值时，如果是浅拷贝（如果没有拷贝构造器，默认是浅拷贝）
    // 两个对象的指针成员指向同一地址。
    // 两个对象析构时，释放指针，会发生 double free 的错误。
    // 因此，当数据成员包含指针时，要实现拷贝构造器实现深拷贝

    return 0;
}
