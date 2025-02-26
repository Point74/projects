#pragma once

#include <fstream>
#include <string>

bool isOpenFile(fstream& file, const string& nameFile);
bool isEmptyStorage(const int storage[], const int& sizeStorage);
bool isEmptyFile(fstream& file, const string& nameFile);
void exit();
void commandsProgram();