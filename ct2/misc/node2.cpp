/**
 * A sample code of clearing a linked list.
 * In this example, we create a new list and append nodes into it,
 * and then remove all the nodes from the list, make the list empty.
 *
 * Outline: There are three steps we should do to clear a list
 *  a) remove a node from a list
 *  b) release the allocated memory of that node
 *  c) repeat a)-b) until there is none node in the list, and reset
 *     the head/tail and other information about the list.
 */

#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

/*
 A linked list is a list constructed using pointers. It is not fixed in
 size and could grow and shrink while the program is running.
 
 A typical defination of list nodes contains at least two parts, both the
 content or date of each element and the pointer to the next element,
 which is shown in the figure below.
 
 +---------+
 |  Data   | -----> holds the data of this element in the list.
 +---------+
 | pointer | -----> is a pointer to the next element in the list.
 +---------+
 
 ***Attention***:
 The pointer holds the address of the next element, not the address of the
 data in the next element, even though they are the same in value sometimes.
 And It should be set to NULL while acting as the last node of the list.
 
 
 Implementation of the single linked list:
 +---------+    --->+---------+    --->+---------+
 |  Data   |    |   |  Data   |    |   |  Data   |
 +---------+    |   +---------+    |   +---------+
 | pointer |-----   | pointer |-----   | pointer |
 +---------+        +---------+        +---------+
 */


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

int main()
{
    /* Create a list */
    LinkedList list;
    list.tailAppend(1);
    list.tailAppend(2);
    list.tailAppend(3);
    list.tailAppend(4);
    
    /* Output the result */
    cout << "Before clearing: " << endl;
    list.traverse_and_print();
    
    /* Output the result */
    list.clear();
    cout << "After clearing: " << endl;
    list.traverse_and_print();
    
    
    return 0;
}




