#include <iostream>
#include <cassert>


template <class T>
struct Node {
    T value;
    Node* next;
    Node(T val) {
        value = val;
        next = nullptr;
    }
};

template <class T>
class List {
    Node<T> *head, *tail;
    unsigned size;
public:
    List() {
        size = 0;
        
        head = new Node<T>(T(0));
        head->next = nullptr;

        tail = head;
        tail->next = nullptr;
    }

    void push_back(T val) {
        size++;
        Node<T>* newNode = new Node<T>(val);
        newNode->next = nullptr;
        
        tail->next = newNode;
        tail = newNode;        
    }

    void push_front(T val) {
        size++;
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head->next;
        
        head->next = newNode; 
    }

    T pop_back() {
        size--;
        
        Node<T>* node = head->next;
        for ( ; node->next != tail; node = node->next) {}

        T result = node->next->value;
        
        delete node->next;
        tail = node;
        tail->next = nullptr;

        return result;
    }

    T pop_front() {
        size--;
        
        Node<T>* tmp = head->next;
        head->next = tmp->next;
        
        T result = tmp->value;
        delete tmp;

        return result;
    }

    void insert(unsigned idx, T val) {
        if (idx == 0) {
            push_front(val);
            return;
        }
        if (idx == size + 1) {
            push_back(val);
            return;
        }
        
        size++;
        Node<T>* node = head;
        for (unsigned i = 0; i < idx; ++i)
            node = node->next;
        
        Node<T>* tmp = node->next;
        node->next = new Node<T>(val);
        node->next->next = tmp;
    }

    void insert(Node<T>** node, T val) {    // insert after
        Node<T>* nde = *node;
        if (nde == tail) {
            push_back(val);
            return;
        }

        size++;
        Node<T>* tmp = nde->next;
        nde->next = new Node<T>(val);
        nde->next->next = tmp;
    }

    void print() const {
        Node<T>* node = head->next;
        for ( ; node; node = node->next) {
            std::cout << node->value << ' ';
        }
        std::cout << std::endl;
    }

    Node<T>* operator[] (unsigned idx) {
        assert(idx < size);
        Node<T>* node = head->next;
        for (unsigned i = 0; i < idx; i++)
            node = node->next;
        
        return node;
    }
};

int main() {
    List<int> L;
    
    // pushing back
    int f = 1;
    for (int i = 1; i <= 6; ++i) {
        f *= i;
        L.push_back(f);        
    }
    L.print();

    // pushing front
    f = 1;
    for (int i = 1; i <= 6; ++i) {
        f *= i;
        L.push_front(f);        
    }
    L.print();

    // inserting by idx
    L.insert(4, -77);
    L.print();

    // indexing
    L[6]->value = -33;
    L.print();

    // inserting by node;
    Node<int>* Q = L[2];
    L.insert(&Q, -99);
    L.print();

    // remove
    L.pop_back();
    L.print();
    L.pop_front();
    L.print();
}