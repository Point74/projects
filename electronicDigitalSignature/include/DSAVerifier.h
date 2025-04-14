#pragma once

#include "DSAKeyGenerator.h"
#include "utils.h"

#include <string>

using namespace std;

class DSAVerifier {
    DSAKeyGenerator& keyGenerator;
    unsigned long long publicKey;

public:
    DSAVerifier(DSAKeyGenerator& generator, unsigned long long key);

    bool verifyMessage(const string& message, unsigned long long r, unsigned long long s);
};