#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct People {
    string name;
    tm date{};
};


void addPeople(People& person, vector<People>& birthday, tm* now);
tm* nowTime();
bool compareTm(People& a, People& b);
void printPeople(const vector<People>& birthday,tm* now);


void addPeople(People& person, vector<People>& birthday, tm* now) {
    while (true) {
        string dataBirthday;
        cout << "Enter person name: ";
        getline(cin, person.name);

        if (person.name == "end") {
            break;
        }

        cout << "Enter person birthday(dd/mm/yyyy): ";
        getline(cin, dataBirthday);

        stringstream ss(dataBirthday);
        ss >> get_time(&person.date, "%d/%m/%Y");

        if (person.date.tm_year > now->tm_year ||
            (person.date.tm_mon > now->tm_mon && person.date.tm_year == now->tm_year) ||
            (person.date.tm_mday > now->tm_mday && person.date.tm_mon == now->tm_mon && person.date.tm_year == now->tm_year)) {
            cout << "Invalid data! You can't now add a person who hasn't now been born yet!\n";
        }

        person.date.tm_year = 0;

        if (person.date.tm_mon < now->tm_mon || (person.date.tm_mday < now->tm_mday && person.date.tm_mon == now->tm_mon)) {
            continue;
        }

        birthday.push_back(person);
    }

    sort(birthday.begin(), birthday.end(), compareTm);
}


bool compareTm(People& a, People& b) {
    if (a.date.tm_mon != b.date.tm_mon)
        return a.date.tm_mon < b.date.tm_mon;

    return a.date.tm_mday < b.date.tm_mday;
}


void printPeople(const vector<People>& birthday, tm* now) {
    cout << "Today: " << setw(2) << setfill('0') << now->tm_mon + 1 << '/' << now->tm_mday << endl;

    for (int i = 0; i < birthday.size(); ++i) {
        if (birthday[i].date.tm_mday == now->tm_mday && birthday[i].date.tm_mon == now->tm_mon) {
            cout << birthday[i].name << " happy birthday!\n";
        }

        else if (birthday[i].date.tm_mday > now->tm_mday || (birthday[i].date.tm_mday <= now->tm_mday && birthday[i].date.tm_mon > now->tm_mon)) {
            cout << "Near birthday:\n";
            for (int j = i; j < birthday.size(); ++j) {
                if (birthday[i].date.tm_mday == birthday[j].date.tm_mday && birthday[i].date.tm_mon == birthday[j].date.tm_mon) {
                    cout << birthday[j].name << " " << setw(2) << setfill('0') << birthday[j].date.tm_mon + 1 << '/' << setw(2) << setfill('0') << birthday[j].date.tm_mday << endl;

                } else return;

                if (j + 1 == birthday.size()) {
                    return;
                }
            }
        }
    }
}


tm* nowTime() {
    time_t t = time(nullptr);
    tm* local = localtime(&t);
    //local->tm_year = 0;

    return local;
}


int main() {
    People person;
    vector<People> birthday;

    tm* now = nowTime();

    addPeople(person, birthday, now);
    printPeople(birthday, now);
}