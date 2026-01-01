#include <gtest/gtest.h>
#include <stop_token>
#include "MessageQueue.hpp"

class MessageQueueTest : public testing::Test {
protected:
    messageQueue::MessageQueue<int, 10> queue;
    std::stop_source stopSource;
    std::stop_token token;

    void SetUp() override {
        token = stopSource.get_token();
    }
};

TEST_F(MessageQueueTest, shouldEnqueueAndDequeueSingleValue) {
    queue.enqueue(42);
    const int value = queue.dequeue(token).value();
    EXPECT_EQ(value, 42);
}
