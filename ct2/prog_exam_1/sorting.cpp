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
#include "sorting.h"
 
using namespace std; 

int findSmallerNeighbour(int arr[], int i){
	
	
	
	for (int j = i - 1; j >= 0; j--){
		if (arr[j] < arr[i]) {
			
			return j + 1;
		}
		
	  
	}
	
   return 0;		
}


int* reorder (int arr[], int i, int j ){
	
	int temp = arr[j];
	for (int k = j - i; k > i; k--){
		arr[k]=arr[k-1];
	}
	
	arr[i] = temp;
	return arr;
}

int* insertionSort (int arr[], int size){
	int j = 0;
	for (int i = 1; i < size; i++){
		j = findSmallerNeighbour(arr, i);
		reorder (arr, j, i);
	}
	return arr;
}

int * hsort (int arr[], int size, int h){
	
	int S[size/h]; 
	for (int i=0; i < size/h; i++){
		S[i] = arr[h*i];
	}
	
	int *array = insertionSort(S, size/h);
	
	for (int k = 0; k < size; k=k+h){
		
		arr[k] = array[k];
		
	}
	
return arr; 

}


int * shellsort(int arr[], int size){
	
	int gaps[8] = {701,301,132,57,23,10,4,1};
	
	for (int gap=0; gap < 8; gap++){
		hsort(arr, size, gap);
	}
	
	return arr;
	
}



