#include "DSAVerifier.h"


DSAVerifier::DSAVerifier(DSAKeyGenerator& generator, unsigned long long key) : keyGenerator(generator), publicKey(key) {}

bool DSAVerifier::verifyMessage(const string& message, unsigned long long r, unsigned long long s) {
    unsigned long long q = keyGenerator.getQ();
    unsigned long long p = keyGenerator.getP();
    unsigned long long g = keyGenerator.getG();

    if (r > 0 && r < q && s > 0 && s < q) {
        unsigned long long messageHash = simpleHash(message);
        unsigned long long modularInverseS = modInverse(s, q);
        unsigned long long hashMultiplier = (messageHash * modularInverseS) % q;
        unsigned long long signatureMultiplier = (r * modularInverseS) % q;
        unsigned long long part1 = modPow(g, hashMultiplier, p);
        unsigned long long part2 = modPow(publicKey, signatureMultiplier, p);
        unsigned long long resultSignatureComponent = ((part1 * part2) % p) % q;

        return resultSignatureComponent == r;
    }

    return false;
}