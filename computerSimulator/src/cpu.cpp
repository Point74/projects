#pragma once

#include "cpu.h"
#include "ram.h"


using namespace std;


void compute(int buffer[], const int& sizeBuffer) {
    readRam(buffer);
    int result = 0;

    for (int i = 0; i < sizeBuffer; ++i) {
        result += buffer[i];
    }

    cout << "Sum: " << result << endl;
}