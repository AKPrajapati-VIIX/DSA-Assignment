// STRUCTUREA
#include<stdio.h>
#include<iostream>
using namespace std;

struct node{
    int item;
    node*next;
};
//class;
class SLL{
    private:
    node * start;
    public:
    SLL();
    SLL(SLL&);
    SLL& operator=(SLL &);  // copy constrator
    void insertAtStart(int);
    void insertAtLast(int);
    void insertAfter(node*,int);
    node* search(int);
    void deleteFirst();
    void deletelast();
    void deletenode(node*);
     ~SLL();  // destractor



};
// CONSTructor
SLL::SLL(){
    start=NULL;
}

// DESTRACTOR:
SLL::SLL(SLL &list)
{
    node *t;
    t=list.start;
    start=NULL;
    while(t)
    {
        insertAtLast(t->item);
        t=t->next;
      }  }


SLL& SLL::operator=(SLL &list)
{
    node *t;
    t=list.start;
    while (start)
        deletefirst();

    while(t)
    {
        insertAtLast(t->item);
        t=t->next;
    } 
    return *this;
}



void SLL:: insertAtStart(int data)
{
    node *n=new node;
    n->item=data;
    n->next=start;
    start=n;
}
void SLL::insertAtLast(int data)
{
    node*t;
    node *n=new node;
    n->item=data;
    n->next=NULL;

    if(start==NULL)
        start=n;
    else{
        t=start;
        while(t->next!=NULL)
            t=t->next;
        t->next=n;
    }
}
node* SLL::search(int data)
{
    node*t;
    t=start;
    while(t!=NULL){
        if(t->item==data)
        return t;
    t=t->next;
    }
    return NULL;
}

//insert after
void SLL::insertAfter(node *t,int data)
{
    node *n;
    if(t){
        n=new node;
        n->item=data;
        n->next=t->next;
        // t=n; wrong 
        t->next=n;
    }

}


// DELETE FIRST:
void SLL::deleteFirst()
{
    node *n;  // for prevent from memory leak
    if(start)
    {
        n=start;
        start=n->next;
        delete n;
    }
}

// DELETE LAST:
void SLL::deletelast()

   node *t; 
    try{
       if(t==NULL){
           throw 1;
       if(start->next==NULL)
     {
          delete start;
          start=NULL;
    }
    else
    {
        t=start;
        while(t->next->next!=NULL)
            t=t->next;
            delete t->next;
            t->next=NULL;
    }
    }
    catch(int e)
    {

    }}


void SLL::delNode(node *t)
{
    node *r;
    try{
        if{start==NULL}
           throw 1;
        if(start==t)
          deletefirst();
        else
        {
            r=start;
            while(r->next!=t)
            r=r->next;
        r->next=t->next;
        delete t;
        }

    }

}

