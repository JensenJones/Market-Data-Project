#pragma once
#include <string>

#include "Greek.hpp"
#include "../MessageHandling/TopOfBook.hpp"

namespace dataProcessing {
    class DataProcessor {
        std::string symbol;
        uint64_t latestUpdateId{};
        std::vector<std::unique_ptr<Greek>> greeks;

        void updateGreeks(const TopOfBook & topOfBook) const;

    public:
        void processData(const TopOfBook& topOfBook) const;

        void addGreek(std::unique_ptr<Greek> greek);
    };
}