#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <cmath>
#include <cctype>


using namespace std;


map<char, int> createStorage();
bool isPrimeNumber(const int& number);
int parameterCloseKey(const int& phi, const int& e);
void saveCloseKey(const int* key);
bool loadCloseKey(int* key);
void clearBuffer();
int* encryptLine(const map<char, int>& storage, const int* key, const string& line, const size_t& sizeLine);
char* decryptLine(const map<char, int>& storage, int* encryptInfo, const int* key, const int& sizeInfo);
void saveEncryptLine(int* encryptArray, const size_t& sizeLine);
int* loadEncryptLine(const int& sizeInfo);
int sizeEncryptInfo();
void fillKey(int* key, const int& firstParameter, const int& secondParameter);
long long modAndExp(long long base, long long exp, long long mod);



map<char, int> createStorage() {
    map<char, int> charToNum;
    for (char i = 'A'; i <= 'Z'; ++i) {
        charToNum[i] = i - 'A' + 1;
    }

    charToNum[' '] = 27;

    for (char i = '0'; i <= '9'; ++i) {
        charToNum[i] = 28 + (i - '0');
    }

    return charToNum;
}


bool isPrimeNumber(const int& number) {
    if (number <= 1) {
        return false;

    } else {
        int count = 0;
        for (int i = 2; i * i <= number; ++i) {
            if (number % i == 0) {
                count++;
            }
        }

        if (count > 0) {
            return false;

        } else return true;
    }
}


int parameterCloseKey(const int& phi, const int& e) {
    int number;

    for (int i = 1; i < INT_MAX; ++i) {
        number = (i * phi + 1) / e;
        if (isPrimeNumber(number)) {
            return number;
        }
    }

    return 1;
}


void saveCloseKey(const int* key) {
    fstream file("rsa/closeKey.txt", ios::out);
    if (!file.is_open()) {
        cout << "File don't open!\n";
        return;
    }

    file << key[0] << " " << key[1] << "\n";

    file.close();
}


bool loadCloseKey(int* key) {
    fstream file("rsa/closeKey.txt", ios::in);
    if (!file.is_open()) {
        cout << "File don't create!";
        return false;

    } else {
        int e, d;
        file >> e >> d;
        file.close();

        key[0] = e;
        key[1] = d;

        return true;
    }
}


void saveEncryptLine(int* encryptArray, const size_t& sizeLine) {
    fstream file("rsa/encrypt.txt", ios::out);
    if (!file.is_open()) {
        cout << "file don't open!\n";
        return;
    }

    for (int i = 0; i < sizeLine; ++i) {
        file << encryptArray[i] << " ";
    }

    file.close();
}


int* loadEncryptLine(const int& sizeInfo) {
    fstream file("rsa/encrypt.txt", ios::in);
    if (!file.is_open()) {
        cout << "File don't open!\n";
        return nullptr;
    }

    int* array = new int[sizeInfo];
    for (int i = 0; i < sizeInfo; ++i) {
        file >> array[i];
    }

    file.close();

    return array;
}


void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


int* encryptLine(const map<char, int>& storage, const int* key, const string& line, const size_t& sizeLine) {
    int* encryptInfo = new int[sizeLine];

    for (int i = 0; i < sizeLine; ++i) {
        char elementLine = static_cast<char>(toupper(line[i]));

        auto it = storage.find(elementLine);
        if (it != storage.end()) {
            encryptInfo[i] = static_cast<int>(modAndExp(it->second, key[0], key[1]));

        } else {
            cout << "Invalid symbol in line!\n";

            delete[] encryptInfo;
            return nullptr;
        }
    }

    return encryptInfo;
}


char* decryptLine(const map<char, int>& storage, int* encryptInfo, const int* key, const int& sizeInfo) {
    char* decryptInfo = new char[sizeInfo];

    for (int i = 0; i < sizeInfo; ++i) {
        int result = static_cast<int>(modAndExp(encryptInfo[i], key[0], key[1]));

        bool found = false;
        for (const auto& it : storage) {
            if (it.second == result) {
                decryptInfo[i] = it.first;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Invalid symbol in line!\n";

            delete[] decryptInfo;
            return nullptr;
        }
    }

    return decryptInfo;
}



long long modAndExp(long long base, long long exp, long long mod) {
    long long result = 1;

    base %= mod;

    while (exp > 0) {
        if (exp & 1) { // если exp нечётная
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        exp >>= 1; // делим exp на 2
    }

    return result;
}


int sizeEncryptInfo() {
    fstream file("rsa/encrypt.txt", ios::in);
    if (!file.is_open()) {
        cout << "File don't open!\n";
        return 0;
    }

    int number;
    int count = 0;
    while (file >> number) {
        count++;
    }

    return count;
}


void fillKey(int* key, const int& firstParameter, const int& secondParameter) {
    key[0] = firstParameter;
    key[1] = secondParameter;
}


int main() {
    map<char, int> storage = createStorage();
    int sizeKey = 2;

    int command;
    while (true) {
        cout << "Enter command:\n1. Encrypt\n2. Decrypt\nCommand: ";
        cin >> command;

        if (command != 1 && command != 2) {
            cout << "Invalid command! Try again!\n";

        } else break;
    }

    int closeKey[sizeKey];
    int openKey[sizeKey];

    if (command == 1) { // шифрование
        int p, q;
        while (true) {
            cout << "Enter two prime numbers: ";
            cin >> p >> q;

            if (isPrimeNumber(p) && isPrimeNumber(q)) {
                break;

            } else cout << "You enter not prime number! Try again!\n";
        }

        long n = p * q;
        long phi = (p - 1) * (q - 1);

        int e;
        while (true) {
            cout << "Enter random number, which 0 < number < " << n << ": ";
            cin >> e;

            if (e > 0 && e < n) {
                break;

            } else cout << "Invalid number! Try again!\n";
        }

        fillKey(openKey, e, n);

        int d = parameterCloseKey(phi, e);
        fillKey(closeKey, d, n);

        saveCloseKey(closeKey);

        clearBuffer();

        string line;
        cout << "Enter line, which you want to encrypt: ";
        getline(cin, line);

        size_t sizeLine = line.length();

        int* encryptArray = encryptLine(storage, openKey, line, sizeLine);
        if (encryptArray == nullptr) {
            cout << "We can't encrypt line!\n";
            return 1;
        }

        saveEncryptLine(encryptArray, sizeLine);
        delete[] encryptArray;

    } else { // расшиврование
        int sizeInfo = sizeEncryptInfo();
        if (sizeInfo == 0) {
            cout << "We don't have encrypt information!\n";
            return 1;
        }

        if (!loadCloseKey(closeKey)) {
            cout << "We don't have close key!\n";
            return 1;
        }

        int* encryptInfo = loadEncryptLine(sizeInfo);
        if (encryptInfo == nullptr) {
            cout << "We can't encrypt line! Encrypted information may not created.\n";
            return 1;
        }

        char* decryptInfo = decryptLine(storage, encryptInfo, closeKey, sizeInfo);
        if (decryptInfo == nullptr) {
            cout << "We can't decrypt line!\n";
            delete[] decryptInfo;
            delete[] encryptInfo;

            return 1;
        }

        cout << "Decrypt information: ";
        for (int i = 0; i < sizeInfo; ++i) {
            cout << decryptInfo[i];
        }

        delete[] encryptInfo;
        delete[] decryptInfo;
    }
}