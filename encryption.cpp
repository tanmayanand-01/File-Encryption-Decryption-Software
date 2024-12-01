#include "encryption.h"
#include <fstream>
#include <cctype>

using namespace std;

bool performCaeserCipher(string &content, bool encrypt){

    int shift;
    if(encrypt == true){
        shift = 13;
    }
    else{
        shift = -13;
    }

    for(char &ch: content){
        if(isalpha(ch)){
            char base = isupper(ch) ? 'A' : 'a';
            ch = static_cast<char> ((ch - base + shift + 26) % 26 + base);      //casercipher logic
        }
    }

    return true;
}


bool encryptFile(const string &filename, bool encrypt){
    //ifstream open the input file
    ifstream inFile(filename);      
    if(!inFile){
        return false;
    }  

    //read the content of the file
    string content((istreambuf_iterator<char>(inFile)), {});

    inFile.close();


    if(performCaeserCipher(content, encrypt)){
        //create an output file and write the modified content
        ofstream outFile(encrypt ? "encrypted_" + filename : "decrypted_" + filename);
        if(!outFile){
            return false;
        }

        outFile << content;

        outFile.close();
    }                      
    return true;
}