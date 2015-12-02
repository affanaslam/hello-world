#ifndef CRICKET_H
#define CRICKET_H
#include <string>
#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <vector> 
#include <algorithm>    // std::swap
#include <map>


using namespace std;

vector<string> getTeam ();

void batPlayer (string pName, int &tScore);

void playTeam (vector<string> getTeam, int &finalscore);

void match ();



#endif 