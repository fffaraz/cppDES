cmake_minimum_required(VERSION 3.14)
project(cppDES)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
  libcppdes
  include/cppdes/des.h
  include/cppdes/des3.h
  include/cppdes/des3cbc.h
  include/cppdes/descbc.h
  lib/des_key.h
  lib/des_lookup.h
  lib/des.cpp
  lib/des3.cpp
  lib/des3cbc.cpp
  lib/descbc.cpp)
target_include_directories(libcppdes PUBLIC include)

add_executable(cppDES src/main.cpp src/fileencryption.h src/fileencryption.cpp)
target_link_libraries(cppDES libcppdes)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(cppDESTest test/main.cpp)
target_link_libraries(cppDESTest libcppdes GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(cppDESTest)
