#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <vector> 
#include <algorithm>    // std::swap
#include <map>
#include "vectorOps.h"

using namespace std;


// [1,2,0,4,5]
int min (std::vector<int> v) {

	//min returns the smallest number in the vector
 int minNumb = v[0];

 for (int i = 1; i < v.size(); i++){
 	
 	if (minNumb > v[i]){ //the algorithm is straight forward; if minNumber that initially is the first index. It is not the most optimal sorting

        minNumb = v[i];
 	}
 }

 return minNumb;
}

int minIndex (std::vector<int> v) { //minimum index algo is of the same nature. It just returns the index of the minimum number 
 int minNumb = v[0];
 int indexMin = 0;

 for (int i = 1; i < v.size(); i++){
 	
 	if (minNumb > v[i]){

        minNumb = v[i];

        indexMin = i; //here it saves the index of the minimum. 
 	}
 }

 return indexMin;
}

int max (std::vector<int> v) {
 int maxNumb = v[0]; // max is same as minimum however the only difference is in the loop 

 for (int i = 1; i < v.size(); i++){
 	
 	if (maxNumb < v[i]){ //it makes v[i] as maximum number if it is greater than maxNumber, which is changing within the loop but initially was 
 	      maxNumb = v[i];//the first index 
 	}
 }
 return maxNumb;
}

int maxIndex (std::vector<int> v) { //returns the index of the maximum element in the integer vector 
 int maxNumb = v[0];
 int indexMax = 0;

 for (int i = 1; i < v.size(); i++){
 	
 	if (maxNumb > v[i]){

        maxNumb = v[i];

        indexMax = i;
 	}
 }

 return indexMax;
}


void swapVector (unsigned int a, unsigned int b, std::vector<int> v) {
	int temp = 0;
 if (a <= v.size() && b <= v.size()) {
 	  
     swap(v[a],v[b]); //algorithm has a built-in function swap. using it to swap the elements. 
      
 }
 else {
    cout << "Error... Index out of range";
 }
}

//these functions are as definied in the manual. quite self-explanatory 
int index (int val, std::vector<int> v) {

	for (int j = 0; j < v.size(); j++){
		if (v[j] == val){
			return j;
		}
	}

	return -1;

}


int count (int val, std::vector<int> v){
	int c = 0;
	for (int i = 0; i < v.size(); i++){
		if (v[i] == val){
			c++;     
		}
	}

	return c;
}


std::vector<int> unique (std::vector<int> v){
	std::vector<int> u;
	u.push_back(v[0]);

	
	for (int i = 1; i < v.size(); ++i)
	{
	   int item = v[i];
	   if ( std::find(u.begin(), u.end(), item) == u.end() ) // if not present in u
	   u.push_back(item); // the push it

}

return u;
}


std::vector<int> index_vec (std::vector<int> v, int val) //it is my own function . it returns the vector u The value for each key is 3
//a vector containing the indexes in the original vector where the key occurs
{
	std::vector<int> u;
	for (int i = 0; i < v.size() ; i++) {
		if (v[i] == val) 
			u.push_back(i);
	}

	return u;
}

std::map<int, vector<int>  > locate( std::vector<int> v)

{
std::map<int, std::vector<int>  > map;	
std::vector<int> u;
u = unique(v); // vector of unique values
    for (int i = 0; i < u.size(); ++i)
    {
    	map[u[i]] = index_vec(v, u[i]);

    	
    }   
 return map;   
}

bool myfunction (int i,int j) { return (i<j); } //my function simply is that if i < j return the one lesser than the other. 

std::vector<int> sorting (std::vector<int> v){ //because sort already is a function; we are going for sorting.

	sort (v.begin(), v.end(), myfunction);

	return v;

}

