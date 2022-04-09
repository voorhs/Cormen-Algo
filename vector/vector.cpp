#include <iostream>
#include <cassert>

template <class T>
class Vector {
    unsigned size, alloc;
    T*  content;
public:
    Vector() {
        size = 0; alloc = 1;
        content = new T[alloc];
    }

    ~Vector() {
        delete[] content;
    }

    Vector(unsigned s, T value = T(0)) {
        assert(s > 0);

        size = s;
        alloc = s;
        content = new T[size];
        
        for (unsigned i = 0; i < size; i++)
            content[i] = value;
    }

    void print(const char* s = 0) const {
        if (s != 0)
            std::cout << s << ": ";
        
        for (unsigned i = 0; i < size; i++)
            std::cout << content[i] << ' ';
        std::cout << std::endl; 
    }

    void push_back(T value) {
        if (++size > alloc) {
            resize(size - 1);
        }

        content[size - 1] = value;
    }

    T& operator[] (int idx) {
        if (idx >= size)
            resize(idx);
                
        return content[idx];
    }

    void remove(unsigned idx) {
        assert(idx < size--);

        for (unsigned i = idx; i < size; i++)
            content[i] = content[i + 1];
    }

    void resize(int idx) {
        while (alloc <= idx) 
            alloc *= 2;
        
        T* newContent = new T[alloc];
        for (unsigned i = 0; i < size; ++i)         // copy stored data
            newContent[i] = content[i];
        for (unsigned i = size; i < alloc; ++i)     // fill extra space with nills
            newContent[i] = T(0);
        
        delete[] content;
        content = newContent;

        size = idx + 1;
    }
};

int main() {
    // create
    Vector<int> v, w(10), x(2, 333);
    
    // show
    v.print("v");
    w.print("w");
    x.print("x");

    // add to tail
    v.push_back(1);
    w.push_back(1);
    x.push_back(1);

    v.print("v");
    w.print("w");
    x.print("x");

    // delete by idx
    v.remove(0);
    w.remove(0);
    x.remove(0);

    v.print("v");
    w.print("w");
    x.print("x");

    // retrieve by idx
    v[5] = 88;
    w[2] = 66;
    x[3] = 77; 

    v.print("v");
    w.print("w");
    x.print("x");
}