#include <iostream>
#include <cstddef>
#include <conio.h>

using namespace std;
class Stack
{

private:
 int top,length;
 int* data;

public:
	Stack(int = 0);
	~Stack();

   void push(int);
   int pop();
   string isEmpty();
   void display();
};

Stack::Stack(int size){
   top = -1;
   length = size;
   if (size == 0)
   	data = 0;
   else
   	data = new int[length];
}

Stack::~Stack(){
	if (data != 0)
		delete [] data; //memory deallocation
}

void Stack::push(int value){
	if (data == 0)
	{
		cout << "Enter the size: ";
		cin >> length;
		data = new int [length];
	}
	/*if (top == length-1)
	{
		top = -1;
	}*/
    else {
    	top++;
    	data[top%length] = value;
    }
}

int Stack::pop (){
	if (data == 0 || top == -1)
	{
		cout << "Stack is empty";
	    return -1;
	}

	int val = data[top];
	top --;
	return val;

}

string Stack::isEmpty(){
	if (top == -1)
		return "true";
	else
		return "false";
}

void Stack::display()
{
    for(int i = 0; i <= top; i++)
        cout<<data[i]<<" ";
    cout<<endl;
}


int main()
{
    Stack s1(3);             //We are creating a stack of size 'zero'
    s1.push(1);

    s1.push(2);
    s1.push(3);
    s1.push(4);
   //s1.~Stack();
    s1.push(5);
   // s1.push(6);
    s1.display();
    //cout << s1.isEmpty();
    /*s1.display();
    s1.pop();
    s1.display();
    s1.pop();
    s1.display();
    s1.pop();
    s1.display();
    s1.pop();
    s1.display();*/
}
