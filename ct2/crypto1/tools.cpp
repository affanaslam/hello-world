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




using namespace std;


string cleanString (string str){

 std::transform(str.begin(), str.end(), str.begin(), ::tolower);

 char* strStripped;

 strStripped = new char [str.length()];

 int j = 0; 
for(int i = 0; i < str.length(); i++)
{
    if (isalpha(str[i]))
    {
        strStripped[j] = str[i];
        j++;
    }
}
strStripped[j] = '\0';

return strStripped;
}

string intToStr(int num){

stringstream s;
s << num;
string str = s.str();
return str; 
}

int strToint(string num){

int result;
stringstream convert(num); 
if ( !(convert >> result) )
    result = 0;
  return result;

}


int countFrequency(string string1) {


  
  string1 = cleanString(string1); 
   int per = 0;
   int c = 0;
   int count[26] = {0};
   while ( string1[c] != '\0' )
   {  

      if ( string1[c] >= 'a' && string1[c] <= 'z' )
         count[string1[c]-'a']++;
      c++;

   
   }



   for ( c = 0 ; c < 26 ; c++ )
   {
      if( count[c] != 0 )

         
  
       std::cout << char(c + 'a') << " and freq: " << (count[c]/float(string1.length())) * 100 << "%" << std::endl;
   }

   return 0;
}



char encipher(char letter, int shift) {
  

 
 return (((letter-'a')+shift)%26)+'a';

}

char decipher(char letter, int shift) {
  

 
 return (( (((letter-'a')-shift)%26) + 26)%26 )+'a';

}


string DecToBin(int dec)
{
   string bin;
    while(dec!=0) {
      bin=(dec%2==0 ?"0":"1")+bin; 
      dec/=2;
   }
    return bin;
}

string bin (int x, int b){

  string val;
  int mask=1;
  for (int i=0; i<b; ++i){
    if ((mask&x) > 0)
    {
      val.append(1,'1');
    }
    else {
      val.append(1, '0');
    }
    mask = mask << 1;
  }
  reverse(val.begin(), val.end());
  return val;
}



string randomBits(int n){

   string a,b; 
   stringstream ss;
   int j, k;
   srand( (unsigned) time (NULL));
   for (int i =  0; i < n; i++){
   j = rand();
   a = DecToBin(j);
   ss << a;
   }
   b = intToStr(j)[0];
   k = strToint(b); 
   return ss.str().substr(k,n);
  
}




int stability (string binary, int nBit){
   
   std::map<std::string,int> mymap;
   int i;
   int c=0;  
   for (i=0; i<pow(2,nBit); i++) {
    string dec = bin(i,nBit); 
    mymap[dec] = 0;   
  }
for (int k=0; k < binary.length() - nBit + 1; k++) { 
  for (std::map<std::string,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    
{

  string sb = binary.substr(k,nBit);
      if (it -> first == sb) {
       mymap[it -> first]++;    
    }
    
}

}
for (std::map<std::string,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
cout << it->first << " => " << it->second << '\n';


cout << "-----------";
return 0;
 
}










