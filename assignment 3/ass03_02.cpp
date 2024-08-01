#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
using namespace std;

class OpenAddressingHashMap {
private:
    vector<pair<string, string>*> table;
    int size;
    string probing;

    int hashFunction(const string& key) {
        hash<string> hashFunc;
        return hashFunc(key) % size;
    }

    int probe(const string& key, int i) {
        return probing == "linear" ? (hashFunction(key) + i) % size : (hashFunction(key) + i * i) % size;
    }

public:
    OpenAddressingHashMap(int size = 100, const string& probing = "linear") : size(size), probing(probing) {
        table.resize(size, nullptr);
    }

    ~OpenAddressingHashMap() {
        for (auto entry : table) {
            if (entry != nullptr && entry != reinterpret_cast<pair<string, string>*>(-1)) {
                delete entry;
            }
        }
    }

    void insert(const string& key, const string& value) {
        for (int i = 0; i < size; i++) {
            int index = probe(key, i);
            if (table[index] == nullptr || table[index] == reinterpret_cast<pair<string, string>*>(-1)) {
                table[index] = new pair<string, string>(key, value);
                return;
            }
        }
        throw overflow_error("HashMap is full");
    }

    bool find(const string& key) {
        for (int i = 0; i < size; i++) {
            int index = probe(key, i);
            if (table[index] == nullptr) return false;
            if (table[index] != reinterpret_cast<pair<string, string>*>(-1) && table[index]->first == key)
                return true;
        }
        return false;
    }

    void remove(const string& key) {
        for (int i = 0; i < size; i++) {
            int index = probe(key, i);
            if (table[index] == nullptr) return;
            if (table[index] != reinterpret_cast<pair<string, string>*>(-1) && table[index]->first == key) {
                delete table[index];
                table[index] = reinterpret_cast<pair<string, string>*>(-1);  
                return;
            }
        }
    }
};


class SeparateChainingHashMap {
private:
    vector<list<pair<string, string>>> table;
    int size;

    int hashFunction(const string& key) {
        hash<string> hashFunc;
        return hashFunc(key) % size;
    }

public:
    SeparateChainingHashMap(int size = 100) : size(size) {
        table.resize(size);
    }

    void insert(const string& key, const string& value) {
        int index = hashFunction(key);
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
    }

    bool find(const string& key) {
        int index = hashFunction(key);
        for (const auto& entry : table[index]) {
            if (entry.first == key) return true;
        }
        return false;
    }

    void remove(const string& key) {
        int index = hashFunction(key);
        table[index].remove_if([&](const pair<string, string>& entry) { return entry.first == key; });
    }
};


int main() {
    
    OpenAddressingHashMap oa_hashmap(10, "linear");
    oa_hashmap.insert("key1", "value1");
    cout << oa_hashmap.find("key1") << endl; 
    oa_hashmap.remove("key1");
    cout << oa_hashmap.find("key1") << endl;  

    SeparateChainingHashMap sc_hashmap(10);
    sc_hashmap.insert("key1", "value1");
    cout << sc_hashmap.find("key1") << endl;  
    sc_hashmap.remove("key1");
    cout << sc_hashmap.find("key1") << endl; 

    return 0;
}
