#ifndef BOOKDB_H
#define BOOKDB_H

#include <string>
#include <vector>
using std::string;
using std::vector;

struct Book
{
    string title;
    string author;
    int publish_year;
    Book(string _title, string _author, int _year);
};

class BookDB
{
private:
    vector<Book> books;
public:
    void insert(const Book &);
    void list();
    bool save();
    BookDB();
};

#endif // BOOKDB_H
