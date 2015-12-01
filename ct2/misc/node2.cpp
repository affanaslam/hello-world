
#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;




/* definition of the list node class */
class Node
{
    friend class LinkedList;
private:
    int _value; /* data, can be any data type, but use integer for easiness */
    Node *_pNext; /* pointer to the next node */

public:
    /* Constructors with No Arguments */
    Node(void)
    : _pNext(NULL)
    { }

    /* Constructors with a given value */
    Node(int val)
    : _value(val), _pNext(NULL)
    { }

    /* Constructors with a given value and a link of the next node */
    Node(int val, Node* next)
    : _value(val), _pNext(next)
    {}

    /* Getters */

    void setValue(int val){
       _value = val;
    }

    void setNext (Node* _pNex){
      _pNext = _pNex;
    }

    int getValue(void)
    { return _value; }

    Node* getNext(void)
    { return _pNext; }
};

/* definition of the linked list class */
class LinkedList
{
private:
    /* pointer of head node */
    Node *_pHead;
    /* pointer of tail node */
    Node *_pTail;

    

public:
    int inc;
    /* Constructors with No Arguments */
    LinkedList(void);
    /* Constructors with a given value of a list node */
    LinkedList(int val);
    /* Destructor */
    ~LinkedList(void);

    /* Function to append a node to the end of a linked list */
    void tailAppend(int val);

    /* Function to delete all the elements of a linked list */
    void clear();

    int at (int index);

    int count ();

    void remove(int val);
   

    Node* getNode(int pos);

    void insert(int pos, int val);

    void headInsert(int val);

    void pop(int pos);

    int index(int val);

    /* Traversing the list and printing the value of each node */
    void traverse_and_print();

};

LinkedList::LinkedList()
{
    /* Initialize the head and tail node */
    _pHead = _pTail = NULL;
}

LinkedList::LinkedList(int val)
{
    /* Create a new node, acting as both the head and tail node */
    _pHead = new Node(val);
    _pTail = _pHead;
}

LinkedList::~LinkedList()
{
    clear();
}

void LinkedList::tailAppend(int val)
{
    /* The list is empty? */
    if (_pHead == NULL) {
        /* the same to create a new list with a given value */
        _pTail = _pHead = new Node(val);
    }
    else
    {
        /* Append the new node to the tail */
        _pTail->_pNext = new Node(val);
        /* Update the tail pointer */
        _pTail = _pTail->_pNext;
    }

}
Node* LinkedList::getNode(int pos)
{
    Node* p = _pHead;

    pos = pos - 1;
    /* Counter */
    while (pos--) {
        if (p != NULL){
            p = p->_pNext;
            cout << "getNode: " << p->_value;
          }  
        else {
            return NULL;
    }
}
    return p;
}


void LinkedList::headInsert(int val)
{
    /* The list is empty? */
    if (_pHead == NULL) {
        /* the same to create a new list with a given value */
        _pTail = _pHead = new Node(val);
    }
    else
    {
        /* Create a new node and insert it before the head node */
        Node *node = new Node(val);
        node->_pNext = _pHead; //its tail is the old _pHead
        /* Update the head node */
        _pHead = node;
    }
}


void LinkedList::insert(int pos, int val)
{
    if (pos >= 0 && pos >= inc)
    {
        LinkedList::tailAppend(val);
    }

    else if (pos < 0)
    {
     LinkedList::headInsert(val);   
    }

   else {
    Node* afterMe = LinkedList::getNode(pos);
    if (afterMe != NULL)
    {
        afterMe->_pNext = new Node(val, afterMe->_pNext);
    }
} 

}


void LinkedList::pop(int pos){

 

}




void LinkedList::remove(int val)
{
    Node *pPre = NULL, *pDel = NULL;
    
    /* Check whether it is the head node?
     if it is, delete and update the head node */
    if (_pHead->_value == val) {
        /* point to the node to be deleted */
        pDel = _pHead;
        /* update */
        _pHead = pDel->_pNext;
        delete pDel;
        return;
    }
    
    pPre = _pHead;
    pDel = _pHead->_pNext;
    
    /* traverse the list and check the value of each node */
    while (pDel != NULL) {
        if (pDel->_value == val) {
            /* Update the list */
            pPre->_pNext = pDel->_pNext;
            /* If it is the last node, update the tail */
            if (pDel == _pTail) {
                _pTail = pPre;
            }
            delete pDel; /* Here only remove the first node with the given value */
            break; /* break and return */
        }
        pPre = pDel;
        pDel = pDel->_pNext;
    }
}



void LinkedList::clear()
{
    Node *pDel = _pHead;

    /* Traverse the list and delete the node one by one from the head */
    while (pDel != NULL) {
        /* take out the head node */
        _pHead = _pHead->_pNext;
        delete pDel;
        /* update the head node */
        pDel = _pHead;
    }
    /* Reset the head and tail node */
    _pTail = _pHead = NULL;
}

int LinkedList::index(int val)
{
    Node *p = _pHead;

    int count = 0; 

    /* The list is empty? */
    if (_pHead == NULL) {
        cout << "The list is empty" << endl;
        return -1;
    }


    /* A basic way of traversing a linked list */
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        if (p->_value == val){
            return count;
        }
        /* The pointer moves along to the next one */
        p = p->_pNext;
        count++;
    }
    return -1;

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
        cout << p->_value << " ";
        /* The pointer moves along to the next one */
        p = p->_pNext;
    }
    cout << endl;

}

int LinkedList::count()
{
    Node *p = _pHead; 

    inc = 0;

    /* The list is empty? */
    if (_pHead == NULL) {
        cout << "The list is empty" << endl;
        return inc;
    }

    /* A basic way of traversing a linked list */
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        /* The pointer moves along to the next one */
        p = p->_pNext;
        inc++;
    }
    return inc; 

}

int LinkedList::at(int index){ //it doesn't take negative numbers as input

Node *p = _pHead;

int m = LinkedList::count();

int pIndex = ((index%m) + m)%m ;
 /* The list is empty? */
    if (_pHead == NULL) {
        cout << "The list is empty" << endl;
        return 0;
    }

for (int i = 0; i < pIndex; i++)
{
  p = p ->_pNext;
}



return p->_value;

}


int main()
{
    /* Create a list */
    
    LinkedList list;
    list.tailAppend(1);
    list.tailAppend(2);
    list.tailAppend(3);
    list.tailAppend(4);
    //list.headInsert(9);
    cout << "count" << list.count() << endl;
    
    list.insert(-1, 6);

    cout << "index: " << list.index(8) << endl;
    //list.remove(6);


    list.traverse_and_print();

    cout << "p" << list.at(-2) <<endl;

    cout << "count" << list.count() << endl;
    /* Output the result */
    cout << "Before clearing: " << endl;
    list.traverse_and_print();

    /* Output the result */
    list.clear();
    cout << "After clearing: " << endl;
    list.traverse_and_print();


    return 0;
}




