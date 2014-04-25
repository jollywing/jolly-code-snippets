
#include <iostream>
#include <iomanip>              // define setprecision
#include <ios>                  // define streamsize
#include <vector>
#include <algorithm>            // define sort()

using std::cout; using std::endl;
using std::cin;
using std::streamsize; using std::setprecision;
using std::vector; using std::sort;

int median(vector<double> &v, double *r)
{
    typedef vector<double>::size_type vec_sz;
    vec_sz size = v.size();
    if(size == 0) {
        return -1;
    }

    sort(v.begin(), v.end());
    vec_sz mid = size / 2;
    *r = size % 2 == 0? (v[mid] + v[mid - 1]) / 2: v[mid];
    return mid;
}

int main()
{
    // int count = 0;
    // Now the memory is not so expensive,
    // so we should use double instead of float
    // double sum = 0;

    // on MS Windows, end-of-file is newline followed by C-z.
    // On Linux, end-of-file is newline followed by C-d.
    cout << "Input your homework scores, end with end-of-file: " << endl;
    double score;
    vector<double> scores;
    // If cin ecounters end-of-file, reading will fail.
    // If cin reads a incompatible type input with the variable, reading will also fail.
    while (cin >> score) {
        // sum += score;
        scores.push_back(score);
    }

    double mid_value;
    if(median(scores, &mid_value) < 0){
        cout << "Please input some scores!" << endl;
        return 1;
    }
    else {
        streamsize prec = cout.precision();
        cout << setprecision(5) << "The  Median is " << mid_value << setprecision(prec) << endl;
        return 0;
    }
}
