#include "DataProcessing/BidAskVolumeRatioTests.hpp"

#include <iostream>

namespace dataProcessing {
    void BidAskVolumeRatioTests::updateRatio() {
        ratio = bidVol / std::max(askVol, 0.000001L);
    }

    void BidAskVolumeRatioTests::update(double newBidQuantity, double newAskQuantity) {
        historicData.emplace_back(newBidQuantity, newAskQuantity);
        bidVol += newBidQuantity;
        askVol += newAskQuantity;

        if (historicData.size() > lookback) {
            auto [removingBidVol, removingAskVol] = historicData.front();
            historicData.pop_front();

            bidVol -= removingBidVol;
            askVol -= removingAskVol;
        }

        updateRatio();
    }

    BidAskVolumeRatioTests::BidAskVolumeRatioTests(const uint16_t lookback) : lookback{ lookback } {}

    void BidAskVolumeRatioTests::update(const TopOfBook &topOfBook) {
        update(topOfBook.getBestBid().getQuantity(), topOfBook.getBestAsk().getQuantity());

        std::cout << "Ratio -- " << ratio << '\n';
    }

    double BidAskVolumeRatioTests::getGreek() const {
        return ratio;
    }
}
