#include <iostream>
#include <cassert>

template <class T>
class Queue {
    unsigned size, head, tail, count;
    T* content;
public:
    Queue(int s) {
        size = s;
        content = new T[size];

        head = 0;
        tail = -1;
        count = 0;
    }

    ~Queue() {
        delete[] content;
    }

    unsigned getCount() {
        return count;
    }

    void push(T value) {
        assert(++count <= size);

        tail = (tail + 1) % size;
        content[tail] = value;
    }

    T pop() {
        assert(count-- != 0);

        T result = content[head];
        head = (head + 1) % size;
        return result;
    }
};

int main() {
    Queue<int> q(10);
    q.push(10);
    q.push(11);
    q.push(12);

    std::cout << q.pop() << ' ' << q.pop() << ' ' << q.pop() << std::endl;
    // std::cout << q.pop() << std::endl;
}