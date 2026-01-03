#pragma once
#include "DataProcessing/DataProcessor.hpp"

namespace messageQueue {
    template<typename Queue>
    class MessageQueueConsumer {
        using DataProcessor = dataProcessing::DataProcessor;
        Queue& queue;
        DataProcessor& dataProcessor;
        inline static std::mutex printingMutex{};

        using valueType = Queue::valueType;

        void sendToProcessor(std::optional<valueType> dataOptional);


    public:
        explicit MessageQueueConsumer(Queue &queue, DataProcessor& dataProcessor);

        void operator()(const std::stop_token& stopToken);
    };

    template<typename Queue>
    MessageQueueConsumer<Queue>::MessageQueueConsumer(Queue &queue, DataProcessor& dataProcessor) :
        queue(queue),
        dataProcessor(dataProcessor) {
    }

    template<typename Queue>
    void MessageQueueConsumer<Queue>::sendToProcessor(std::optional<valueType> dataOptional) {
        if (dataOptional) {
            std::unique_lock lock(printingMutex);
            dataProcessor.processData(dataOptional.value());
        }
    }

    template<typename Queue>
    void MessageQueueConsumer<Queue>::operator()(const std::stop_token &stopToken) {
        while (!stopToken.stop_requested()) {
            sendToProcessor(queue.dequeue(stopToken));
        }
    }
}
