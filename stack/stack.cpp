#include <iostream>
#include <cassert>

template <class T>
class Stack {
    unsigned size, alloc;
    T* content;
public:
    Stack() {
        size = 0; alloc = 1;
        content = new T[alloc];
    }

    ~Stack() {        
        delete[] content;
    }

    bool isEmpty() {
        return (size == 0);
    }

    void push(T value) {
        if (++size > alloc)
        {    
            alloc *= 2;

            T* newContent = new T[alloc];
            for (unsigned i = 0; i < size - 1; i++)
                newContent[i] = content[i];
            for (unsigned i = size - 1; i < alloc; i++)
                newContent[i] = T(0);
            
            delete[] content;
            content = newContent;
        }

        content[size - 1] = value;
    }

    T& top() const {
        return content[size - 1];
    }

    T pop() {
        assert(size > 0);
        return content[--size];
    }
};


int main() {
    Stack<int> s;
    s.push(12);
    std::cout << s.isEmpty() << ' ' << s.pop() << ' ' << s.isEmpty();   // False 12 True
}