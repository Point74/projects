#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <limits>


using namespace std;

class PhoneBook;
class PhoneNumber;
void clearData(PhoneBook* phoneBook, PhoneNumber* phoneNumber);


class PhoneNumber {
private:
    string name;
    string phone;

    static bool isValidNumber(PhoneNumber* phoneNumber);


    friend class PhoneBook;
};


class PhoneBook {
private:
    vector<PhoneNumber> phonePerson;
    string fullInformation;
    vector<string> foundNumber;
    string message;


public:
    int command{};

    static void fillBook(PhoneBook* phoneBook, PhoneNumber* phoneNumber);
    void callPhone(PhoneBook* phoneBook, PhoneNumber* phoneNumber);
    void smsPhone(PhoneBook* phoneBook, PhoneNumber* phoneNumber);
    static void savePhones(PhoneBook* phoneBook, fstream& storagePhones);
    static void loadPhones(PhoneBook* phoneBook, fstream& storagePhones);
    static bool isSimilarNumber(PhoneBook* phoneBook, PhoneNumber* phoneNumber);


    static void printCommandsPhone() {
        cout << "\n1.add\n2.call\n3.sms\n4.print all numbers\n5.exit\n";
    }

    static void printAllNumbers(PhoneBook* phoneBook) {
        for (auto & person : phoneBook->phonePerson) {
            cout << person.phone << " " << person.name << endl;
        }
    }

    static void exitProgram() {
        cout << "\nExit from program....\n";
    }
};


bool PhoneNumber::isValidNumber(PhoneNumber* phoneNumber) {
    if (phoneNumber->phone.length() != 12) {
        return false;
    }

    for (int i = 0; i < phoneNumber->phone.length(); ++i) {
        if ((phoneNumber->phone[0] != '+' || phoneNumber->phone[1] != '7') ||
            (i >= 2 && !isdigit(phoneNumber->phone[i]))) {
            return false;
        }
    }

    return true;
}


bool PhoneBook::isSimilarNumber(PhoneBook* phoneBook, PhoneNumber *phoneNumber) {
    for (auto& iterator : phoneBook->phonePerson) {
        if (iterator.phone == phoneNumber->phone) {
            return true;
        }
    }

    return false;
}


void PhoneBook::fillBook(PhoneBook* phoneBook, PhoneNumber* phoneNumber) {

    while (true) {
        cout << "Enter number(format: +7<10 numbers>, for example '+70000000000') and person's name\n"
                "(if you want to stop filling phonebook, enter 'stop'):\n";
        getline(cin, phoneBook->fullInformation);

        if (phoneBook->fullInformation == "stop") {
            break;
        }

        stringstream ss(phoneBook->fullInformation);
        ss >> phoneNumber->phone >> phoneNumber->name;

        if (!PhoneNumber::isValidNumber(phoneNumber)) {
            cout << "You enter invalid number!\n"
                    "The number can only contain digits from 0 to 9, "
                    "without letters or any other symbols.\nTry enter data again!\n";
            continue;
        }

        if (PhoneBook::isSimilarNumber(phoneBook, phoneNumber)) {
            cout << "Number which you entered already in phonebook! Enter other data.\n";
            continue;
        }

        cout << "Information added!\n";
        phoneBook->phonePerson.push_back(*phoneNumber);
    }
}


void PhoneBook::callPhone(PhoneBook *phoneBook, PhoneNumber *phoneNumber) {
    while (true) {
        cout << "What do you want to enter?\n1.Contact name\n2.Phone number\nCommand(1 or 2):";
        cin >> phoneBook->command;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (phoneBook->command != 1 && phoneBook->command != 2) {
            cout << "Invalid command! Try again!\n";

        } else break;
    }

    if (phoneBook->command == 1) { // если имя
        while (true) {
            cout << "Enter the name of the contact you want to call"
                    "(if you don't want to call enter 'stop'):\n";
            getline(cin, phoneNumber->name);

            if (phoneNumber->name == "stop") {
                return;
            }

            cout << "Found numbers:\n";
            int count = 0;
            for (int i = 0; i < phoneBook->phonePerson.size(); ++i) {
                if (phoneBook->phonePerson[i].name == phoneNumber->name) {
                    cout << count + 1 << ". " << phoneBook->phonePerson[i].phone << endl;
                    foundNumber.push_back(phoneBook->phonePerson[i].phone);
                }
            }

            if (foundNumber.empty()) {
                cout << "No numbers were found for this name! Try again!\n";
                continue;

            } else if (foundNumber.size() == 1) {
                cout << '\n' << phoneNumber->name << " " << foundNumber[0] << "\nCALL\n";
                break;

            } else if (foundNumber.size() > 1) {
                while (true) {
                    cout << "Which phone number you want to call?\nAnswer: ";
                    cin >> phoneBook->command;

                    if (phoneBook->command > foundNumber.size() || phoneBook->command < 1) {
                        cout << "Invalid command! Try again!\n";

                    } else {
                        cout << '\n' << phoneNumber->name << " " << foundNumber[phoneBook->command - 1] << "\nCALL\n";
                        break;
                    }
                }

                break;
            }
        }

        foundNumber.clear();

    } else if (phoneBook->command == 2) {
        while (true) {
            cout << "Enter phone number you want to call: ";
            getline(cin, phoneNumber->phone);
            if (!PhoneNumber::isValidNumber(phoneNumber)) {
                cout << "You enter invalid phone number! Try again!\n";
                continue;
            }

            bool flag = false;
            for (auto &person: phoneBook->phonePerson) {
                if (person.phone == phoneNumber->phone) {
                    cout << '\n' << person.name << " " << phoneNumber->phone << "\nCALL\n";
                    flag = true;
                    break;
                }
            }

            if (!flag) {
                cout << "No people were found for this name! Try again!\n";

            } else break;
        }
    }
}


void PhoneBook::smsPhone(PhoneBook *phoneBook, PhoneNumber *phoneNumber) {
    while (true) {
        cout << "What do you want to enter?\n1.Contact name\n2.Phone number\nCommand(1 or 2):";
        cin >> phoneBook->command;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (phoneBook->command != 1 && phoneBook->command != 2) {
            cout << "Invalid command! Try again!\n";

        } else break;
    }

    if (phoneBook->command == 1) { // если имя
        while (true) {
            cout << "Enter the name of the contact you want to sms"
                    "(if you don't want to sms enter 'stop'): ";
            getline(cin, phoneNumber->name);

            if (phoneNumber->name == "stop") {
                return;
            }

            cout << "Found numbers:\n";
            int count = 0;
            for (auto & person : phoneBook->phonePerson) {
                if (person.name == phoneNumber->name) {
                    cout << count + 1 << ". " << person.phone << endl;
                    foundNumber.push_back(person.phone);
                }
            }

            if (foundNumber.empty()) {
                cout << "No numbers were found for this name! Try again!\n";
                continue;

            } else if (foundNumber.size() == 1) {
                cout << '\n' << phoneNumber->name << " " << foundNumber[0] << "\n Enter message:\n";
                getline(cin, phoneBook->message);
                cout << "Sent!\n";

                break;

            } else if (foundNumber.size() > 1) {
                while (true) {
                    cout << "Which phone number you want to sms?\nAnswer: ";
                    cin >> phoneBook->command;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (phoneBook->command > foundNumber.size() || phoneBook->command < 1) {
                        cout << "Invalid command! Try again!\n";

                    } else {
                        cout << '\n' << phoneNumber->name << " " << foundNumber[phoneBook->command - 1] << "\n Enter message:\n";
                        getline(cin, phoneBook->message);
                        cout << "Sent!\n";

                        break;
                    }
                }

                break;
            }
        }

        foundNumber.clear();

    } else if (phoneBook->command == 2) {
        while (true) {
            cout << "Enter phone number you want to sms:\n";
            getline(cin, phoneNumber->phone);
            if (!PhoneNumber::isValidNumber(phoneNumber)) {
                cout << "You enter invalid phone number! Try again!\n";
                continue;
            }

            bool flag = false;
            for (auto &person: phoneBook->phonePerson) {
                if (person.phone == phoneNumber->phone) {
                    cout << '\n' << person.name << " " << phoneNumber->phone << "\n Enter message:\n";
                    getline(cin, phoneBook->message);
                    cout << "Sent!\n";

                    flag = true;
                    break;
                }
            }

            if (!flag) {
                cout << "No people were found for this name! Try again!\n";

            } else break;
        }
    }
}


void PhoneBook::savePhones(PhoneBook *phoneBook, fstream &storagePhones) {
    storagePhones.clear();
    storagePhones.seekp(0, ios::beg);

    for (auto & person : phoneBook->phonePerson) {
        storagePhones << person.phone << " " << person.name << endl;
    }
}


void PhoneBook::loadPhones(PhoneBook* phoneBook, fstream &storagePhones) {
    storagePhones.clear();
    storagePhones.seekg(0, ios::beg);

    while (getline(storagePhones, phoneBook->fullInformation)) {
        PhoneNumber infoNumber;
        stringstream ss(phoneBook->fullInformation);
        ss >> infoNumber.phone >> infoNumber.name;
        phoneBook->phonePerson.push_back(infoNumber);

    }
}


void clearData(PhoneBook* phoneBook, PhoneNumber* phoneNumber) {
    delete phoneBook;
    delete phoneNumber;
    phoneBook = nullptr;
    phoneNumber = nullptr;
}


int main() {
    auto* phoneBook = new PhoneBook();
    auto* phoneNumber = new PhoneNumber();

    fstream storagePhones("phones.txt");
    if (!storagePhones.is_open()) {
        storagePhones.open("phones.txt", ios::out);

        if (!storagePhones.is_open()) {
            cout << "File don't open!\n";
            clearData(phoneBook, phoneNumber);
            return 1;
        }
    }

    storagePhones.seekg(0, ios::end);
    if (storagePhones.tellg() == 0) {
        cout << "File is empty! You can fill it out!\n";
        PhoneBook::fillBook(phoneBook, phoneNumber);
    }

    PhoneBook::loadPhones(phoneBook, storagePhones);

    while (true) {
        PhoneBook::printCommandsPhone();
        cout << "Enter command for telephone: ";
        cin >> phoneBook->command;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (phoneBook->command == 1) { // добавить номер
            PhoneBook::fillBook(phoneBook, phoneNumber);

        } else if (phoneBook->command == 2) { // позвонить
            phoneBook->callPhone(phoneBook, phoneNumber);

            while (true) {
                string stopAction;
                cout << "Enter 'stop' to stop calling\nCommand: ";
                getline(cin, stopAction);
                if (stopAction != "stop") {
                    cout << "Invalid command! Try again!\n";

                } else break;
            }

        } else if (phoneBook->command == 3) { // написать смс
            phoneBook->smsPhone(phoneBook, phoneNumber);

        } else if (phoneBook->command == 4) { // вывод всех номеров
            PhoneBook::printAllNumbers(phoneBook);

        } else if (phoneBook->command == 5) { // выйти из программы
            PhoneBook::savePhones(phoneBook, storagePhones);
            PhoneBook::exitProgram();
            break;

        }
    }

    clearData(phoneBook, phoneNumber);
}