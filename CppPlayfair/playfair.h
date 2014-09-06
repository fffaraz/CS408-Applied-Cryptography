#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <string>
#include <vector>

using namespace std;

struct vec2
{
    int x, y;
};


class Playfair
{
public:
    Playfair(string key);
    bool isValid();
    string encrypt(string plainText);
    string decrypt(string cipherText);

private:
    bool validKey;
    char matrix[5][5];
    string sanitizeKey(string k);
    string sanitizeText(string t);
    vec2 findChar(char c);
    void encvec(vec2 &a, vec2 &b);
    void decvec(vec2 &a, vec2 &b);
    int mod(int i, int m);

};

#endif // PLAYFAIR_H
