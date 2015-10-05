#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "fileio.h"


using namespace std;

int strToint(string num){

int result;
stringstream convert(num); 
if ( !(convert >> result) )
    result = 0;
  return result;

}


int readHeader (string fileName){
  
  ifstream in (fileName.c_str());
  
string format, f, useless,line3, gray, width, height;
in >> format; 
f = format;
if (format == "P2") {
 cout << "File format: " << "PGM" << endl;
}
else if(format == "P1") { 
 cout << "File Format:"	<< "PBM" << endl;
}
 getline(in, format);
 getline(in, useless);
 in >> width; 
 cout << "Width: " << width << endl;
 in >> height;
 cout << "Height: " << height << endl;
 getline(in, line3);
 in >> gray;
 if (f == "P1"){
 	cout<< "Gray levels: 2" ;
 }
 else cout << "Gray levels:" << gray;

}


int trim(string fileName){

	string testline, line1,line2,line3,gray,height,width;
    int w,h;   
 
 

    ifstream Test ("logo.pgm");
    ofstream out ("trim.pgm");

    getline(Test, line1);
    getline(Test, line2);

    Test >> width; 
    Test >> height;

    w = strToint(width);
    h = strToint(height);

    getline(Test, line3);
    
    Test >> gray; 

    cout << gray;  

    string word[h][w];
    

    if (!Test)
    {
        cout << "There was an error opening the file.\n";
        return 0;
    }
    //store words in array
    int x=0,y=0;
    while( Test>>testline )
    {
        word[y][x]=testline;
        x++;
        if (testline=="")
        y++;
    }

      out << line1 <<endl; 
      out << line2 <<endl;
      out << w-2 << " " << h-2 <<endl;
      out << gray <<endl;
    //output whole array with array position numbers for each entry
    
        for (int y=1;y<h-1;y++)
        {
            for (int x=1;x<w-1;x++){
              out << word[y][x] << endl;
          }
        }
  
    return 0;
}







int main (){

   trim("logo.pgm");
   return 0;

}

