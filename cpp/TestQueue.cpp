#include <string>
#include <iostream>
#include <queue>

using std::string;
using std::cout; using std::endl;
using std::queue;

struct Movie {
    string title;
    string director;
    int year;
    ~Movie(){
        cout << "Movie object destroied." << endl;
    }
};

void TestQueueWithPointer()
{
    Movie movie1, movie2, movie3;
    queue<Movie *> movies;
    movies.push(&movie1);
    movies.push(&movie2);
    movies.push(&movie3);

    while(!movies.empty())
        movies.pop();
    cout << "Function will return, has the movie objects been destroied?" << endl;
}


int main()
{
    TestQueueWithPointer();
    return 0;
}
