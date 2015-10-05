#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include "crypto1.h"

using namespace std;


char encipher(char letter, int shift) {
  
 //unlike Khan Academy , the shift starts with zero  

 
 return (((letter-'a')+shift)%26)+'a';

}

char decipher(char letter, int shift) {
  
 //unlike Khan Academy , the decipher starts with zero  
 
 return (((((letter-'a')-shift)%26) + 26)%26 )+'a';

} 





int caeserCipher(string inFile, string outFile, int shift){


	ifstream Test (inFile.c_str());
	ofstream out (outFile.c_str());
	char letter, enc; 
    while(Test){
	  Test >> noskipws >> letter;
	  cout << letter;
	  letter = tolower(letter); 
      if (isspace(letter)) {
        out << char(32); 
	  }	



       else if (isalpha(letter))

     {  
     	enc = encipher(letter, shift);
     	out << enc;
     }  

	}
   Test.close();
 return 0;
}

int caeserDecipher(string inFile, string outFile, int shift){



	ifstream Test (inFile.c_str());
	ofstream out (outFile.c_str());
	char letter, enc; 
    while(Test){
	  Test >> noskipws >> letter;
	  cout << letter;
	  letter = tolower(letter); 
      if (isspace(letter)) {
        out << char(32); 
	  }	

       else if (isalpha(letter))

     {  
     	enc = decipher(letter, shift);
     	out << enc;
     }  

	}
   Test.close();
 return 0;
}

int polyCipher(string inFile, string outFile, string shift){

  ifstream Test (inFile.c_str());
  ofstream out (outFile.c_str());
  
  int c = 0; 
  int j = 0; 
  
  char letter, enc; 
    while(Test){

     
      
  for (int i=0; i < shift.length() ; i++) {
    Test >> noskipws >> letter;
    letter = tolower(letter); 
    std::transform(shift.begin(), shift.end(), shift.begin(), ::tolower);
    
    if (isspace(letter)) {
        out << char(32); 
        i--;
    } 
       else if (isalpha(letter))

     {    
     
      enc = encipher(letter, int(char(shift[i])) - 97);
      cout << letter << " is mapped to " << shift[i] << " is encyrpted to: " << enc << endl; 
      out << enc;

      
      }
      
      if(!Test) {break;}

     }
    

  }

 Test.close();
 return 0;
}

  


int polyDecipher(string inFile, string outFile, string shift){

  ifstream Test (inFile.c_str());
  ofstream out (outFile.c_str());
  
  int c = 0; 
  int j = 0; 
  
  char letter, enc; 
    while(Test){

     
      
  for (int i=0; i < shift.length() ; i++) {
    Test >> noskipws >> letter;
    letter = tolower(letter); 
    std::transform(shift.begin(), shift.end(), shift.begin(), ::tolower);
    
    if (isspace(letter)) {
        out << char(32); 
        i--;
    } 
       else if (isalpha(letter))

     {    
     
      enc = decipher(letter, int(char(shift[i])) - 97);
      cout << letter << " is mapped to " << shift[i] << " is encyrpted to: " << enc << endl; 
      out << enc;

      
      }
      
      if(!Test) {break;}

     }

   j++;     

  }

cout << c << " " << j;
 Test.close();
 return 0;
}

