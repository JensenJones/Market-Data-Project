#include "../../include/DataProcessing/DataProcessor.hpp"


namespace dataProcessing {
    void DataProcessor::updateGreeks(const TopOfBook &topOfBook) const {
        for (const auto& greek : greeks) {
            greek->update(topOfBook);
        }
    }

    void DataProcessor::processData(const TopOfBook& topOfBook) const {
        if (topOfBook.getUpdateId() <= latestUpdateId) return;

        updateGreeks(topOfBook);
    }

    void DataProcessor::addGreek(std::unique_ptr<Greek> greek) {
        greeks.emplace_back(std::move(greek));
    }
}