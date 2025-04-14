#include <iostream>

#include "DSAKeyGenerator.cpp"
#include "DSASigner.cpp"
#include "DSAVerifier.cpp"
#include "utils.cpp"


int main() {
    DSAKeyGenerator keyGenerator;

    cout << "Private key: " << keyGenerator.getPrivateKey();
    cout << "\nPublic key: " << keyGenerator.getPublicKey();

    DSASigner signer(keyGenerator);
    string message;
    message = "Hello, DSA!";

//    cout << "Enter message: ";
//    getline(cin, message);

    auto signature = signer.signMessage(message);
    unsigned long long r = signature.first; // отпечаток подписи
    unsigned long long s = signature.second; // подпись на сообщении

    cout << "\nMessage: " << message;
    cout << "\n Signature:\n";
    cout << "r = " << r;
    cout << "\ns = " << s;

    DSAVerifier verifier(keyGenerator, keyGenerator.getPublicKey());
    bool isValid = verifier.verifyMessage(message, r, s);

    if (isValid)
        cout << "\nSignature is true!\n";

    else cout << "\nSignature is false!\n";
}