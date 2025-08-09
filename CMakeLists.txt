cmake_minimum_required(VERSION 3.31.6)

project(Market-Data-Project)

set(CMAKE_CXX_STANDARD 23)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Werror -Wpedantic -Wshadow -Wconversion")
string(APPEND CMAKE_CXX_FLAGS " -Wnull-dereference -Wdouble-promotion")
string(APPEND CMAKE_CXX_FLAGS " -flto -march=native -g")

find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS headers)

set(SOURCES
    src/main.cpp
    src/WebSocketManager.cpp
)

add_executable(market_data ${SOURCES})

target_include_directories(market_data
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(market_data
    PRIVATE
        Boost::Boost
        OpenSSL::SSL
)