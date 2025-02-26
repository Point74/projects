#pragma once

#include "kbd.h"
#include "ram.h"

void input(int buffer[], const int& sizeBuffer) {
    for (int i = 0; i < sizeBuffer; ++i) {
        cout << "Enter number " << i + 1 << ": ";
        cin >> buffer[i];
    }

    writeRam(buffer);
}