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
#include "ntheory.h";
 
using namespace std; 
 
 
void divmod (int a, int b, int &q, int &r){
	q = a/b; 
	r = a%b;

}
 	

int gcd (int a, int b){
	
	if (a==0) {
		return a; 
	}
	else if (b==0){
		return b;
	}
	
	else {
		int q,r;
		divmod (a,b,q,r);
		gcd(b,r);
		
		if (r != 0){
			cout << r << endl;
		}
	}
	
	

	return 0;
}

int sieve (int n, *primes){
	
	primes = new int [];
	
	for (int i=0; i<primes; i++){
		primes[i] = 1; //1 represents masking
	}
	
	for (int i=2; i<sqrt(n); i++) {
		
		for (int j = 0; j < n; i=i+h){
			primes[i] = 0;
		}
		
	}


	
 return *primes;	
}



