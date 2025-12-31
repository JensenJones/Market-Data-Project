#pragma once

namespace messageQueue {
    template<typename Queue>
    class MessageQueueConsumer {
        Queue& queue;

        using valueType = typename Queue::valueType;

        void sendToProcessor(std::optional<valueType> dataOptional);

    public:
        explicit MessageQueueConsumer(Queue &queue);

        void operator()(const std::stop_token& st) {
            while (!st.stop_requested()) {
                sendToProcessor(queue.dequeue());
            }
        }
    };
    template<typename Queue>
    MessageQueueConsumer(Queue&) -> MessageQueueConsumer<Queue>;

    template<typename T, std::size_t N>
    MessageQueueConsumer(MessageQueue<T, N>&) -> MessageQueueConsumer<MessageQueue<T, N>>;


    template<typename Queue>
    void MessageQueueConsumer<Queue>::sendToProcessor(std::optional<valueType> dataOptional) {
        if (dataOptional) {
            auto value = dataOptional.value();
            // TODO: Send this to something to calculate statistics;
        }
    }

    template<typename Queue>
    MessageQueueConsumer<Queue>::MessageQueueConsumer(Queue &queue): queue(queue) {}

}
