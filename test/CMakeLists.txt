cmake_minimum_required(VERSION 3.14)
project(ZeroInfinity_Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  interval_test
  src/main.cpp
)

target_include_directories(interval_test PRIVATE src)

target_link_libraries(
  interval_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(interval_test)
