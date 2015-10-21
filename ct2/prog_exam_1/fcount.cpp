#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include <math.h>
#include <map>
 #include "fcount.h"

using namespace std;

string capitalize (string text){
	
//explanation : using string transform function that takes each char and make it upper case 	
	 std::transform(text.begin(), text.end(), text.begin(), ::toupper);	 
	 
	 return text;
}


int countLetters(string text) {

//explanation : string 1 capitalize the text and outputs it; we are only considering upprcase 
  string string1;
  string1 = capitalize(text); 
   int per = 0;
   int c = 0;
   int count[26] = {0};
   while ( string1[c] != '\0' )
   {  
     
      if ( string1[c] >= 'A' && string1[c] <= 'Z' )
         count[string1[c]-'A']++;
      c++;

   
   }

   for ( c = 0 ; c < 26 ; c++ )
   {
      if( count[c] != 0 )

         
  
       std::cout << char(c + 'A') << " and freq: " << count[c] << std::endl;
   }

   return 0;
}


int count (string text, string word){
	 
	 
	//count takes a string , and counts its occurences by using text.find() 

	int index = text.find(word);
	int count = 0;
	
	while (index != -1){
	 if ((text[0] || text[index-1] == char(32))	&&  ( text[index+word.length()] == char(32)  || index+word.length() == text.length() ) )
	  {
	    index = text.find(word, index+1);
		count ++;
	  }
	  
	  	
	}
	
	return count;
	

	
	
}

 int countWords (string text){
	
	stringstream ss; 
	map<string,int> mymap; 
	ss >> text;
  
     
	while (ss >> text) {
		mymap[text]++; 
		
	}
	
  for (std::map<std::string,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it) {
  	
  	cout << "hello";
  
   cout << it->first << " => " << it->second << '\n';
}

}


int main () {
   
    //cout << capitalize("hello my name is affan 123");
    
  
   
  countWords("my name affan isaffan affan");

	return 0;
}
