#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <cstddef>
#include <conio.h>
#include <string>


using namespace std;



class Stack
{

private:
 int top; //top is the current top of the stack 
 int length; //because bottom is a misleading term so I dare to use 'length' as my variable instead. It makes much more sense now. 
 int* data; //data pointer points to the data 

public:
	Stack(int = 0); //initializing as zero; I have done an additional thing. When you will enter a zero stack; it will automatically ask you to push more 
	~Stack(); //destructor 

   void push(int);
   int pop();
   string isEmpty();
   void display(); //an additional function for the display purpose. You can ignore it or use it for the testing purpose. 
};

#endif