#pragma once
#include <array>
#include <concepts>

// TODO Make threadsafe
namespace messageQueue {
    template<typename T, size_t CAPACITY>
    class MessageQueue {
        std::array<std::optional<T>, CAPACITY> data{};

        size_t head{};
        size_t tail{};
        size_t size{};

    public:
        using valueType = T;

        template<typename U>
        requires std::constructible_from<T, U&&>
        void enqueue(U&& message);
        std::optional<T> dequeue();

        bool isEmpty() const;
        bool isFull() const;
    };

    template<typename T, size_t CAPACITY>
    template<typename U> requires std::constructible_from<T, U &&>
    void MessageQueue<T, CAPACITY>::enqueue(U &&message) {
        if (isFull()) return;

        data[head].emplace(std::forward<U>(message));
        head = (head + 1) % CAPACITY;
        ++size;
    }

    template<typename T, size_t CAPACITY>
    std::optional<T> MessageQueue<T, CAPACITY>::dequeue() {
        if (isEmpty()) return std::nullopt;

        auto result = std::move(data[tail]);
        data[tail].reset();
        tail = (tail + 1) % CAPACITY;
        --size;

        return result;
    }

    template<typename T, size_t CAPACITY>
    bool MessageQueue<T, CAPACITY>::isEmpty() const {
        return size == 0;
    }

    template<typename T, size_t CAPACITY>
    bool MessageQueue<T, CAPACITY>::isFull() const {
        return size == CAPACITY;
    }
}
