#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

void code();
void decode();
int openFile(std::string name, std::string& data);
std::string vigenereCode(std::string message, std::string key);
std::string vigenereDecode(std::string message, std::string key);
int writeToResultTxt(std::string& str);

bool alphabetOnly = true;

int main()
{
    unsigned int choice = 1;
    std::string actualMode;

    while(choice > 0 && choice <= 3) {
        actualMode = (alphabetOnly) ? "Alphabet Only" : "ASCII";
        std::cout << "What do you want to do?" << std::endl
                  << "1) Encrypt a message" << std::endl
                  << "2) Decrypt a message" << std::endl
                  << "3) Toggle cypher mode (alphabet only or ascii). Actual mode: " + actualMode << std::endl
                  << "Other) Quit" << std::endl
                  << "> ";

        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(choice) {
            case 1:
                code();
                break;
            case 2:
                decode();
                break;
            case 3:
                alphabetOnly = !alphabetOnly;
                break;
        }

        std::cout << std::endl << std::endl;
    }

    return 0;
}

void code() {
    unsigned int choice = 0;
    std::cout << std::endl << "What do you want to do?" << std::endl
                           << "1) Write the message in standard input" << std::endl
                           << "2) Encrypt a text file";

    while(choice < 1 || choice > 2) {
        std::cout << std::endl << "> ";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string message;

    if(choice == 1) {
        std::cout << std::endl << "Your message > ";
        getline(std::cin, message);
    }
    else if(choice == 2) {
        std::string name;
        std::cout << std::endl << "Please enter the name of the file > ";
        getline(std::cin, name);
        if(openFile(name, message) == 1)    { std::cout << "Error, quitting"; return; }
    }

    std::string key;

    std::cout << "Choose a key > ";
    getline(std::cin, key);

    if(key.size() == 0)     { std::cout << "Key's length is 0, quitting"; return; }

    std::string result = vigenereCode(message, key);

    std::cout << "Result : " << result;
}

void decode() {
    std::string message;
    std::string key;

    std::cout << "Your message > ";
    getline(std::cin, message);

    std::cout << "Your key > ";
    getline(std::cin, key);

    if(key.size() == 0)     { std::cout << "Key's length is 0, quitting"; return; }

    std::string result = vigenereDecode(message, key);

    std::cout << "Result : " << result;
}

std::string vigenereCode(std::string message, std::string key) {
    unsigned int counterKey = 0, sizeOfKey = key.size();
    char codedChar;
    std::string codedString;
    unsigned int placeOfChar;
    if(alphabetOnly) {
        std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
        for(unsigned int i = 0; i < message.size(); i++) {
            if((placeOfChar = alphabet.find(message[i])) == std::string::npos)  { return "Error, characters are not part of the following string : " + alphabet; }
            codedChar = (placeOfChar + key[counterKey]%53)%53;
            codedString += alphabet[codedChar];
            ++counterKey%=sizeOfKey;
        }
    } else {
        for(unsigned int i = 0; i < message.size(); i++) {
            codedChar = (message[i] + key[counterKey])%256;
            codedString += codedChar;
            ++counterKey%=sizeOfKey;
        }
    }
    writeToResultTxt(codedString);
    return codedString;
}

std::string vigenereDecode(std::string message, std::string key) {
    unsigned int counterKey = 0, sizeOfKey = key.size();
    char decodedChar;
    std::string decodedString;
    unsigned int placeOfChar;
    if(alphabetOnly) {
        std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
        for(unsigned int i = 0; i < message.size(); i++) {
            if((placeOfChar = alphabet.find(message[i])) == std::string::npos)  { return "Error, characters are not part of the following string : " + alphabet; }
            decodedChar = (placeOfChar - (key[counterKey]%53));
            std::cout<< "1: " << (int)decodedChar << std::endl;
            if(decodedChar < 0)   { decodedChar+=53; }
            std::cout<< "2: " << (int)decodedChar << std::endl;
            decodedString += alphabet[decodedChar];
            ++counterKey%=sizeOfKey;
        }
    } else {
        for(unsigned int i = 0; i < message.size(); i++) {
            decodedChar = (message[i] - key[counterKey]);
            if(decodedChar < 0)   { decodedChar+=256; }
            decodedString += decodedChar;
            ++counterKey%=sizeOfKey;
        }
    }
    writeToResultTxt(decodedString);
    return decodedString;
}

///**** OpenFile ****///
/** Store the content of a file in a string **/
int openFile(std::string name, std::string& data) {
    std::ifstream file{name};
    std::string temp;

    if(!file)   { std::cout << "Error, file cannot be opened" << std::endl; return 1; }

    /// We put all the text of the file in the string and add a '\0' char at the end
    else {
        while(getline(file, temp)) {
            data += temp;
        }
        return 0;
    }
}

/// Write the string in the file result.txt ///
int writeToResultTxt(std::string& str) {
    std::ofstream ofs;
    ofs.open("result.txt", std::ofstream::out | std::ofstream::trunc);
    ofs << str;
    ofs.close();
    return 0;
}
