#ifndef TOOLS_H
#define TOOLS_H
#include <string>


using namespace std; 

char encipher(char letter, int shift);

char decipher(char letter, int shift);

int caeserCipher(string inFile, string outFile, int shift);

int caeserDecipher(string inFile, string outFile, int shift);

int polyCipher(string inFile, string outFile, string shift);

int polyDecipher(string inFile, string outFile, string shift); 



#endif