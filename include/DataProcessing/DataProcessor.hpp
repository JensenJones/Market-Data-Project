#pragma once
#include <string>
#include <utility>

#include "Greek.hpp"
#include "../MessageHandling/TopOfBook.hpp"

namespace dataProcessing {
    template<typename Queue>
    concept QueueConcept = requires(Queue q) {
            typename Queue::valueType;
            q.enqueue(Queue::valueType);
    };

    template<QueueConcept Queue>
    class DataProcessor {
        std::string symbol;
        uint64_t latestUpdateId{};
        std::vector<std::unique_ptr<Greek>> greeks;
        Queue& tradeQueue;

        void updateGreeks(const TopOfBook & topOfBook) const;

        [[nodiscard]] bool calcBidAmount() const;
        [[nodiscard]] bool calcAskAmount() const;

        void checkConditions() const;
    public:
        DataProcessor(std::string symbol, Queue& tradeQueue);
        void processData(const TopOfBook& topOfBook) const;

        void addGreek(std::unique_ptr<Greek> greek);
    };

    template<QueueConcept Queue>
    DataProcessor<Queue>::DataProcessor(std::string symbol, Queue &tradeQueue) :
        symbol(std::move(symbol)), tradeQueue(tradeQueue) {
    }

    template<QueueConcept Queue>
    void DataProcessor<Queue>::updateGreeks(const TopOfBook &topOfBook) const {
        for (const auto& greek : greeks) {
            greek->update(topOfBook);
        }
    }

    template<QueueConcept Queue>
    void DataProcessor<Queue>::checkConditions() const {
        if (calcBidAmount()) {
            // TODO: place bid order
            tradeQueue.enqueue();
        } else {
            if (calcAskAmount()) {
                // TODO: place ask order
            }
        }
    }

    template<QueueConcept Queue>
    void DataProcessor<Queue>::processData(const TopOfBook& topOfBook) const {
        if (topOfBook.getUpdateId() <= latestUpdateId) return;

        updateGreeks(topOfBook);
    }

    template<QueueConcept Queue>
    void DataProcessor<Queue>::addGreek(std::unique_ptr<Greek> greek) {
        greeks.emplace_back(std::move(greek));
    }
}