#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;


class Node
{

	friend class LinkedList; 
public:
 

  Node(int value)
: _data(value), _pNext(NULL)
{}

//getters and setters

 Node* setNext(Node* next){
	_pNext = next;
}

Node* getNext(void){
	return _pNext;
}


int getData(void){
	return _data;
}

int setData (int value){
	_data = value;
}


private:
	int _data; //data to be inserted in the node
	Node* _pNext; // the next node's pointer.  	
};


class LinkedList  {
 
 private:

 	Node* _pHead;  
 
 public: 

  /* Constructors with No Arguments */
    LinkedList(void);
    /* Constructors with a given value of a list node */
    LinkedList(int val);
    /* Destructor */
    ~LinkedList(void);

    void traverse_and_print();
};

LinkedList::LinkedList(void) {
_pHead = NULL;
}

void LinkedList::traverse_and_print()
{
    Node *p = _pHead;
    
    /* The list is empty? */
    if (_pHead == NULL) {
        cout << "The list is empty" << endl;
        return;
    }
    
    cout << "LinkedList: ";
    /* A basic way of traversing a linked list */
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        cout << p->_data;
        /* The pointer moves along to the next one */
        p = p->_pNext;
    }
    cout << endl;
}
int main()
{
    /* Create an empty list */
    LinkedList list1;
    cout << "Created an empty list named list1." << endl;
    /* output the result */
    cout << "list1:" << endl;
    list1.traverse_and_print();
    
    /* Create a list with only one node */
    LinkedList list2(10);
    cout << "Created a list named list2 with only one node." << endl;
    /* output the result */
    cout << "list2:" << endl;
    list2.traverse_and_print();
    
    return 0;
}