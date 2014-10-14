#ifndef HILLCIPHER_H
#define HILLCIPHER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class HillCipher
{
public:
    HillCipher(string key);
    bool isValid();
    string encrypt(string plainText);
    string decrypt(string cipherText);

private:
    bool validKey;
    int matrix[2][2];
    int invmat[2][2];
    string sanitizeText(string t);
};

#endif // HILLCIPHER_H
