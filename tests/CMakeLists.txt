cmake_minimum_required(VERSION 3.20)

include(FetchContent)
FetchContent_Declare(
    ut
    GIT_REPOSITORY https://github.com/boost-ext/ut.git
    GIT_SHALLOW TRUE
    GIT_TAG v2.3.1
)
FetchContent_MakeAvailable(ut)

add_library(test_common INTERFACE
    MockSocket.hpp
)
target_include_directories(test_common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

function(create_test SRC)
    get_filename_component(NAME ${SRC} NAME_WLE)
    add_executable(${NAME} ${SRC})
    target_link_libraries(${NAME} PRIVATE Boost::ut httpcpp test_common)
    target_compile_options(${NAME} PRIVATE "-fsanitize=undefined,address")
    target_link_options(${NAME} PRIVATE "-fsanitize=undefined,address")
    add_test(NAME ${NAME} COMMAND ${NAME})
endfunction()

create_test(HttpResponseParserTest.cpp)
create_test(HttpClientTest.cpp)
create_test(SocketTest.cpp)


