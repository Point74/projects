#pragma once

#include "utils.h"

bool isOpenFile(fstream& file, const string& nameFile) {
    if (!file.is_open()) {
        file.open(nameFile, ios::out);

        if (!file.is_open()) {
            cerr << "\nFile don't open!\n";
            return false;
        }
    }

    return true;
}


bool isEmptyFile(fstream& file, const string& nameFile) {
    file.seekg(0, ios::end);
    if (file.tellg() == 0) {
        return true;
    }

    return false;
}


bool isEmptyStorage(const int storage[], const int& sizeStorage) {
    for (int i = 0; i < sizeStorage; ++i) {
        if (storage[i] != 0) {
            return false;
        }
    }

    return true;
}


void commandsProgram() {
    cout << "\n1. Sum\n2. Save\n3. Load\n4. Input\n5. Display\n6. Exit\n";
}


void exit() {
    cout << "Stop program....";
}