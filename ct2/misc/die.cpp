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



using namespace std;

vector<string> getTeam (){
std::vector<string> v;
string name; 
cout << "Enter the name of the team: ";
cin >> name; 
v.push_back(name);

for (int i = 0; i < 11; i++){
	cout << "Enter the name of the player:";
	cin >> name;
	v.push_back(name);
}
return v;
}


void playerInnings (string pName, int &tScore) {


//srand (seed);


int score = 0; 
int total = 0; 

cout << pName << ": "; 
while (score != 5){
	score = rand()%6 + 1;
   if (score == 5) 
    cout << "OUT" << "..." ;
    else{
    cout << score << ",";	
    total = total + score;
    }
}
cout << "total score: " << total << endl;
tScore = total;
}

void teamScore (vector<string> getTeam, int &finalscore){

	std::vector<string> v; //teamlist 
    v = getTeam; //copying getTeam to v; 
    int tScore = 0;
    int t = 0;
    

    cout << v[0] << endl;
  
    for (int i = 1; i < v.size(); i++) {
    	playerInnings (v[i], tScore);
    	t = t + tScore; 
    } 

    cout << "total score: " << t;

    finalscore = t;

}

void dieCricket (){



int score_a = 0;
int score_b = 0;
std::vector<string> team_a,team_b;

team_a = getTeam();
team_b = getTeam();

teamScore(team_a, score_a);
teamScore(team_b, score_b);

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

struct node {
  int x;
  node *next;
};




int main (){

//srand(time(NULL));	
	/*for (int i = 0; i < n.size(); i++){
		cout << n[i] << endl;
	}
*/
	//playerInnings("affan", total);
	//dieCricket();
	
}