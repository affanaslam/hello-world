#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <vector> 
#include <map>

using namespace std;

int min (std::vector<int> v);

int minIndex (std::vector<int> v);

int max (std::vector<int> v);

int maxIndex (std::vector<int> v); 

void swapVector (unsigned int a, unsigned int b, std::vector<int> v);


int index (int val, std::vector<int> v);


int count (int val, std::vector<int> v);


std::vector<int> unique (std::vector<int> v);

std::vector<int> index_vec (std::vector<int> v, int val);

std::map<int, vector<int>  > locate( std::vector<int> v);

bool myfunction (int i,int j);

std::vector<int> sorting (std::vector<int> v);


#endif



