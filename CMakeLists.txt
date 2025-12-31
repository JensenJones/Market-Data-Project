cmake_minimum_required(VERSION 3.31.6)

project(Market-Data-Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

#string(APPEND CMAKE_CXX_FLAGS " -Wall -Werror -Wpedantic -Wshadow -Wconversion")
#string(APPEND CMAKE_CXX_FLAGS " -Wnull-dereference -Wdouble-promotion")
string(APPEND CMAKE_CXX_FLAGS " -march=native -g") # may need -pthread

find_package(OpenSSL CONFIG REQUIRED)

find_package(Boost REQUIRED COMPONENTS headers)

set(SOURCES
        src/WebSocketClient.cpp
        src/MarketDataHandler.cpp
        include/MarketDataHandler.hpp
        include/MarketDepthMessage.hpp
        include/Order.hpp
        src/Order.cpp
        src/MarketDepthMessage.cpp
        include/OrderFactory.hpp
        src/OrderFactory.cpp
        include/TopOfBook.hpp
        src/TopOfBook.cpp
        include/MessageQueue.hpp
        include/MessageQueueConsumer.hpp
)

add_executable(market_data ${SOURCES})

target_link_libraries(market_data
        PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
)

target_include_directories(market_data
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)