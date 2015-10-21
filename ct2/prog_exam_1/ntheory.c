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
 #include "ntheory.h"
 
 
void divmod (int a, int b, int &q, int &r){
	q = b/a; 
	r = a%b;
}
 	

void gcd (int a, int b){
	
	if (a==0) {
		return 
	}
	else if (b==0){
		return;
	}
	
	else {
		int q,r;
		divmod (a,b,q,r);
		return gcd(b,r);
		
		if (r != 0){
			cout << r << endl;
		}
	}
	
	
	
	
}
