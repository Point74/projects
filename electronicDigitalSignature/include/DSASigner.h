#pragma once

#include "DSAKeyGenerator.h"

#include <string>
#include <utility>

using namespace std;

class DSASigner {
    DSAKeyGenerator& keyGenerator;

public:
    DSASigner(DSAKeyGenerator& generator);

    pair<unsigned long long, unsigned long long> signMessage(const string& message);
};