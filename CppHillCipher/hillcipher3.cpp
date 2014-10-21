#include "hillcipher3.h"


HillCipher3::HillCipher3(string key)
{
    validKey = false;
    if(key.size() != 9) return;

    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    for(unsigned int i = 0; i < key.size(); i++)
        if(key[i] < 'a' || key[i] > 'z')
            return;

    matrix[0][0] = key[0] - 'a';
    matrix[0][1] = key[1] - 'a';
    matrix[0][2] = key[2] - 'a';
    matrix[1][0] = key[3] - 'a';
    matrix[1][1] = key[4] - 'a';
    matrix[1][2] = key[5] - 'a';
    matrix[2][0] = key[6] - 'a';
    matrix[2][1] = key[7] - 'a';
    matrix[2][2] = key[8] - 'a';

    cout << "mat: " << endl
         << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << endl
         << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << endl
         << matrix[2][0] << " " << matrix[2][1] << " " << matrix[2][2] << endl;

    int det =
            + matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
            - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
            + matrix[0][2] * (matrix[1][0] * matrix[2][2] - matrix[1][1] * matrix[2][0]);

    det = -939;
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

    invmat[0][0] = (matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1]) * invdet;
    invmat[0][1] = (matrix[0][2]*matrix[2][1] - matrix[0][1]*matrix[2][2]) * invdet;
    invmat[0][2] = (matrix[0][1]*matrix[1][2] - matrix[0][2]*matrix[1][1]) * invdet;
    invmat[1][0] = (matrix[1][2]*matrix[2][0] - matrix[1][0]*matrix[2][2]) * invdet;
    invmat[1][1] = (matrix[0][0]*matrix[2][2] - matrix[0][2]*matrix[2][0]) * invdet;
    invmat[1][2] = (matrix[0][2]*matrix[1][0] - matrix[0][0]*matrix[1][2]) * invdet;
    invmat[2][0] = (matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]) * invdet;
    invmat[2][1] = (matrix[0][1]*matrix[2][0] - matrix[0][0]*matrix[2][1]) * invdet;
    invmat[2][2] = (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]) * invdet;

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            invmat[i][j] = invmat[i][j] % 26;
            if(invmat[i][j] < 0) invmat[i][j] += 26;
        }

    cout << "inv: " << endl
             << invmat[0][0] << " " << invmat[0][1] << " " << invmat[0][2] << endl
             << invmat[1][0] << " " << invmat[1][1] << " " << invmat[1][2] << endl
             << invmat[2][0] << " " << invmat[2][1] << " " << invmat[2][2] << endl;

    validKey = true;
}

bool HillCipher3::isValid()
{
    return validKey;
}

string HillCipher3::sanitizeText(string t)
{
    std::transform(t.begin(), t.end(), t.begin(), ::tolower);

    int counter = 0;
    for(unsigned int i = 0; i < t.size(); i++)
        if(t[i] >= 'a' && t[i] <= 'z')
            counter++;
    //if(counter % 2 == 1)
    //    t.append("x");

    return t;
}

string HillCipher3::encrypt(string plainText)
{
    plainText = sanitizeText(plainText);

    for(unsigned int i = 0; i < plainText.size() - 1; i += 3)
    {
        while(plainText[i] < 'a' || plainText[i] > 'z') i++;
        int c1 = i;

        while(plainText[i + 1] < 'a' || plainText[i + 1] > 'z') i++;
        int c2 = i + 1;

        while(plainText[i + 2] < 'a' || plainText[i + 2] > 'z') i++;
        int c3 = i + 2;

        char p1 = plainText[c1] - 'a';
        char p2 = plainText[c2] - 'a';
        char p3 = plainText[c3] - 'a';

        char q1 = (p1*matrix[0][0] + p2*matrix[1][0] + p3*matrix[2][0]) % 26;
        char q2 = (p1*matrix[0][1] + p2*matrix[1][1] + p3*matrix[2][1]) % 26;
        char q3 = (p1*matrix[0][2] + p2*matrix[1][2] + p3*matrix[2][2]) % 26;

        plainText[c1] = q1 + 'a';
        plainText[c2] = q2 + 'a';
        plainText[c3] = q3 + 'a';
    }

    return plainText;
}

string HillCipher3::decrypt(string cipherText)
{
    cipherText = sanitizeText(cipherText);

    for(unsigned int i = 0; i < cipherText.size() - 1; i += 3)
    {
        while(cipherText[i] < 'a' || cipherText[i] > 'z') i++;
        int c1 = i;

        while(cipherText[i + 1] < 'a' || cipherText[i + 1] > 'z') i++;
        int c2 = i + 1;

        while(cipherText[i + 2] < 'a' || cipherText[i + 2] > 'z') i++;
        int c3 = i + 2;

        char p1 = cipherText[c1] - 'a';
        char p2 = cipherText[c2] - 'a';
        char p3 = cipherText[c3] - 'a';

        char q1 = (p1*invmat[0][0] + p2*invmat[1][0] + p3*invmat[2][0]) % 26;
        char q2 = (p1*invmat[0][1] + p2*invmat[1][1] + p3*invmat[2][1]) % 26;
        char q3 = (p1*invmat[0][2] + p2*invmat[1][2] + p3*invmat[2][2]) % 26;

        cipherText[c1] = q1 + 'a';
        cipherText[c2] = q2 + 'a';
        cipherText[c3] = q3 + 'a';
    }
    return cipherText;
}

