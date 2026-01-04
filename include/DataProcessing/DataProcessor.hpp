#pragma once
#include <string>
#include <utility>

#include "Greeks/Greek.hpp"
#include "../MessageHandling/TopOfBook.hpp"
#include "Greeks/GreekName.hpp"

namespace dataProcessing {

    template<typename Queue>
    concept EnqueueQueue = requires(Queue& q) {
        q.enqueue(std::declval<typename Queue::valueType>());
    };

    template<EnqueueQueue Queue>
    class DataProcessor {
        const std::string symbol;
        uint64_t latestUpdateId{};
        std::unordered_map<GreekName, std::unique_ptr<Greek>> greeks;
        const Queue& tradeQueue;

        using valueType = Queue::valueType;

        void updateGreeks(const TopOfBook & topOfBook) const;

        [[nodiscard]] double calcBidAmount() const;
        [[nodiscard]] double calcAskAmount() const;

        void checkConditions() const;
    public:
        DataProcessor(std::string symbol, Queue& tradeQueue);
        void processData(const TopOfBook& topOfBook) const;

        void addGreek(GreekName greekName, std::unique_ptr<Greek> greek);
    };

    template<EnqueueQueue Queue>
    DataProcessor<Queue>::DataProcessor(std::string symbol, Queue &tradeQueue) :
        symbol(std::move(symbol)), tradeQueue(tradeQueue) {
    }

    template<EnqueueQueue Queue>
    void DataProcessor<Queue>::updateGreeks(const TopOfBook &topOfBook) const {
        for (const auto &greek: greeks | std::views::values) {
            greek->update(topOfBook);
        }
    }

    template<EnqueueQueue Queue>
    double DataProcessor<Queue>::calcBidAmount() const {
        return 0.0;
    }

    template<EnqueueQueue Queue>
    double DataProcessor<Queue>::calcAskAmount() const {
        return 0.0;
    }

    template<EnqueueQueue Queue>
    void DataProcessor<Queue>::checkConditions() const {
        // if (calcBidAmount()) {
        //     // TODO: place bid order
        //     tradeQueue.enqueue(Order());
        // } else {
        //     if (calcAskAmount()) {
        //         // TODO: place ask order
        //         tradeQueue.enqueue(Order());
        //     }
        // }
    }

    template<EnqueueQueue Queue>
    void DataProcessor<Queue>::processData(const TopOfBook& topOfBook) const {
        if (topOfBook.getUpdateId() <= latestUpdateId) return;

        updateGreeks(topOfBook);
    }

    template<EnqueueQueue Queue>
    void DataProcessor<Queue>::addGreek(const GreekName greekName, std::unique_ptr<Greek> greek) {
        greeks[greekName] = std::move(greek);
    }
}
