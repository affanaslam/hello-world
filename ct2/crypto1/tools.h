#ifndef TOOLS_H
#define TOOLS_H
#include <string>

using namespace std;

string cleanString (string str);

int countFrequency (string str);

char encipher(char letter, int shift);

char decipher(char letter, int shift);

char randomBits(int number);

stability (string binary, int nBit);

string bin (int x, int b);

string DecToBin(int n);

string intToStr(int num);


#endif 