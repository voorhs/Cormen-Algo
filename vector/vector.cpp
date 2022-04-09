#include <iostream>
#include <cassert>

template <class T>
class Vector {
    int size, alloc;
    T*  content;
public:
    Vector() { size = 0; alloc = 0; }

    ~Vector() {
        if (alloc > 0)
            delete[] content;
    }

    Vector(int s, T value = T(0)) {
        assert(s > 0);

        size = s;
        alloc = s;
        content = new T[size];
        
        for (int i = 0; i < size; i++)
            content[i] = value;
    }

    void print(const char* s = 0) {
        if (s != 0)
            std::cout << s << ": ";
        
        for (int i = 0; i < size; i++)
            std::cout << content[i] << ' ';
        std::cout << std::endl; 
    }

    void push_back(T value) {
        if (++size > alloc)
        {
            if (alloc == 0)
                alloc = 1;
            else
                alloc *= 2;
            
            T* tmp = new T[alloc];
            for (int i = 0; i < size - 1; i++)
                tmp[i] = content[i];
            for (int i = size - 1; i < alloc; i++)
                tmp[i] = T(0);
            
            if (alloc > 1)
                delete[] content;
            content = tmp;
        }

        content[size - 1] = value;
    }

    T& operator[] (int idx) {
        if (idx >= size)
            resize(idx);
                
        return content[idx];
    }

    void remove(int idx) {
        assert(idx < size--);

        for (int i = idx; i < size; i++)
            content[i] = content[i + 1];
    }

    void resize(int idx) {
        bool empty = (alloc == 0);
        unsigned newAlloc = (empty ? 1 : alloc);
        while (newAlloc <= idx) 
            newAlloc *= 2;
        
        T* newContent = new T[newAlloc];
        for (unsigned i = 0; i < size; ++i)         // copy stored data
            newContent[i] = content[i];
        for (unsigned i = size; i < newAlloc; ++i)  // fill extra space with nills
            newContent[i] = T(0);
        
        if (!empty)
            delete[] content;
        content = newContent;

        alloc = newAlloc;
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
    x[3] = 17;
    x.print("x");
}