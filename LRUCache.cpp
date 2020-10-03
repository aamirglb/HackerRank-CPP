#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
#include <fstream>
#include <sstream>

using namespace std;

struct Node{
   Node* prev;
   Node* next;
   int key;
   int value;
   
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache {
   
protected: 
   map<uint32_t,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
public:
    LRUCache(int capacity) {
        cp = capacity;
        tail = nullptr;
        head = nullptr;
        head = nullptr;
        size = 0;
    }

    void set(int key, int value) override {
        if(!head) {
            // first entry
            head = new Node(key, value);            
            mp[key] = head;
            ++size;
        } else {
            if(mp.count(key) > 0) {                
                // entry already present, move to first
                Node *tmp = mp[key];
                // found already at head node or tail node
                if(tmp->prev == nullptr || tmp->next == nullptr) {
                    tmp->value = value;
                } 
                if(tmp->prev != nullptr && tmp->next != nullptr) {                    
                    tmp->value = value;
                    
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                    tmp->next = head;
                    tmp->prev = nullptr;
                    head = tmp;                    
                }
            } else {
                if(size < cp) {
                    auto *tmp = new Node(nullptr, head, key, value);   
                    head->prev = tmp;
                    head = tmp;
                    mp[key] = head;                 
                    ++size;
                } else { 
                    // cache capacity full, delete last node 
                    // and insert new node at head
                    auto *tmp = head;
                    while(tmp->next != nullptr) {                     
                        tmp = tmp->next;                                                
                    }
                    mp.erase(tmp->key);                    
                    tmp->prev->next = nullptr;                    
                    delete tmp;
                    
                    tmp = new Node(nullptr, head, key, value);                    
                    head->prev = tmp;
                    head = tmp;                    
                }
            }
        }        
    }

    int get(int key) override {
        if(mp.count(key) > 0) {
            Node *tmp = mp[key];
            return tmp->value;
        } else {
            return -1;
        }
    }

    void print_cache() {
        auto *tmp = head;
        cout << "NULL";
        while(tmp != nullptr) {
            cout <<"<=>(" << tmp->key << ", " << tmp->value << ")";
            tmp = tmp->next; 
        }
        cout << "<=>NULL\n";
    }

    void print_map() {
        for(auto p : mp) {
            cout << p.first << ", " << p.second << '\n';
        }
        cout << '\n';
    }
private:
    Node *head;   
    int size; 
};

int main() {
#if 1    
    ifstream in("inputs.txt");
    ofstream out("output.txt");

    string line;
    uint32_t line_count, capacity;
    in >> line_count >> capacity;
    cout << line_count << ", " << capacity << '\n';
    LRUCache c(capacity);
    line_count = 0;
    
    while(getline(in, line)) {
        ++line_count;
        stringstream ss(line);
        string cmd;
        int32_t val1{}, val2{};
        ss >> cmd >> val1 >> val2;

        if(cmd == "get") {
            // out << val1 << ", " << c.get(val1) << '\n';
            out << c.get(val1) << '\n';
        } else if(cmd == "set") {
            // out << "setting: " << val1 << " = " << val2 << '\n';
            c.set(val1, val2);
            // c.print_map();
            // cout << "=========\n";
        }
        // cout << "(" << cmd << ", " << val1 << ", " << val2 << ")\n";        
        // if(line_count > 80) break;
    }
#else    
    // c.set(4, 2);
    // c.set(2, 7);
    // cout << c.get(2) << '\n';
    // c.set(1, 8);
    // c.set(5, 9);
    // c.print_cache();
    // c.set(6, 15);
    // c.print_cache();
    // cout << c.get(4) << '\n';
    // cout << c.get(5) << '\n';    
    // c.print_map();
    // c.print_cache();
    
    // c.print_cache();
#endif    
}
