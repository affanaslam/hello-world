// reading a text file
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include "cricket.h"



using namespace std;

vector<string> getTeam (){ //the function returns a vector 
std::vector<string> v;
string name; 
cout << "Enter the name of the team: ";
cin >> name; 
v.push_back(name); //push back simply appends the name to the vector. It is the name of the team

for (int i = 0; i < 11; i++){
	cout << "Enter the name of the player:"; //Likewise appends all the team players one by one in the vector  
	cin >> name;
	v.push_back(name);
}
return v;
}

void batPlayer (string pName, int &tScore) {  //tScore is the pointer pointing to the team total score which we need for the later functions


//srand (seed); the seed is supposed to be used in main. 


int score = 0; 
int total = 0; 

cout << pName << ": "; 
while (score != 5){
	score = rand()%6 + 1; //we are using rand() for rolling the dice in order to have random values. By +1 we are avoiding occurence of '0'. The value cannot exceed 6
   if (score == 5) 
    cout << "OUT" << "..." ;
    else{
    cout << score << ",";	
    total = total + score; //summing up the total score 
    }
}
cout << "total score: " << total << endl; //output the total 
tScore = total; //send it to tScore. 
}

void playTeam (vector<string> getTeam, int &finalscore){

	std::vector<string> v; //teamlist 
    v = getTeam; //copying getTeam to v; 
    int tScore = 0;
    int t = 0;
    

    cout << v[0] << endl;
  
    for (int i = 1; i < v.size(); i++) {
    	batPlayer (v[i], tScore);
    	t = t + tScore; 
    } 

    cout << "total score: " << t;

    finalscore = t;

}

void match (){  //dieCricket()



int score_a = 0;
int score_b = 0;
std::vector<string> team_a,team_b;

team_a = getTeam();
team_b = getTeam();

playTeam(team_a, score_a);
playTeam(team_b, score_b);

if (score_a > score_b) {
	cout << endl << team_a[0] << " wins!";
}
else if (score_a < score_b) {
	cout << endl << team_b[0] << " wins!";
}

else  {
	cout << endl << "TIE!";
}


}


