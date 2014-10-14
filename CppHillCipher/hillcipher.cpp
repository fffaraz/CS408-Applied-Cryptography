#include "hillcipher.h"

HillCipher::HillCipher(string key)
{
    validKey = false;
    if(key.size() != 4) return;

    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    for(unsigned int i = 0; i < key.size(); i++)
        if(key[i] < 'a' || key[i] > 'z')
            return;

    matrix[0][0] = key[0] - 'a';
    matrix[0][1] = key[1] - 'a';
    matrix[1][0] = key[2] - 'a';
    matrix[1][1] = key[3] - 'a';

    cout << "mat: " << matrix[0][0] << " " << matrix[0][1] << " " << matrix[1][0] << " " << matrix[1][1] << endl;

    int det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    cout << "det1: " << det << endl;
    if(det == 0) return;

    det = det % 26;
    cout << "det2: " << det << endl;
    if(det < 0) det += 26;
    cout << "det3: " << det << endl;

    int invdet;
    for(int i=1; i<26; i++)
        if( (i * det) % 26 == 1)
        {
            invdet = i;
            break;
        }
    cout << "invdet: " << invdet << endl;

    invmat[0][0] = invdet * matrix[1][1];
    invmat[0][1] = invdet * matrix[0][1] * -1;
    invmat[1][0] = invdet * matrix[1][0] * -1;
    invmat[1][1] = invdet * matrix[0][0];

    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
        {
            invmat[i][j] = invmat[i][j] % 26;
            if(invmat[i][j] < 0) invmat[i][j] += 26;
        }

    cout << "inv: " << invmat[0][0] << " " << invmat[0][1] << " " << invmat[1][0] << " " << invmat[1][1] << endl;

    validKey = true;
}

bool HillCipher::isValid()
{
    return validKey;
}

string HillCipher::sanitizeText(string t)
{
    std::transform(t.begin(), t.end(), t.begin(), ::tolower);

    int counter = 0;
    for(unsigned int i = 0; i < t.size(); i++)
        if(t[i] >= 'a' && t[i] <= 'z')
            counter++;
    if(counter % 2 == 1)
        t.append("x");

    return t;
}

string HillCipher::encrypt(string plainText)
{
    plainText = sanitizeText(plainText);

    for(unsigned int i = 0; i < plainText.size() - 1; i += 2)
    {
        while(plainText[i] < 'a' || plainText[i] > 'z') i++;
        int c1 = i;

        while(plainText[i + 1] < 'a' || plainText[i + 1] > 'z') i++;
        int c2 = i + 1;

        char p1 = plainText[c1] - 'a';
        char p2 = plainText[c2] - 'a';

        char q1 = (p1*matrix[0][0] + p2*matrix[1][0]) % 26;
        char q2 = (p1*matrix[0][1] + p2*matrix[1][1]) % 26;

        plainText[c1] = q1 + 'a';
        plainText[c2] = q2 + 'a';
    }

    return plainText;
}

string HillCipher::decrypt(string cipherText)
{
    cipherText = sanitizeText(cipherText);

    for(unsigned int i = 0; i < cipherText.size() - 1; i += 2)
    {
        while(cipherText[i] < 'a' || cipherText[i] > 'z') i++;
        int c1 = i;

        while(cipherText[i + 1] < 'a' || cipherText[i + 1] > 'z') i++;
        int c2 = i + 1;

        char p1 = cipherText[c1] - 'a';
        char p2 = cipherText[c2] - 'a';

        char q1 = (p1*invmat[0][0] + p2*invmat[1][0]) % 26;
        char q2 = (p1*invmat[0][1] + p2*invmat[1][1]) % 26;

        cipherText[c1] = q1 + 'a';
        cipherText[c2] = q2 + 'a';
    }
    return cipherText;
}

