#include <iostream>
#include <map>
#include <string>
#include <limits>
#include <vector>

using namespace std;

void addSubscriber(map<string, string>& numberToSurname, map<string, vector<string>>& surnameToNumber, string& surname, string& phoneNumber);
void findOutSubscriberSurname(map<string, string>& numberToSurname, string& phoneNumber, int& storage);
void findOutSubscriberPhoneNumber(map<string, vector<string>>& surnameToNumber, string& surname, int& storage);


void addSubscriber(map<string, string>& numberToSurname, map<string, vector<string>>& surnameToNumber, string& surname, string& phoneNumber) {
    string answer;
    bool flag = true;
    while (flag) {
        cout << "Enter phone number: ";
        getline(cin, phoneNumber);

        cout << "Enter surname subscriber: ";
        getline(cin, surname);

        if (!numberToSurname.count(phoneNumber)) { // если нет номера в мапе
            numberToSurname.insert({phoneNumber, surname});
        }

        surnameToNumber[surname].push_back(phoneNumber);

        while (true) {
            cout << "Add another subscriber?(y/n)";
            getline(cin, answer);

            if (answer == "n") {
                flag = false;
                break;

            } else if (answer == "y") {
                break;

            } else {
                cout << "Invalid command! Try again!\n";
            }
        }
    }
}


void findOutSubscriberSurname(map<string, string>& numberToSurname, string& phoneNumber, int& storage) {
    cout << "Enter phone number: ";
    getline(cin, phoneNumber);

    auto it = numberToSurname.find(phoneNumber);
    if (it != numberToSurname.end()) {
        cout << it->second << endl;
    }
}


void findOutSubscriberPhoneNumber(map<string, vector<string>>& surnameToNumber, string& surname, int& storage) {
    cout << "Enter subscriber's surname: ";
    getline(cin, surname);

    auto it = surnameToNumber.find(surname);
    if (it != surnameToNumber.end()) {
        for (auto& elem : it->second) {
            cout << elem << '\n';
        }

    } else {
        cout << "Subscriber with this number doesn't exist!\n";
    }
}


int main() {
    map<string, string> numberToSurname; // номер - фамилия
    map<string, vector<string>> surnameToNumber; // фамилия - номер/номера

    string surname, phoneNumber;
    int command;
    int storage = 0;

    while (true) {
        cout << "Commands:\n"
                "1. Add the phone number and surname of the subscriber to the directory\n"
                "2. Find out a subscriber's surname by phone number\n"
                "3. Find out a subscriber's phone number by surname\n";
        cout << "\nIf you want to stop, enter '0'.\nEnter command for telephone directory: ";
        cin >> command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (command == 0) {
            break;
        }

        switch (command) {
            case 1:
                addSubscriber(numberToSurname, surnameToNumber, surname, phoneNumber);
                break;

            case 2:
                findOutSubscriberSurname(numberToSurname, phoneNumber, storage);
                break;

            case 3:
                findOutSubscriberPhoneNumber(surnameToNumber, phoneNumber, storage);
                break;

            default:
                cout << "Invalid command!";
                continue;
        }
    }
}