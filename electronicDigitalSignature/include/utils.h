#pragma once

#include <string>

using namespace std;

unsigned long long modPow(unsigned long long base, unsigned long long exp, unsigned long long mod);
unsigned long long randomGenerateNumber(const unsigned long long& start, const unsigned long long& stop);
unsigned long long randomGeneratePrime(const unsigned long long& start, const unsigned long long& stop);
bool isPrime(unsigned long long number);
unsigned long long simpleHash(const string& message);
unsigned long long modInverse(unsigned long long a, unsigned long long mod);