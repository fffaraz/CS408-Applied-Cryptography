#ifndef HILLCIPHER_H
#define HILLCIPHER_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class HillCipher
{
public:
    HillCipher(string key);
    bool isValid();
    string encrypt(string plainText);
    string decrypt(string cipherText);
};

#endif // HILLCIPHER_H
