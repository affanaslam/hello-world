#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <vector> 
#include <algorithm>    // std::swap
#include <map>

using namespace std;


// [1,2,0,4,5]
int min (std::vector<int> v) {
 int minNumb = v[0];

 for (int i = 1; i < v.size(); i++){
 	
 	if (minNumb > v[i]){

        minNumb = v[i];
 	}
 }

 return minNumb;
}

int minIndex (std::vector<int> v) {
 int minNumb = v[0];
 int indexMin = 0;

 for (int i = 1; i < v.size(); i++){
 	
 	if (minNumb > v[i]){

        minNumb = v[i];

        indexMin = i;
 	}
 }

 return indexMin;
}

int max (std::vector<int> v) {
 int maxNumb = v[0];

 for (int i = 1; i < v.size(); i++){
 	
 	if (maxNumb < v[i]){
 	      maxNumb = v[i];
 	}
 }
 return maxNumb;
}

int maxIndex (std::vector<int> v) {
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
 	  
     swap(v[a],v[b]);
      
 }
 else {
    cout << "Error... Index out of range";
 }
}

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


std::vector<int> index_vec (std::vector<int> v, int val)
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

bool myfunction (int i,int j) { return (i<j); }

std::vector<int> sorting (std::vector<int> v){

	sort (v.begin(), v.end(), myfunction);

	return v;

}

int main(){

	
static const int arr[] = {11,12,3,11};
vector<int> v (arr, arr + sizeof(arr) / sizeof(arr[0]) );



for (int i =0 ; i < sorting(v).size() ; ++i)
	cout << sorting(v)[i] << endl;
   //cout << "the max number is: " << max(v);
//swapVector(1,2,v);



/*for (int i = 0; i < v.size(); i++){
	cout << v[i] << ",";
} 	
*/
//cout << count (11,v);
/*u = index_vec(v, 12);
for (int i = 0; i < u.size(); i++){
	cout << u[i] << ",";
} */

/* std::map<int,vector<int>  >::iterator it = locate(v).begin();

for (it=locate(v).begin(); it!=locate(v).end(); ++it)
    std::cout << it->first << '\n';
*/



}