#pragma once

#include "ram.h"
#include "utils.h"

static const int sizeRAM = 8;
static int ram[sizeRAM] = {};


void readRam(int buffer[]) {
    isEmptyStorage(ram, sizeRAM);
    for (int i = 0; i < sizeRAM; ++i) {
        buffer[i] = ram[i];
    }
}


void writeRam(const int buffer[]) {
    for (int i = 0; i < sizeRAM; ++i) {
        ram[i] = buffer[i];
    }
}

//    file.seekg(0, ios::end);
//    if (file.tellg() == 0) {
//        cout << "File is empty!\n";
//        input(buffer, sizeRAM);
//
//    } else {
//        file.clear();
//        file.seekg(0, ios::beg);
//        int number;
//        int index = 0;
//        while (file >> number) {
//            buffer[index] = number;
//            index++;
//        }
//    }