#pragma once


class DSAKeyGenerator {
    unsigned long long p, q, g;
    unsigned long long privateKey, publicKey;

public:
    DSAKeyGenerator();

    unsigned long long getP() const;

    unsigned long long getQ() const;

    unsigned long long getG() const;

    unsigned long long getPublicKey() const;

    unsigned long long getPrivateKey() const;
};