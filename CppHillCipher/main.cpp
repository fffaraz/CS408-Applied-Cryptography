// Faraz Fallahi
// CS408 Lab2+Faraz

#include <iostream>
#include <string>
#include <fstream>

#include "hillcipher.h"
#include "hillcipher3.h"

using namespace std;

void usage()
{
    cout << "Usage: hillcipher -e/-d key file" << endl;
}

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        usage();
        return 1;
    }

    string enc_dec = argv[1];
    string key = argv[2];
    string file = argv[3];

    if(enc_dec != "-e" && enc_dec != "-d")
    {
        usage();
        return 2;
    }

    ifstream input(file);
    if(!input.is_open())
    {
        cout << "File not found." << endl;
        return 3;
    }

    //HillCipher hc(key);
    HillCipher3 hc(key);

    if(!hc.isValid())
    {
        cout << "Invalid key." << endl;
        return 4;
    }

    string buffer;
    string output_str;
    string output_file;

    if(enc_dec == "-e")
    {
        cout << "Encrypting \"" << file << "\" using the key \"" << key << "\" ..." << endl << endl;
        output_file = file + ".enc";
        char buf[1024];
        input.getline(buf, 1024);
        cout  << buf;
        output_str += hc.encrypt(buf);
    }

    if(enc_dec == "-d")
    {
        cout << "Decrypting \"" << file << "\" using the key \"" << key << "\" ..." << endl << endl;
        output_file = file + ".dec";
        //input >> buffer;
        //cout  << buffer;
        char buf[1024];
        input.getline(buf, 1024);
        cout  << buf;
        output_str += hc.decrypt(buf);
    }

    input.close();

    ofstream output(output_file);
    output << output_str;
    cout << endl << output_str << endl << endl;
    output.flush();
    output.close();

    cout << "Done." << endl;
    return 0;
}
