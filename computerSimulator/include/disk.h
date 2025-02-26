#pragma once

#include <fstream>

using namespace std;

void save(fstream& file, int buffer[], const int& sizeBuffer);
void load(fstream& file, int buffer[], const int& sizeBuffer);