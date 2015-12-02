#include <iostream>
#include <cstddef>
#include <conio.h>
#include <string>
#include "stackArray.h"

using namespace std;
/*class Stack
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
};*/

Stack::Stack(int size){
   top = -1; // top starts from -1 
   length = size; // length is actually equal to size. 
   if (size == 0)
   	data = 0;  
   else
   	data = new int[length]; //creation of stack with allocated size 
}

Stack::~Stack(){
	if (data != 0)
		delete [] data; //memory deallocation
}

void Stack::push(int value){
	if (data == 0)
	{
		cout << "Enter the size: "; //in case the stack is empty, let the user create it. A nice pratice maybe. 
		cin >> length;
		data = new int [length];
	}
    
    	top++; //increment the top first , make it at least zero; top begins from -1
    	data[top%length] = value;// as specified in the manual. Once the size
//of the array is exceeded, subsequent pushes add elements at index 0 onward in the array, i.e. elements
//in the stack that are older by size pushes get overwritten. We can simple take top modulo length to make it move in a cyclical manner 
    
}

int Stack::pop (){
	if (data == 0 || top == -1)
	{
		cout << "Stack is empty"; //Stack is empty 
	    return -1;
	}

	int val = data[top%length]; // pop again would consinder the out of range notion. Hence we need to use this idea here as well 
	top --;
	return val;

}

string Stack::isEmpty(){ //we can also take a bool but since we are returning a string why not string. 
	if (top == -1) //as we specified earlier , our top is intialized at -1. Means that if it is empty, it has to be -1 
		return "true";
	else
		return "false";
}

void Stack::display()
{
    for(int i = 0; i <= length; i++)
        cout<<data[i]<<" ";
    cout<<endl;
}


