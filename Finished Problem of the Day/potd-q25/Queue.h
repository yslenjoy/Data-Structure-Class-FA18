#ifndef _QUEUE_H
#define _QUEUE_H

#include <cstddef>
#include <vector>

class Queue {
    public:
        int size() const;
        bool isEmpty() const;
        void enqueue(int value);
        int dequeue();
        Queue();
    private:
    	std::vector<int> q;
};

#endif
