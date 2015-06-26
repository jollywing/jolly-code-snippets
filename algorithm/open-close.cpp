#include <iostream>
#include <stdlib.h>

using namespace std;

class TimeString {
public:
    // Assume format of s is HH:MM:SS
    TimeString(string &s) {
        hour = s.substr(0, 2);
        minute = s.substr(3, 2);
        second = s.substr(6, 2);
    }

    friend ostream & operator<<(ostream & out, TimeString &ts) {
        out << ts.hour << ":" << ts.minute << ":" << ts.second;
        return out;
    }

    unsigned int get_seconds() {
        int h, m, s;
        h = atoi(hour.c_str());
        m = atoi(minute.c_str());
        s = atoi(second.c_str());
        return h * 3600 + m * 60 + s;
    }

    bool operator>(TimeString &ts) {
        int lhs, rhs;
        lhs = this->get_seconds();
        rhs = ts.get_seconds();
        return lhs > rhs;
    }

    string hour;
    string minute;
    string second;
};

class Record {
public:
    string id;
    TimeString *login;
    TimeString *logout;

    Record(string card_id, string come, string leave) {
        id = card_id;
        login = new TimeString(come);
        logout = new TimeString(leave);
    }

    ~Record() {
        delete login;
        delete logout;
    }
};

int main() {
    int day_num, rec_num, i, j;
    string card_id, come, leave;
    int first_come, last_leave;
    cin >> day_num;
    string open_close[day_num][2];
    for(j = 0; j < day_num; j++) {
        cin >> rec_num;
        Record * recs[rec_num];
        for(i = 0; i < rec_num; i++) {
            cin >> card_id;
            cin >> come;
            cin >> leave;
            recs[i] = new Record(card_id, come, leave);
        }
        first_come = 0;
        last_leave = 0;
        for(i = 1; i < rec_num; i++) {
            if (recs[first_come]->login > recs[i]->login) {
                first_come = i;
            }
            if (recs[i]->logout > recs[last_leave]->logout)
                last_leave = i;
        }
        for(i = 0; i < rec_num; i++) {
            delete recs[i];
            recs[i] = NULL;
        }
        open_close[j][0] = recs[first_come]->id;
        open_close[j][1] = recs[last_leave]->id;
    }

    for(j = 0; j < day_num; j++) {
        cout << open_close[j][0] << " " << open_close[j][1] << endl;
    }
	return 0;
}
