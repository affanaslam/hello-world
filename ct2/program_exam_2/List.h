#ifndef LIST_H
#define LIST_H


#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;


class Node
{
    friend class List; //Friendclass is the class within the class. 
private:
    int data; /* data, can be any data type, but use integer for our project purpose; data is the 'value' of the Node */
    Node *next; /* pointer to the next node; next is the pointer next  */

public:
    /* Constructors with No Arguments */
    Node(void)
    : next(NULL)
    { }

    /* Constructors with a given value */
    Node(int val)
    : data(val), next(NULL)
    { }

    /* Constructors with a given value and a link of the next node. We can make several constructors as per our need */
    Node(int val, Node* pnext)
    : data(val), next(pnext)
    {}

    /* Getters & Setters (as specified in the manual) */

    void setValue(int val){
       data = val;
    }

    void setNext (Node* _pNex){
      next = _pNex;
    }

    int getValue(void)
    { return data; }

    Node* getNext(void)
    { return next; }
};

/* definition of the linked list class */
class List
{
private:
    /* pointer of head node */
    Node *head;   // head is the pointer head of type Node * (as specified in the manual)
    /* pointer of tail node */
    Node *tail; //this is my tail pointer -- not given in the manual but I am using it. 

    

public:
    int inc;
    /* Constructors with No Arguments */
    List(void);
    /* Constructors with a given value of a list node */
    List(int val);
    /* Destructor */
    ~List(void);

    /* Function to append a node to the end of a linked list */
    void append(int val);

    /* Function to delete all the elements of a linked list. As you will see later, it will loop through the entire linked list and delete one by one */
    void clear();

    int at (int index); // 

    int count ();

    void remove(int val);
   

    Node* getNode(int pos); //it gets the pointer to the node of the index 'pos'

    void insert(int pos, int val);

    void headInsert(int val);

    void pop(int pos);

    void sort ();

    int index(int val);


};


#endif