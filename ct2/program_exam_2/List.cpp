#include <iostream>
#include <cstddef>
#include "list.h"

using std::cout;
using std::endl;


/* 
 class Node
{
    friend class List; //Friendclass is the class within the class. 
private:
    int data;  data, can be any data type, but use integer for our project purpose; data is the 'value' of the Node 
    Node *next; /* pointer to the next node; next is the pointer next  */

//public:
    // Constructors with No Arguments 
 /*   Node(void)
    : next(NULL)
    { }

  
    Node(int val)
    : data(val), next(NULL)
    { }

    Node(int val, Node* pnext)
    : data(val), next(pnext)
    {}

 

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


class List
{
private:

    Node *head;   // head is the pointer head of type Node * (as specified in the manual)
    
    Node *tail; //this is my tail pointer -- not given in the manual but I am using it. 

    

public:
    int inc;
   
    List(void);
    
    List(int val);

    ~List(void);

  
    void append(int val);

    

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

*/
List::List()
{
    /* Initialize the head and tail node */
    head = tail = NULL;
}

List::List(int val)
{
    /* Create a new node, acting as both the head and tail node */
    head = new Node(val);
    tail = head;
}

List::~List()
{
    clear();
}

void List::append(int val)
{
    /* The list is empty? */
    if (head == NULL) {
        /* the same to create a new list with a given value */
        tail = head = new Node(val);
    }
    else
    {
        /* Append the new node to the tail */
        tail->next = new Node(val);
        /* Update the tail pointer */
        tail = tail->next;
    }

}
Node* List::getNode(int pos) //custom functions; gets the node as specified in the public
{
    Node* p = head;

    pos = pos - 1;
    /* Counter */
    while (pos--) { //it does not do anything special. It gets the Node pointer of the desired index. 
        if (p != NULL){
            p = p->next;
            cout << "getNode: " << p->data;
          }  
        else {
            return NULL;
    }
}
    return p;
}


void List::headInsert(int val) //it is a custom function; inserts a node at the head/beginning 
{
    /* If the the list is empty */
    if (head == NULL) {
        /* the same to create a new list with a given value */
        tail = head = new Node(val);
    }
    else
    {
        /* Create a new node and insert it before the head node */
        Node *node = new Node(val);
        node->next = head; //its tail is the old head
        /* Update the head node */
        head = node;
    }
}


void List::insert(int pos, int val) // my pos is the index. I am accustomed to using pos instead of index because index is also a function
{
    inc = List::count(); //inc is the length of the entire linked list 
    if (pos >= 0 && pos >= inc) // if position is positive and out of range. append at the end. 
    {
        List::append(val);
    }

    else if (pos < 0) //if position is negative, append at the beginning 
    {
     List::headInsert(val);   
    }

   else {
    Node* me = List::getNode(pos); //if in middle, append as follows (ME IS 'MIDDLE ELEMENT')
    if (me != NULL)
    {
        me->next = new Node(val, me->next); //we designed a node constructor with val, pointer for this particular job. 
    }
} 

}


void List::pop(int pos = -1) //well it is -1 because -1 when gets modulo-ed with m , will give me the last node. If no pos is specified go
//pop the value of the last node. 

{
    int m = List::count();
    pos = ((pos%m) + m)%m ; 
    int count = 0;
    Node *pPre = NULL, *pDel = NULL;
    
    /* Check whether it is the head node
     if it is, delete and update the head node */
    if (pos == 0) {
        /* point to the node to be deleted */
        pDel = head;
        /* update the head */
        head = pDel->next;
        delete pDel;
        return;
    }
    
    pPre = head;
    pDel = head->next;
        

    /* loop through the list and check the value of each node */
    while (pDel != NULL) {
        count++; 
        if (count == pos) {
            /* Update the list */
            pPre->next = pDel->next;
            /* If it is the last node, try to update the tail */
            if (pDel == tail) {
                tail = pPre;
            }
            delete pDel; /* Here only remove the first node with the given value */
            break; /* break and return */
        }
        pPre = pDel;
        pDel = pDel->next;
    }

}



void List::remove(int val)
{
    Node *pPre = NULL, *pDel = NULL;
    
    /* Check whether it is the head node?
     if it is, delete and update the head node */
    if (head->data == val) {
        /* point to the node to be deleted */
        pDel = head;
        /* update */
        head = pDel->next;
        delete pDel;
        return;
    }
    
    pPre = head;
    pDel = head->next;
    
    /* traverse the list and check the value of each node */
    while (pDel != NULL) {
        if (pDel->data == val) {
            /* Update the list */
            pPre->next = pDel->next;
            /* If it is the last node, update the tail */
            if (pDel == tail) {
                tail = pPre;
            }
            delete pDel; /* Here only remove the first node with the given value */
            break; /* break and return */
        }
        pPre = pDel;
        pDel = pDel->next;
    }
}



void List::clear()
{
    Node *pDel = head;

    /* Traverse the list and delete the node one by one from the head */
    while (pDel != NULL) {
        /* take out the head node */
        head = head->next;
        delete pDel;
        /* update the head node */
        pDel =head;
    }
    /* Reset the head and tail node */
    tail = head = NULL;
}

int List::index(int val)
{
    Node *p = head;

    int count = 0; 

    /* If the list is empty */
    if (head == NULL) {
        cout << "The list is empty" << endl;
        return -1;
    }


    /* A basic way of traversing a linked list */
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        if (p->data== val){
            return count;
        }
        /* The pointer goes to the next one */
        p = p->next;
        count++;
    }
    return -1;

}


void List::sort()
{

    Node* temp =head; //take a temporary node as head 
    int tmp;
    int counter= List::count(); //entire size of the linked list
    for (int i =0; i<=counter; i++)
    {
        while(temp->next) //while head has any list 
            {
            if(temp->data > temp->next->data) //if data of the pervious node greater than the next of next node do the following.
                {
                    tmp = temp->data;
                    temp->data = temp->next->data;
                    temp->next->data = tmp;
                    temp = temp->next;
                }
            else{
                temp= temp->next;
            }
            }   temp=head;
    }
    }


int List::count()
{
    Node *p = head; 

    inc = 0;

    /* The list is empty? */
    if (head == NULL) {
        cout << "The list is empty" << endl;
        return inc;
    }

    /* A basic way of traversing a linked list */
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        /* The pointer moves along to the next one */
        p = p->next;
        inc++;
    }
    return inc; 

}

int List::at(int index){ 

Node *p = head;

int m = List::count();

if (index > m){
	cout << "Error...this is out of range";
	return -1;
}

int pIndex = ((index%m) + m)%m ; //for negative indices -- for example -1 is the last element. 
 /* The list is empty? */
    if (head == NULL) {
        cout << "The list is empty" << endl;
        return 0;
    }

for (int i = 0; i < pIndex; i++)
{
  p = p ->next;
}



return p->data;

}

