#include "DSAKeyGenerator.h"
#include "utils.h"

#include <iostream>

DSAKeyGenerator::DSAKeyGenerator() {
    q = randomGeneratePrime(1000, 10000);

    unsigned long long k = 2;
    while (true) {
        p = k * q + 1;
        if (isPrime(p)) {
            break;
        }

        k++;
    }

    unsigned long long v = randomGenerateNumber(2, p - 2);
    g = modPow(v, (p - 1) / q, p);

    if (g <= 1)
        cerr << "Error: g <= 1!\n";

    privateKey = randomGenerateNumber(1, q - 1);
    publicKey = modPow(g, privateKey, p);
}

unsigned long long DSAKeyGenerator::getP() const {
    return p;
}

unsigned long long DSAKeyGenerator::getQ() const {
    return q;
}

unsigned long long DSAKeyGenerator::getG() const {
    return g;
}

unsigned long long DSAKeyGenerator::getPublicKey() const {
    return publicKey;
}

unsigned long long DSAKeyGenerator::getPrivateKey() const {
    return privateKey;
}