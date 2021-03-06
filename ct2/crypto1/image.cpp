#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "image.h"
#include <cmath>


using namespace std;

int strToint(string num){

int result;
stringstream convert(num); 
if ( !(convert >> result) )
    result = 0;
  return result;

}

int halve(string fileName){

    string testline, line1,line2,line3,gray,height,width;
    int w,h;   
 
 

    ifstream Test ("logo.pgm");
    ofstream out ("halve.pgm");

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
      out << w/2 << " " << h/2 <<endl;
      out << gray <<endl;
    //output whole array with array position numbers for each entry
    
        for (int y=1;y<h-1;y=y+2)
        {
            for (int x=1;x<w-1;x=x+2){
              out << word[y][x] << endl;
          }
        }
  
    return 0;
}

int threshold(string fileName, int t_val = 150){

	string testline, line1,line2,line3,gray,height,width;
    int w,h;   
 
 

    ifstream Test ("logo.pgm");
    ofstream out ("threshold.pbm");

    getline(Test, line1);
    getline(Test, line2);

    Test >> width; 
    Test >> height;

    w = strToint(width);
    h = strToint(height);

    getline(Test, line3);
    
    getline(Test, gray); 

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
       if (strToint(testline) < t_val) {
        word[y][x]= "0";}

       else {word[y][x]="1";} 
        x++;

        if (testline=="")
        y++;
    }

      out << "P1" <<endl; 
      out << line2 <<endl;
      out << w << " " << h << endl; 
    //output whole array with array position numbers for each entry
        for (int y=0;y<h;y=y+1)
        {
            for (int x=0;x<w;x=x+1){
              out << word[y][x] << endl;
          }
        }
  
    return 0;
  
    return 0;
}

int doubleUp(string fileName){

    string testline, line1,line2,line3,gray,height,width;
    int w,h;   
 
 

    ifstream Test ("log.pgm");
    ofstream out ("double.pgm");

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
    string array[2*h][2*w];
    

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
        x = (x+1);
        if(x>=w)
{
    y = (y+1)%h;
    x = x % w;
}
     
    }

      out << line1 <<endl; 
      out << line2 <<endl;
      out << ceil(w*1.5) << " " << ceil(h*1.5) <<endl;
      out << gray <<endl;
    //output whole array with array position numbers for each entry
   

   for (int a=0;a<h;a++)
        for (int b=0;b<w;b++)
        cout << word[a][b] << " " ;
   
       for (int a=0;a<h;a++){
        for (int b=0;b<w;b++){



           if ((a%2 == 0) && (b%2==0)) {

            array[a*2][b*2]=word[a][b];   
            array[a*2+1][b*2]=word[a][b];
            array[a*2][b*2+1]=word[a][b];
            array[a*2+1][b*2+1]=word[a][b];
        }

           else if  ((a%2 == 0) && (b%2!=0)) {

            array[a*2][b*2]=word[a][b]; 
            array[a*2+1][b*2]=word[a][b]; }


            else if  ((a%2 != 0) && (b%2==0)) {
            array[a*2][b*2]=word[a][b];
            array[a*2][b*2+1]=word[a][b]; 

            }

            else if  ((a%2 != 0) && (b%2!=0)) {
            array[a*2][b*2]=word[a][b];

            }
        }
       } 
       

        for (int y=0;y<2*h;y++)
        {
            for (int x=0;x<2*w;x++){
             if(array[y][x] != "") {
              out << array[y][x] <<  endl;
            }
          }
        }
  
    return 0;
}

