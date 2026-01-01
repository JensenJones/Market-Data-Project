#include <gtest/gtest.h>
#include <stop_token>
#include "MessageQueue.hpp"

class MessageQueueTest : public testing::Test {
protected:
    constexpr static size_t QUEUE_CAPACITY = 3;
    messageQueue::MessageQueue<int, QUEUE_CAPACITY> queue;
    std::stop_source stopSource;
    std::stop_token token;

    void SetUp() override {
        token = stopSource.get_token();
    }
};

TEST_F(MessageQueueTest, shouldEnqueueAndDequeueSingleValue) {
    queue.enqueue(22);
    const int value = queue.dequeue(token).value();
    EXPECT_EQ(value, 22);
}

TEST_F(MessageQueueTest, shouldEnqueueAndDequeueMultipleMessagesFIFO) {
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    EXPECT_EQ(queue.isFull(), true);

    auto first = queue.dequeue(token).value();
    auto second = queue.dequeue(token).value();
    auto third = queue.dequeue(token).value();

    EXPECT_EQ(first, 1);
    EXPECT_EQ(second, 2);
    EXPECT_EQ(third, 3);
}

TEST_F(MessageQueueTest, shouldBlockOrdersExceedingCapacity) {
    queue.enqueue(1);
    queue.enqueue(2);

}
