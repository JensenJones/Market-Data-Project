#pragma once
#include <iosfwd>
#include <concepts>
#include <iostream>
#include <print>

namespace messageQueue {
    template <typename T>
    concept Printable = requires(std::ostream& outputStream, const T& templateInstance) {
        { outputStream << templateInstance } -> std::same_as<std::ostream&>;
    };

    template<typename T>
    class MessageQueue {
    public:
        void enqueue(T message) {
            std::cout << message << '\n';
        }

        void enqueue(T message) requires (!Printable<T>) {
            std::cout << "Message type is not printable. Message has type: "
                      << typeid(message).name() << "\n";
        }
    };
}





