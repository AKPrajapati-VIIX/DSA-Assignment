#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
public:
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void remove(Node* node) {
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
    }

    void add(Node* node) {
        node->next = head->next;
        node->next->prev = node;
        head->next = node;
        node->prev = head;
    }

public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            remove(node);
            add(node);
            return node->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            remove(cache[key]);
        }
        Node* node = new Node(key, value);
        add(node);
        cache[key] = node;
        if (cache.size() > capacity) {
            Node* lru = tail->prev;
            remove(lru);
            cache.erase(lru->key);
            delete lru;
        }
    }

    ~LRUCache() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    LRUCache lru_cache(2);
    lru_cache.put(1, 1);
    lru_cache.put(2, 2);
    cout << lru_cache.get(1) << endl;  
    lru_cache.put(3, 3);              
    cout << lru_cache.get(2) << endl;  
    lru_cache.put(4, 4);               
    cout << lru_cache.get(1) << endl; 
    cout << lru_cache.get(3) << endl;  
    cout << lru_cache.get(4) << endl;  

    return 0;
}
