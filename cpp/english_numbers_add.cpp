
#include <iostream>
#include <map>
using namespace std;

string & trim(string &s)
{
    if (s.empty())
        return s;

    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
    return s;
}

int get_number_from_string(string &s, map<const char *, int> &num_map){
    int sum = 0;
    string new_s = trim(s);
    cout << "trimed:" << new_s << endl;

    int start = 0;
    int space_pos = -1;
    string num_str;
    int num = 0;
    map<const char *, int>::iterator it;
    // find space
    while((space_pos = new_s.find(' ', start)) != string::npos){
        num_str = new_s.substr(start, space_pos - start);
        cout << "sub num str:" << num_str << endl;
        start = space_pos + 1;
        // it = num_map.find(num_str.c_str());
        num = num_map[trim(num_str).c_str()];
        // num = it->second;
        cout << "get num from map: " << num << endl;
        sum = sum * 10 + num;
    }
    num_str = new_s.substr(start);
    cout << "get the last sub string: " << num_str.c_str() << endl;
    // it = num_map.find(num_str.c_str());
    // num = it->second;
    cout << num_map["nine"] << "|" << endl;
    cout << num_str.c_str() << "|" << endl;
    num = num_map[num_str.c_str()];
    cout << "get num from map: " << num << endl;
    sum = sum * 10 + num;
    cout << "get num: " << sum << endl;
    return sum;
}

int main(){
    char input[256];
    int add_pos, equal_pos;
    int a, b;

    map<const char *, int> num_map;
    const char * num_strs[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for(int i = 0; i < 10; i++) {
        // OR: num_map[num_strs[i]] = i;
        num_map.insert(pair<const char *, int>(num_strs[i], i));
    }

    for(int i = 0; i < 10; i++){
        cout << num_map[num_strs[i]] << " ";
    }
    cout << endl;

    while(!cin.eof()){
        cin.getline(input, 256);
        string exp(input);

        add_pos = exp.find_first_of('+');
        equal_pos = exp.find_first_of('=');
        // find A string
        string a_str = exp.substr(0, add_pos);
        cout << "a_str: " << a_str << endl;
        a = get_number_from_string(a_str, num_map);
        // find B string
        string b_str = exp.substr(add_pos + 1, equal_pos - add_pos - 1);
        cout << "b_str: " << b_str << endl;
        b = get_number_from_string(b_str, num_map);
        cout << a + b << endl;
    }
    return 0;
}
