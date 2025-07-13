cmake_minimum_required(VERSION 3.20)
project(httpcpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(httpcpp)

target_sources(httpcpp
    PRIVATE
        src/Socket.cpp
        src/HttpClient.cpp
        src/HttpResponse.cpp
        src/HttpResponseParser.cpp
)

target_include_directories(httpcpp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_executable(example src/main.cpp)
target_link_libraries(example httpcpp)

# Add tests
enable_testing()

find_package(GTest REQUIRED)

add_executable(httpcpp_tests tests/HttpResponseParserTest.cpp)
target_link_libraries(httpcpp_tests httpcpp GTest::gtest GTest::gtest_main)
