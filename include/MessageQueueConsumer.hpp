#pragma once

namespace messageQueue {
    template<typename Queue>
    class MessageQueueConsumer {
        Queue& queue;

        using valueType = typename Queue::valueType;

        void sendToProcessor(valueType message);

    public:
        explicit MessageQueueConsumer(Queue &queue);

        void operator()(std::stop_token st) {
            while (!st.stop_requested()) {
                if (auto data = queue.dequeue()) {
                    sendToProcessor(data.value());
                }
            }
        }
    };
    template<typename Queue>
    MessageQueueConsumer(Queue&) -> MessageQueueConsumer<Queue>;

    template<typename T, std::size_t N>
    MessageQueueConsumer(MessageQueue<T, N>&) -> MessageQueueConsumer<MessageQueue<T, N>>;


    template<typename Queue>
    void MessageQueueConsumer<Queue>::sendToProcessor(valueType message) {
        // TODO: Send this to something to calculate statistics;
    }

    template<typename Queue>
    MessageQueueConsumer<Queue>::MessageQueueConsumer(Queue &queue): queue(queue) {}

}
