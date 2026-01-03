#pragma once
#include "DataProcessing/DataProcessor.hpp"

namespace messageQueue {
    template<typename Queue>
    concept QueueConcept =
        requires(Queue q, std::stop_token st) {
            // Must expose valueType
            typename Queue::valueType;

            // Must support dequeue(stop_token) returning std::optional<valueType>
            { q.dequeue(st) } -> std::same_as<std::optional<typename Queue::valueType>>;
        };

    template<QueueConcept Queue>
    class MessageQueueConsumer {
        using DataProcessor = dataProcessing::DataProcessor<Queue>;
        Queue& queue;
        DataProcessor& dataProcessor;
        inline static std::mutex printingMutex{};

        using valueType = Queue::valueType;

        void sendToProcessor(std::optional<valueType> dataOptional);


    public:
        explicit MessageQueueConsumer(Queue &queue, DataProcessor& dataProcessor);

        void operator()(const std::stop_token& stopToken);
    };

    template<QueueConcept Queue>
    MessageQueueConsumer<Queue>::MessageQueueConsumer(Queue &queue, DataProcessor& dataProcessor) :
        queue(queue),
        dataProcessor(dataProcessor) {
    }

    template<QueueConcept Queue>
    void MessageQueueConsumer<Queue>::sendToProcessor(std::optional<valueType> dataOptional) {
        if (dataOptional) {
            std::unique_lock lock(printingMutex);
            dataProcessor.processData(dataOptional.value());
        }
    }

    template<QueueConcept Queue>
    void MessageQueueConsumer<Queue>::operator()(const std::stop_token &stopToken) {
        while (!stopToken.stop_requested()) {
            sendToProcessor(queue.dequeue(stopToken));
        }
    }
}
