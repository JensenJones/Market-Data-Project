#pragma once
#include <deque>

#include "Greek.hpp"

namespace dataProcessing {
    class BidAskVolumeRatioTests : public Greek {
        uint16_t lookback;
        std::deque<std::pair<double, double>> historicData;
        double ratio{};
        long double bidVol{};
        long double askVol{};

        void updateRatio();

        void update(double newBidQuantity, double newAskQuantity);
    public:
        explicit BidAskVolumeRatioTests(uint16_t lookback);
        void update(const TopOfBook& topOfBook) override;

        [[nodiscard]] double getGreek() const override;
    };
}