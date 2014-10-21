#ifndef HILLCIPHER3_H
#define HILLCIPHER3_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class HillCipher3
{
public:
    HillCipher3(string key);
    bool isValid();
    string encrypt(string plainText);
    string decrypt(string cipherText);

private:
    bool validKey;
    int matrix[3][3];
    int invmat[3][3];
    string sanitizeText(string t);
};

#endif // HILLCIPHER3_H
