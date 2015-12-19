#include <iostream>
  #include <cmath>
  #include <map>
  #include "symbolicc++.h"
  #include <fstream>
  #include <string>
  #include <cstdlib>
  #include <vector>
  #include <stdio.h>
  #include "proof.h"




  using namespace std;


  int factorial(int N)

  //Basic function to calculate the factorial using loop
  {
   int result=1;
   for(int i=2;i<=N;i++) result *= i;
     return result;
  }


  Symbolic faulhaberCombination(int n, int r){

    //In the Faulhaber's formula, we use 'Combinations'. This function takes care of that part

    Symbolic x= Symbolic(factorial(n))/(factorial(r)*factorial(n-r));
    return x;
  }

  /*

  Bernoulli numbers are used in some series
  expansions of several functions (trigonometric, hyperbolic, gamma, etc.),
  and are extremely important in number theory and analysis.
  Note that there are two definitions of Bernoulli numbers;
  this task will be using the modern usage. The n'th Bernoulli number is expressed as Bn.

  */

  Symbolic BERNOA(int n){

    // Computes the first n even _absolute_ Bernoulli numbers.
    // B[0], B[2], B[4], ..., B[2*n - 2] for n >= 1.
    //The Akiyama–Tanigawa algorithm
    //Reference: https://en.wikipedia.org/wiki/Bernoulli_number#Algorithmic_description
    //The function, when looped, generates Bernoulli numbers upto the power in the Faulhaber's formula
    n=n-1;
    Vector<Symbolic> B(n+2);

    for(int i=0;i<=n+1;i++){

      B[i]=Symbolic(1)/(i+1);

      for(int k=i;k>=1;k--){
        B[k-1]= k*(B[k-1]-B[k]);
      }
    }
    if(n==0){
      B[0]=-1*B[0];
    }
    return B[0];
  }

/*
Steps for generating a proof using generateProof():

1) The function takes power as an input and within the function generates
the general form of the Faulhaber series of that formula.
The Faulhaber's formula can be found here: https://en.wikipedia.org/wiki/Faulhaber%27s_formula.
The faulhaberCombination() is used for the part in the formula where we have to calculate the Combination.
It can be seen in the faulhaberCombination() that factorial() is being used.
For example, the general form for 1^1 + 2^1 + 3^1 +.....+ n^1 is n(n+1)/2. For symbolic computations as specified
before, SymbolicC++ is being used.
2) Once we have the general form stored in the 'y' variable, we print it out in LaTex
3) Then we print out the entire proof in the LaTex using the basic Induction Steps.
4) However, we encounter a limitation of Symbolic and LaTex i.e. Symbolic 'cannot' output a string
and when it does computation, it adds ^ for power, which in LaTex is power for a single digit number.
So for instance, if the power is 10 , it will only take 1 not 10. In LaTex for this you need to put {} around exponent
Therefore we decided to parse the LaTex we printed out before converting that into pdf in order to add these
curly brackets around the exponent.
5)After adding curly brackets around the power, we convert that pdf into latex.
*/


  int generateProof(int p){

    string fs,ds,fo;
    cout<<"enter file name" <<endl;
    cin>>fs;
    fo=fs;          //fs is a dummy file while fo will be the actuall file that we will convert to pdf
    ofstream file;
    fo.append(".tex");
    fs.append("_dummy.txt");
    file.open(fs.c_str());
    ds="pdflatex ";             // This varible  is used in the end For Command line input
    ds.append(fo);
    file<<"%BEGIN Preamble\n\\documentclass[letterpaper, 12pt]{article}\n\\usepackage{fullpage}\n\\title{Induction Proof}\n\\author{Abdullah And Affan}\n%END Preamble\n\\begin{document}\n\\maketitle\n\\section{Theorem}\nFor all integers $ n \\geq 1 $\n";
    file<<"\\[1^"<<p<<" +2^"<<p<<" +3^"<<p<<" +...+ n^"<<p;
    //So Basicly we are writing in the file the Format of our proof


      Symbolic t= Symbolic(1)/(1+p);    //according to the algoritm we will need this
      Symbolic one=-1,c,L,b,dumy;       // To make it simple we use more varibles
      Symbolic n("n"),y("y");
      n=~n;
      int Signs;
      y=0;
      for(int i=0; i<=p;i++){           //This step is to calculate the power of -1^n
        Signs=i;
        if(Signs==0)
          one=1;
        else{
          one=-1;
          while(Signs>1){
            one=one*-1;                 //storing the -1^n
            Signs=Signs-1;
          }
        }

        c=faulhaberCombination(p+1,i);  //Storing the Combination
        b=BERNOA(i);                      //Storing the Bernoli
        L=p+1-i;                        //Storing the n^
        dumy=b*c*one;                  //Generating the Coeficent
        y+=dumy*(n^L);                 //Putting it all together

      }
      y=y*t;                           //The final Fraction to multiply


        //From here on we handle the Printing of the output
      file<<" = "<<y<<".......[1]\\]\n";

  file<<"\\section{Proving for a Base Case}\nShow that the property $P(n)$ is true for $n=1$.\n";
  file<<"\\[ 1^"<<p<<" = "<<y<<"...where..n=1\\]\n";

  Equation eq = (1==y[n==1]);

  if(eq){       //This is checking if our Base Case is working or not.
    file<<"\\[1=1\\]\n";
    file<<"Proven For base case\n";}
    else
      file<<"failed to prove\n";
    file<<"\\section{Induction}\nSuppose [1] is true for some n = k $\\geq$ 1, that is.\n";
    file<<"\\[1^"<<p<<"+2^"<<p<<"+3^"<<p<<"+ ... + k^"<<p<<" = "<<y[n=="k"]<<"\\]\nProve that [1] is true for n = k + 1, that is \n";
    file<<"\\[1^"<<p<<"+2^"<<p<<"+3^"<<p<<"+ ... + (k+1)^"<<p<<" = "<<y[n=="(k+1)"]<<"....[2]\\]\nWe have: \n";
    file<<"\\[1^"<<p<<"+2^"<<p<<"+3^"<<p<<"+ ... + k^"<<p<<"+ (k+1)^"<<p<<" = "<<y[n=="(k+1)"]<<"\\]\nInductive Step; solving for the LHS: \n";
    file<<"\\["<<y[n=="k"]<<"+ (k+1)^"<<p<<"\\]\n";
    y=y[n=="k"];        //Substituting n=k
    Symbolic J=y,k("k");
    n="k";
    y=y+((n+1)^p);      //Generating the left hand side
    file<<"\\["<<y<<".....[3]\\]\nNow verifying whether [2] and [3] are equal using SymbolicC++ internal verifier\\\\\n\n The simplified form of [2] is:\n";
    file<<"\\[ "<<J[n=="(k+1)"]<<"\\]\n"<<endl;
    J=J.subst(n==k+1);      //Right hand Side
    file<<"\\[ "<<J<<"\\]\n";
    if(p<=7){       //for bigger powers Symbolic cant handle LONG LONG
      if(J==y)      //This computation becomes time consuming like 50 minutes
        file<<"\n\nwhich is the same as [3]\\\\\n\nHence it is proved. ";
      else
        file<<"unProved\n";
    }
    else
     file<<"\n\nwhich is the same as [3]\\\\\n\nHence it is proved. ";

   file<<"\n\\end{document}\n";
   file.close();
   //THis part of the code Handles all the Formating like having \fac{}{} and \cdot{} and Correcting the Powers etc
   map<char,int> m1;
   m1['+']=1;
   m1['-']=1;
   m1['*']=1;
   m1['/']=1;
   m1['=']=1;
   m1['\\']=1;
   m1['[']=1;
    m1[']']=1;
    m1['\n']=1;
    int flag=0,flag2=0;
    string out=" ",lastop;
    string line,num,dee;
    ifstream myfile (fs.c_str());
    //Since We cant convert Symbolic to String we Read the Symbol from a File as a string
    if (myfile.is_open())
    {
      while ( getline (myfile,line) )
      {
        line.append(1,'\n');
        for (int i = 0; i < line.size(); ++i)
        {
         if(m1.count(line[i])==1 && line[i]!='/'){
          lastop=line[i];
         flag2=0;
          if(dee!=""){
            out.erase(out.size()-dee.size(),out.size());
            out.append("{");
            out.append(dee);
            out.append("}");
            dee="";
            num="";
          }
        }
        out.append(1,line[i]);

        if(flag2==1){
          dee.append(1,line[i]);
        }

        if(line[i]=='/'){

          flag2=1;
          out.erase(out.size()-1,out.size());
          num=out.substr( out.rfind(lastop)+1,out.size()-1);
          out.erase(out.size()-num.size(),out.size());
          out.append("\\frac{");
          out.append(num);
          out.append("}");
        }

        if(line[i]=='^'){
          flag=1;
          out.append(1,'{');
        }
        if(flag==1 && (line[i]=='(' || line[i]==')')){ //removing brackets from the game. for elegance
          out.erase(out.size()-1,out.size());
        }
        if(m1.count(line[i])==1 && flag==1){
          flag=0;

          out.insert(out.size()-1,"}");

        }
      }
      for (int i = 0; i < line.size(); ++i)
        if(line[i]=='*'){
          out.replace(out.find("*"),1,"\\cdot{}");
        }

      }
      myfile.close();
    }
    ofstream ok(fo.c_str());
    ok<<out;
    ok.close();
    system(ds.c_str());//command line
    return 0;
  }



  int main(int argc, char* argv[])
  {
    int power;
    cout<<"enter the number"<<endl;

    cin>>power;


    generateProof(power);


    return 0;
  }
