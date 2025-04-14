#include "../include/utils.h"
#include <random>


unsigned long long simpleHash(const string& message) {
    unsigned long long hash = 0;
    const int p = 31;
    const int m = 1e9 + 9;

    for (char element : message) {
        hash = (hash * p + element) % m;
    }

    return hash;
}


unsigned long long modInverse(unsigned long long a, unsigned long long mod) {
    long long originalMod = mod;
    long long x0 = 0, x1 = 1;

    while (a > 1) {
        long long quotient = a / mod;
        long long remainder = a % mod;

        a = mod;
        mod = remainder;

        long long temp = x0;
        x0 = x1 - quotient * x0;
        x1 = temp;
    }

    if (x1 < 0)
        x1 += originalMod;

    return static_cast<long long>(x1);
}


unsigned long long randomGeneratePrime(const unsigned long long& start, const unsigned long long& stop) {
    while (true) {
        unsigned long long num = randomGenerateNumber(start, stop);
        if (isPrime(num)) {
            return num;
        }
    }
}


bool isPrime(unsigned long long number) {
    if (number < 2)
        return false;

    for (long long i = 2; i * i <= number; ++i) {
        if (number % i == 0)
            return false;
    }

    return true;
}


unsigned long long randomGenerateNumber(const unsigned long long& start, const unsigned long long& stop) {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<unsigned long long> dist(start, stop);

    return dist(gen);
}


unsigned long long modPow(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;

    base %= mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}