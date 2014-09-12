#include "playfair.h"

Playfair::Playfair(string key)
{
    validKey = true;
    if(key.size() < 1 || key.size() > 10)
        validKey = false;
    // TODO: other checks
    // toLower
    // bad chars
    if(!validKey) return;

    string alphabet = "abcdefghiklmnopqrstuvwxyz";
    string sanitizedKey = sanitizeKey(key);

    for(unsigned int i = 0; i < sanitizedKey.size(); i++)
        for(unsigned int j = 0; j < alphabet.size(); j++)
            if(sanitizedKey[i] == alphabet[j])
                alphabet.erase(j, 1);

    sanitizedKey.append(alphabet);

    int index = 0;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            matrix[i][j] = sanitizedKey[index++];
}

bool Playfair::isValid()
{
    return validKey;
}

string Playfair::sanitizeKey(string k)
{
    for(unsigned int i = 0; i < k.size(); i++)
        for(unsigned int j = 0; j < i; j++)
            if(k[i] == k[j])
                k.erase(i, 1);
    return k;
}

string Playfair::sanitizeText(string t)
{
    for(unsigned int i = 0; i < t.size(); i++)
        if(t[i] == 'j')
            t[i] = 'i';

    for(unsigned int i = 0; i < t.size() - 1; i += 2)
    {
        if(t[i] == t[i+1])
            t.insert(i, "x");

    }

    if(t.size() % 2 == 1)
        t.append("x");

    std::transform(t.begin(), t.end(), t.begin(), ::tolower);

    return t;
}

vec2 Playfair::findChar(char c)
{
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            if(matrix[i][j] == c)
                return vec2{i, j};
    return vec2{-1, -1};
}

string Playfair::encrypt(string plainText)
{
    plainText = sanitizeText(plainText);
    for(unsigned int i = 0; i < plainText.size() - 1; i += 2)
    {
        vec2 a = findChar(plainText[i]);
        vec2 b = findChar(plainText[i + 1]);

        // TODO: skip non-alphabeics

        encvec(a, b);

        plainText[i]   = matrix[a.x][a.y];
        plainText[i+1] = matrix[b.x][b.y];
    }
    return plainText;
}

string Playfair::decrypt(string cipherText)
{
    for(unsigned int i = 0; i < cipherText.size() - 1; i += 2)
    {
        vec2 a = findChar(cipherText[i]);
        vec2 b = findChar(cipherText[i + 1]);

        // TODO: skip non-alphabeics

        decvec(a, b);

        cipherText[i]   = matrix[a.x][a.y];
        cipherText[i+1] = matrix[b.x][b.y];
    }
    return cipherText;
}

void Playfair::encvec(vec2 &a, vec2 &b)
{
    if(a.x == b.x)
    {
        a.y = (a.y + 1) % 5;
        b.y = (b.y + 1) % 5;
    }
    else if(a.y == b.y)
    {
        a.x = (a.x + 1) % 5;
        b.x = (b.x + 1) % 5;
    }
    else
    {
        int temp = a.x;
        a.x = b.x;
        b.x = temp;
    }
}

void Playfair::decvec(vec2 &a, vec2 &b)
{
    if(a.x == b.x)
    {
        a.y = mod(a.y - 1, 5);
        b.y = mod(b.y - 1, 5);
    }
    else if(a.y == b.y)
    {
        a.x = mod(a.x - 1, 5);
        b.x = mod(b.x - 1, 5);
    }
    else
    {
        int temp = a.x;
        a.x = b.x;
        b.x = temp;
    }
}

int Playfair::mod(int i, int m)
{
    int r = i % m;
    return r < 0 ? r+m : r;
}
