#include "crypto2.h"
#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <string> 
#include <bitset>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <limits> 
#include <algorithm>
#include <ctime>
// Other includes as necessary.

using namespace std;


void Tools::divmod(long a, long b, long* q, long* r) {


 *q  = a/b; //the functions takes the quotient
 *r  = a%b; // now the a%b calculates the remaninder using quotient remaindere theorem ; r = a - bq 

}




long Tools::gcd(long a, long b, long &x, long &y) {
   
int temp = 0;
   
   if(a < b) { // we want b to be smaller than a for our algorithm. Because there is no difference between g(b,a) and g(a,b), we can swap it
    
    temp = a; 
    a = b;
    b = temp;

   }

   if (b == 0){

    x = 1;
    y = 0;

    return a;
  }

    long x1 = 0;
    long y1 = 0;
    long d = 0; 
    x1, y1, d = gcd(b, a%b, x1,y1); // here we are using euclid extension algorithm : gcd = ax + by; 
    x= y1;
    y = x1 - (a/b) * y1;
    return d;
}



bool Tools::primality1(unsigned long n) {
  
  for (int k=2; k<n-1; k++){ 
    if (n % k)
      return false; //he we are using a lengthy algorithm which will run from 2 to n-1 and try to divide n; if it doesn't divide, it is prime 
  }

  return true;
}

long Tools::fastModularExponent(long a, long b, long c) {
  
  if (b == 0)
  return 1;
  
  long z = 0;
  long p,k = 0;
  z = fastModularExponent(a,floor(b/2),c); //here we are using fast algorithm to calculate large mods 2^212232 mod 4 fastly by dividing it into 2
  if (b%2 == 0){

    p = pow(z,2);

    return p%c;
  }
  else {
    k = a*pow(z,2);
    return k%c;
  }
}  


bool Tools::primality2(unsigned long n, int k) {

  if (n==1){
    return false;
  }
  
for (int i=1; i<k; i++){
  if (fastModularExponent(i,n-1,n) != 1){ //primarlity two using fermat's theroem a^p - 1 is congruent to 1 mod n; in order 
  //to minimize the uncertainty of the occurence of Carmicheal numbers, we using k numbers as 1^p-1 , 2^p-1 etc. 
    return false;
  }
  
    
  
}

return true;

}


string Tools::intToStr(int num){

stringstream s;
s << num;
string str = s.str(); // a simple function to convert int to string. 
return str; 
}

int Tools::strToint(string num){

int result;
stringstream convert(num); 
if ( !(convert >> result) ) // a simple function to convert string to int
    result = 0;
  return result;

}

int Tools::random(int n, int l, int s) {

int d;
int l2 = l;


string middle;  
/*
 mathematics, the middle-square method is a method of generating ‘pseudorandom’ numbers.To generate a sequence of 4-digit pseudorandom numbers, a 4-digit starting value is created and squared, producing an 8-digit number (if the result is less than 8 digits, leading zeroes are added to compensate). The middle 4 digits of the result would 
 be the next number in the sequence, and returned as the result. This process is then repeated to generate more numbers.
the loop will run upto n numbers and ultimately we return a random of number of length at the nth position 

*/

l = l/2;

for (int i=0; i < n; i++){
    d = s*s;
 
    middle = intToStr(d);

    middle = middle.substr((middle.size()/2 - 1), l2);

    s = strToint(middle);
}

 return s;

}



unsigned long long Tools::convert(string& bits)


{

  //a function to convert long binary string to its 'long' decimal representation. It will be used in stringToNumbers 
  //when we will convert the stringToNumbers to its binary representation and then again to decimal 
    if (bits.length() > (size_t)numeric_limits<unsigned long long>::digits)
        return 0;

    unsigned long long sum = 0;
    unsigned long long shift = 1;
    for (string::reverse_iterator it(bits.rbegin()), end(bits.rend());
         it < end; ++it)
    {
        if (*it == '1') sum += shift;
        shift = (shift << 1);
    }

    return sum;
}

unsigned long long Tools::stringToNumbers(std::string text) {

  string binary;

  //using bitset we are looping through the string and concantinating its binary ascii; later we concatenate 

  unsigned long long r= 0;
  for (int i = 0; i < text.length(); i++){
    bitset<8> bit = bitset<8>(text[i]);
    string mystring = bit.to_string<char, string::traits_type,string::allocator_type>();
    binary += mystring;
  }
   
  //r = convert1(binary); // by using our convert we return the decimal representation of binary 

  return r;
}

bool Tools::prime(int n) {
  bool k = true;
  if (n != 2){
    for (int i = 2; i < (int) sqrt(n) + 1; i++){ // This prime is more optimized because it just loops through sqrt(n)
      if (n % i == 0){
        k = false;
        break;
      }
    }
  }
  return k;
}

unsigned long long Tools::gen_prime(int l){
  srand (time(NULL));
  int t = random(100,l,rand()%100); //in this function we are generating a prime; it generates a number and checks 
  //if it is prime; if it is not, increment t++ and check again. 

  do{
    t++;
  } while (!prime(t));

  return t;
}


void Tools::_generateKeys(int l, unsigned long& n, unsigned long& e, unsigned long& d) {

// I followed  With examples: http://doctrina.org/How-RSA-Works-With-Examples.html step by step setup
/*
generate two primes 
calculate the produce of p and q; 
then calculate a phi (euler toint) by (p - 1)*(q -1)

calculate e such that it is coprime to e;

and d is the multiciplicative inverse of e.


*/

unsigned long long  p,q;
unsigned long phi;

p = gen_prime(l);
cout << "p: " << p <<endl;
q = gen_prime(l);
cout << "q: " << q << endl;

n = p * q;

cout <<"n: " << n <<endl;

phi = (p - 1) * (q - 1);

 e = rand()%(phi-2) + 2;

 cout << "e: " << e <<endl;
  


 long y = 0; 
 long  x = 0;
 long g = 0;
 
  while ( gcd(phi, e, y, x) != 1){
    e = rand()%(phi-2) + 2;
  }
  d = x;

}


long Tools::encrypt(long m,unsigned long n, unsigned long e) {
  // 
  // Your code here.
  // 
  return fastModularExponent(m,e,n);
}

long Tools::decrypt(unsigned long c, unsigned long n, long d) {
  // 
  // Your code here.
  // 
 return fastModularExponent(c,d,n);
}

// ----------------------------------------------------------------------

RSA::RSA() {
  Tools _tools;  // member variable - to be used in other methods of this class.
  // 
  // Your code here - use _tools to generate keys and store in member variables.
  // 

  unsigned long n,e,d,enc;

 

  int l = 5;

  unsigned long long  plainText_int = _tools.stringToNumbers(plainText);

  _tools._generateKeys(l,n,e,d); 


  return 0;
}

std::string RSA::encrypt(std::string plainText) {

  string cipher;

   enc = _tools.encrypt(plainText_int, e,n);

   cipher = _tools.intToStr(enc);
  // 
  // Your code here.
  // 
  return enc;
}

std::string RSA::decrypt(std::string cipherText) {

  string decipher;

  long dec; 

  dec = _tools.decrypt(intToStr(cipherText), d,n);
  
  decipher = _tools.strToint(dec);

  return decipher;
}



