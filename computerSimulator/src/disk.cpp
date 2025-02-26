#pragma once

#include "disk.h"
#include "ram.h"

using namespace std;

void save(fstream& file, int buffer[], const int& sizeBuffer) {
    readRam(buffer);

    for (int i = 0; i < sizeBuffer; ++i) {
        file << buffer[i] << endl;
    }

    file.close();
}


void load(fstream& file, int buffer[], const int& sizeBuffer) {
    for (int i = 0; i < sizeBuffer; ++i) {
        file >> buffer[i];
    }

    writeRam(buffer);
}