#pragma once

#include "gpu.h"
#include "ram.h"

void display(int buffer[], const int& sizeBuffer) {
    readRam(buffer);

    cout << "Buffer: ";
    for (int i = 0; i < sizeBuffer; ++i) {
        cout << buffer[i] << " ";
    }
}