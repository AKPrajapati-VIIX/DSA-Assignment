// STRUCTUREA
#include<stdio.h>
#include<iostream>
using namespace std;

struct node{
    node*prev;
    int item ;
    node*next;
};
//class;
class DLL{
    private:
    node * start;
    public:
    DLL();

    DLL(DLL&);  //copy constractor
    DLL operator=(DLL &);
    void insertAtStart(int);
    void insertAtLast(int);
    node * search(int);
    void insertAfter(node *t,int);
    // void insertAtLast(int);
    // void insertAfter(node*,int);
    void deleteFirst();
    void del(node);
    ~DLL();   //destractor
     
};

DLL::DLL(){
    start=NULL;
}
DLL::DLL(DLL&d)
{
    node *t;
    if(start!=NULL){

    t=d.start;
    while(t->next! = NULL)
    t=t->next;
    while(t)
    {
        insertAtStart(t->item);
        t=t->prev;

    }
}
else{
    start=NULL;

}}
DLL& DLL::operator=(DLL &d)   //

{ 
    while(start)
        deleteFirst();
    
    node *t;
    if(d.start!=NULL){
    t=d.start;
    while(t->next!=NULL)
    t=t->next;
    while(t)
    {
        insertAtStart(t->item);
        t=t->prev;
    }
}
else{
    start=NULL;

}
   return *this;
   
}


void  DLL::insertAtFirst(int data )
{
     node *n=new node;
    // if(start!=NULL)
    
    n->item=data;
    n->prev=NULL;
    n->next=Start;
    if(start!=NULL){
        start->prev=n;
        start=n;
    }}

void  DLL::insertAtLast(int data ){
    node *n,*t=new node;
    n->item=data;
    n->next=NULL;
    if(start==NULL){
        n->prev=NULL;
        start=n;
    }
    else
    { 
    t=start;
    while(t->next!=NULL)
    n->prev=t;
    t->next=n;
}
}

node* DLL::search(int data){
    node *t,*s=new node;
    t=start;
    while(t){
        if(t->item==data)
        return t;
    t=t->next;
    }
  return NULL;

}


void DLL::insertAfter(node*t,int data)
{
    node*n;
    n=new node;
    n->prev=t;
    n->item=data;
    n->next=t->next;

    if(t->next!=NULL)
       t->next->prev=n;  // focuses
    t->next=n;
}

void DLL::deleteFirst(){
    node*r;
    if(start!=NULL){
        r=start;
        start=r->next;
        start->prev=NULL;
        delete r;
    }
}

void DLL::deleteLast()
{
    node *t=new node;
    t=start;
    if(start==NULL)
    {
        cout<<"list underflow";
    }else
    {
        if(start->next==NULL)
        {
        delete start;
        start=NULL;
        }
        else{
        while(t->next!=NULL)
        t=t->next;
        t->prev->next=NULL;
        delete t;.
        }
    }
}

void DLL::del(node *t)  // traversing dont reqiured.
{
    if(start==NULL)
    cout<<"underflow";

    else if(start==t)
        deleteFirst();
    else if(t->next==NULL)
        deleteLast();

    else{
        t->next->prev=t->prev;
        t->prev->next=t->next;
        delete t;  
    }
} 

DLL::~DLL()
{
    while(start)
        deleteFirst();
}





