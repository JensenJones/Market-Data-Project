#include "DataProcessing/BidAskVolumeRatioTests.hpp"

#include <gtest/gtest.h>

class BidAskVolumeRatioTest : public testing::Test {
protected:
    constexpr static uint16_t LOOKBACK{5};
    dataProcessing::BidAskVolumeRatioTests subject{LOOKBACK};

    void SetUp() override {
    }
};

TEST_F(BidAskVolumeRatioTest, shouldReturnZeroForInitialRatio) {
    const auto ratio = subject.getGreek();

    ASSERT_EQ(ratio, 0.0);
}

TEST_F(BidAskVolumeRatioTest, shouldReturnARatioOnceUpdatedLookbackTimes) {
    double totalBidQuanty{};
    double totalAskQuantity{};

    for (int i = 0; i < LOOKBACK; ++i) {
        double newBidQuantity = 1;
        double newAskQuantity = 2 + i;

        subject.update(TopOfBook(i, "BTC/USDT",
            Order(10, newBidQuantity),
            Order(11, newAskQuantity)));

        totalBidQuanty += newBidQuantity;
        totalAskQuantity += newAskQuantity;

        const auto ratio = subject.getGreek();
        ASSERT_NEAR(ratio, totalBidQuanty / totalAskQuantity);
    }
}

TEST_F(BidAskVolumeRatioTest, shouldFIFOEvictAndUpdateRatioAcordingly) {
    double windowBidQuantity{};
    std::vector<double> bidQuantitiesAdded{};
    double windowAskQuantity{};
    std::vector<double> askQuantitiesAdded{};

    for (int i = 0; i < LOOKBACK; ++i) {
        constexpr double newBidQuantity = 1;
        const double newAskQuantity = 2 + i;

        subject.update(TopOfBook(i, "BTC/USDT",
            Order(10, newBidQuantity),
            Order(11, newAskQuantity)));

        windowBidQuantity += newBidQuantity;
        bidQuantitiesAdded.push_back(newBidQuantity);
        windowAskQuantity += newAskQuantity;
        askQuantitiesAdded.push_back(newAskQuantity);
    }

    for (int i = 0; i < bidQuantitiesAdded.size(); ++i) {
        constexpr double newBidQuantity = 1;
        constexpr double newAskQuantity = 1;
        subject.update(TopOfBook(i, "BTC/USDT",
        Order(10, newBidQuantity),
        Order(11, newAskQuantity)));

        windowBidQuantity += newBidQuantity;
        windowAskQuantity += newAskQuantity;
        windowBidQuantity -= bidQuantitiesAdded[i];
        windowAskQuantity -= askQuantitiesAdded[i];

        const auto ratio = subject.getGreek();
        ASSERT_NEAR(ratio, windowBidQuantity / windowAskQuantity);
    }
}
