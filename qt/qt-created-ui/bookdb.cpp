#include "bookdb.h"

Book::Book(string _title, string _author, string _year)
{
    title = _title;
    author = _author;
    publish_year = _year;
}

BookDB::BookDB()
{
    books.clear();
}

void BookDB::insert(const Book & b)
{
    books.push_back(b);
}

void BookDB::list()
{

}

bool BookDB::save()
{
    return true;
}
