#pragma once
#include <iosfwd>
#include <concepts>
#include <iostream>
#include <print>

namespace messageQueue {
    template<typename T>
    class MessageQueue {
        std::vector<T> data;
        std::vector<T>::iterator head;
        std::vector<T>::iterator tail;

        size_t capacity;
        size_t size;

    public:
        explicit MessageQueue(size_t capacity) {
            assert(capacity > 0);

            data = std::vector<T>(capacity);
            head = data.begin();
            tail = data.begin();

            this->capacity = capacity;
            size = 0;
        }

        void enqueue(T message);
        T dequeue();
    };

    template<typename T>
    void MessageQueue<T>::enqueue(T message) {
        if (size == capacity) return;

        *head++ = message;
        if (head == data.end()) {
            head = data.begin();
        }
        ++size;
    }

    template<typename T>
    T MessageQueue<T>::dequeue() {
        if (size == 0) return T{};

        T toReturn = *tail++;
        if (tail == data.end()) {
            tail = data.begin();
        }
        --size;

        return toReturn;
    }
}





