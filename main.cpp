#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

void code();
int openFile(std::string name, std::string& data);
std::string vigenereCode(std::string message, std::string key);


int main()
{
    unsigned int choice = 1;

    while(choice > 0 && choice < 2) {
        std::cout << "Que voulez vous faire ?" << std::endl
                  << "1) Coder un message" << std::endl
                  << "2) Decoder un message" << std::endl
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
                //decode();
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

    if(key.size() == 0)     { std::cout << "Clé de longueur 0, abandon"; return; }

    std::string result = vigenereCode(message, key);

    std::cout << "Result : " << result;
}

void decode()

std::string vigenereCode(std::string message, std::string key) {
    unsigned int counterKey = 0, sizeOfKey = key.size();
    char codedChar;
    std::string codedString;
    for(unsigned int i = 0; i < message.size(); i++) {
        codedChar = (message[i] + key[counterKey])%256;
        codedString += codedChar;
        ++counterKey%=sizeOfKey;
    }
    return codedString;
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
