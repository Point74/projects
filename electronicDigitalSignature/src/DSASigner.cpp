#include "DSASigner.h"
#include "utils.h"


DSASigner::DSASigner(DSAKeyGenerator& generator) : keyGenerator(generator) {}

pair<unsigned long long, unsigned long long> DSASigner::signMessage(const string& message) {
    unsigned long long hash = (simpleHash(message)) % keyGenerator.getQ();
    unsigned long long k = randomGenerateNumber(1, keyGenerator.getQ() - 1);
    unsigned long long r = modPow(keyGenerator.getG(), k, keyGenerator.getP()) % keyGenerator.getQ();
    unsigned long long kInverse = modInverse(k, keyGenerator.getQ());
    unsigned long long s = (kInverse * (hash + keyGenerator.getPrivateKey() * r)) % keyGenerator.getQ();

    return {r, s};
}