#include <iostream>
#include <stdio.h>
using namespace std;

#define INVALID_QUEUE_STATE 1
#define OVERFLOW 2
#define UNDERFLOW 3

class Queue {
private:
    int capacity;
    int front, rear;
    int *ptr;

public:
    Queue(int);
    Queue(const Queue&);
    Queue& operator=(const Queue&);
    void insert(int);
    bool isFull();
    int getFront();
    int getBack();
    bool isEmpty();
    void del();
    ~Queue();
    int count();
};

Queue::Queue(int cap) {
    capacity = cap;
    front = -1;
    rear = -1;
    if (cap > 0)
        ptr = new int[cap];
    else
        ptr = nullptr;
}

Queue::Queue(const Queue &q) {
    capacity = q.capacity;
    front = q.front;
    rear = q.rear;
    ptr = new int[capacity];
    for (int i = 0; i < capacity; i++)
        ptr[i] = q.ptr[i];
}

Queue& Queue::operator=(const Queue &q) {
    if (this != &q) {
        delete[] ptr;
        capacity = q.capacity;
        front = q.front;
        rear = q.rear;
        ptr = new int[capacity];
        for (int i = 0; i < capacity; i++)
            ptr[i] = q.ptr[i];
    }
    return *this;
}

void Queue::insert(int data) {
    if (capacity <= 0)
        throw INVALID_QUEUE_STATE;
    if (isFull())
        throw OVERFLOW;

    if (rear == -1) {
        rear = front = 0;
        ptr[rear] = data;
    } else if (rear == capacity - 1) {
        rear = 0;
        ptr[rear] = data;
    } else {
        rear++;
        ptr[rear] = data;
    }
}

void Queue::del() {
    if (isEmpty())
        throw UNDERFLOW;
    if (front == rear) {
        front = rear = -1;
    } else if (front == capacity - 1) {
        front = 0;
    } else {
        front++;
    }
}

bool Queue::isFull() {
    return (front == 0 && rear == capacity - 1) || (rear + 1 == front);
}

bool Queue::isEmpty() {
    return front == -1;
}

int Queue::getFront() {
    if (isEmpty())
        throw UNDERFLOW;
    return ptr[front];
}

int Queue::getBack() {
    if (isEmpty())
        throw UNDERFLOW;
    return ptr[rear];
}

int Queue::count() {
    if (front == -1)
        return 0;
    if (front == rear)
        return 1;

    if (rear > front)
        return rear - front + 1;
    else
        return capacity - front + rear + 1;
}

Queue::~Queue() {
    delete[] ptr;
}


int main() {
    try {
        Queue q(5); // Create a queue with capacity 5
        
        // Insert elements into the queue
        q.insert(10);
        q.insert(20);
        q.insert(30);
        q.insert(40);
        q.insert(50);
        
        // Display front and rear elements
        cout << "Front element: " << q.getFront() << endl; // Output: 10
        cout << "Rear element: " << q.getBack() << endl; // Output: 50
        
        // Display queue status
        cout << "Is queue full? " << (q.isFull() ? "Yes" : "No") << endl; // Output: Yes
        cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl; // Output: No
        cout << "Number of elements in queue: " << q.count() << endl; // Output: 5
        
        // Delete two elements from the queue
        q.del();
        q.del();
        
        // Display front and rear elements
        cout << "Front element after deletion: " << q.getFront() << endl; // Output: 30
        cout << "Rear element after deletion: " << q.getBack() << endl; // Output: 50
        
        // Insert another element into the queue
        q.insert(60);
        
        // Display front and rear elements
        cout << "Front element after insertion: " << q.getFront() << endl; // Output: 30
        cout << "Rear element after insertion: " << q.getBack() << endl; // Output: 60
        
        // Display queue status
        cout << "Is queue full? " << (q.isFull() ? "Yes" : "No") << endl; // Output: No
        cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl; // Output: No
        cout << "Number of elements in queue: " << q.count() << endl; // Output: 4

    } catch (int e) {
        if (e == INVALID_QUEUE_STATE)
            cerr << "Error: Invalid queue state" << endl;
        else if (e == OVERFLOW)
            cerr << "Error: Queue overflow" << endl;
        else if (e == UNDERFLOW)
            cerr << "Error: Queue underflow" << endl;
    }
    
    return 0;
}
