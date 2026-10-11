cmake_minimum_required(VERSION 3.16)
project(IndustrialSensorBackend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(point_processing src/point_processing.cpp src/message_parser.cpp)
target_include_directories(point_processing PUBLIC src)
target_compile_options(point_processing PRIVATE -Wall -Wextra -Wpedantic)

add_executable(sensor_backend src/main.cpp)
target_link_libraries(sensor_backend PRIVATE point_processing)
target_compile_options(sensor_backend PRIVATE -Wall -Wextra -Wpedantic)

include(FetchContent)
FetchContent_declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable( point_processing_tests 
                tests/point_processing_tests.cpp
                tests/message_parser_tests.cpp)
target_link_libraries(point_processing_tests PRIVATE point_processing GTest::gtest_main)
target_compile_options(point_processing_tests PRIVATE -Wall -Wextra -Wpedantic)

include(GoogleTest)
gtest_discover_tests(point_processing_tests)

add_executable(tcp_server src/server_main.cpp)
target_compile_options(tcp_server PRIVATE -Wall -Wextra -Wpedantic)