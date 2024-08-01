#include<stdio.h>
#include<iostream>
using namespace std;


class Array{
    
    private:

         int capacity;
         int lastindex;
         int *ptr;

    public:
        // functions;
        //apstract datatype.
        Array();  // constractor for prevent memory leak
        Array(Array &);  // copy constractor.
        Array& operator=(Array &);
        void createArray(int);
        void insert(int,int); // change nhi karega
        void append(int);
        int getItem(int);
        bool isEmpty();
        bool isFull();
        void del(int);
        void edit(int,int); //value ko change karega
        int count();
        int getcapacity();
        ~Array();

};

// constactor for prevent memory leak 
Array::Array(){
    ptr=NULL;
}

Array::Array(Array&arr){
    capacity=arr.capacity;
    lastindex=arr.lastindex;
    ptr=new int[capacity];
    for(int i=0;i<=lastindex;i++)
        ptr[i]=arr.ptr[i];


}

Array& Array::operator=(Array &arr)
{
    capacity=arr.capacity;
    lastindex=arr.lastindex;
    if(ptr!=NULL)
        delete []ptr;
    ptr=new int[capacity];
    for(int i=0;i<=lastindex;i++)
        ptr[i]=arr.ptr[i];
    return(*this);

}

//class
void Array::createArray(int cap)
{
    capacity=cap;
    lastindex=-1;
    if(ptr!=NULL)
        delete []ptr;
    ptr=new int [capacity];
}


void Array::append(int data)
{
    
    if(isFull())
    {
        lastindex++;
        ptr[lastindex]=data;
    }
    else
    cout<<"overflow : append not perform"<<endl;

}

bool Array::isFull()
{
    return lastindex==capacity-1;
}
bool Array::isEmpty()
{
    return lastindex==-1;
}

void Array::insert(int index,int data)
{
    int i;

    try{
        if(index<0 || index>lastindex+1)
            throw 1;
        if(isFull())
            throw 2;
        for(i=lastindex;i>=index;i--)
            ptr[i+1]=ptr[i];
        ptr[index]=data;
        lastindex++;

    }
    catch(int e){
        if(e==1)
            cout<<"invalid index";
        else if(e==2)
            cout<<"overflow";
    }
    }

int Array::getItem(int index)
{
    try{
        if(index<0 || index>lastindex)
            throw 1;
        return ptr[index];
        
    }
    catch(int e)
    {
        if(e==1)
        cout<<"\ninvalid index or Aray is empty";

    }
    return -1;
}

int Array::getcapacity()
{
    return capacity;
}
int Array::count()
{
    return lastindex+1;
}

void Array::edit(int index,int newdata)
{
    try{
        if(index<0 || index>lastindex)
            throw 1;
        ptr[index]=newdata;
    }
    catch(int e)
    {
        if(e==1)
            cout<<"\ninvalide index";
    }
}

void Array::del(int index)
{
    int i;
    try{
        if(index<0 || index>lastindex)
            throw 1;
        for(i=index; i<lastindex;i++)
            ptr[i]=ptr[i+1];
        lastindex--;
    }
    catch(int e)
    {
        if(e==1)
            cout<<"\ninvalid index or underflow";
    }
}

Array::~Array()
{
    delete []ptr;
}