#include <vector>
#include <iostream>
#include <algorithm>

using std::cin; using std::cout; using std::endl;
using std::istream; using std::ostream;
using std::vector; using std::string;

struct Student_info {
    istream & read(istream & in) {
        return in;
    }

    // need add const
    static bool compare(const Student_info & s1, const Student_info & s2) {
        return true;
    }

    string name(){
        return "John";
    }
};

struct Picture {
    friend ostream& operator<<(ostream &out, const Picture &p) {
        return out;
    }
};

Picture histogram(const vector<Student_info>& students)
{
    Picture names;
    for(vector<Student_info>::const_iterator it = students.begin();
        it != students.end(); ++it) {
        // vector<T>(int n, T t); n elements with value t
        names = vcat(names, vector<string>(1, it->name()));
    }
    return names;
};

Picture frame(const Picture &){
}

int main()
{
    vector<Student_info> students;
    Student_info s;

    while(s.read(cin))
        students.push_back(s);

    sort(students.begin(), students.end(), Student_info::compare);

    cout << frame(histogram(students)) << endl;
    return 0;
}
