#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

void code();
void decode();
int openFile(std::string name, std::string& data);
std::string vigenereCode(std::string message, std::string key);
std::string vigenereDecode(std::string message, std::string key);

bool alphabetOnly = false;

int main()
{
    unsigned int choice = 1;
    std::string actualMode;

    while(choice > 0 && choice <= 3) {
        if(alphabetOnly)    { actualMode = "Alphabet Only"; }
        else                { actualMode = "ASCII"; }
        std::cout << "Que voulez vous faire ?" << std::endl
                  << "1) Coder un message" << std::endl
                  << "2) Decoder un message" << std::endl
                  << "3) Toggle cypher mode (alphabet only or ascii). Actual mode: " + actualMode << std::endl
                  << "Autre) Quitter" << std::endl
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
    std::cout << std::endl << "Que voulez-vous faire ?" << std::endl
                           << "1) Ecrire le message ici" << std::endl
                           << "2) Coder un fichier texte";

    while(choice < 1 || choice > 2) {
        std::cout << std::endl << "> ";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string message;

    if(choice == 1) {
        std::cout << std::endl << "Votre message > ";
        getline(std::cin, message);
    }
    else if(choice == 2) {
        std::string name;
        std::cout << std::endl << "Veuillez entrer le nom du fichier > ";
        getline(std::cin, name);
        if(openFile(name, message) == 1)    { std::cout << "Probleme, abandon"; return; }
    }

    std::string key;

    std::cout << "Choisissez une cle > ";
    getline(std::cin, key);

    if(key.size() == 0)     { std::cout << "Cl� de longueur 0, abandon"; return; }

    std::string result = vigenereCode(message, key);

    std::cout << "Result : " << result;
}

void decode() {
    std::string message;
    std::string key;

    std::cout << "Votre message > ";
    getline(std::cin, message);

    std::cout << "Votre cle > ";
    getline(std::cin, key);

    if(key.size() == 0)     { std::cout << "Cl� de longueur 0, abandon"; return; }

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
            codedChar = (placeOfChar + key[counterKey])%53;
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
            decodedChar = (placeOfChar - alphabet[key[counterKey]]);
            std::cout<< "1: " << (int)decodedChar << std::endl;
            if(decodedChar < 0)   { decodedChar+=52; }
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
            data += '\n';
        }
        return 0;
    }
}
