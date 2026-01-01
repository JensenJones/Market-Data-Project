enable_testing()

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(MessageQueueTests
        MessageQueueTests.cpp
)

target_link_libraries(MessageQueueTests
        PRIVATE
        market_data_lib
        GTest::gtest
        GTest::gtest_main
        Threads::Threads
)

target_include_directories(MessageQueueTests
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

add_test(NAME MessageQueueTests COMMAND MessageQueueTests)
