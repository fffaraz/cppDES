cmake_minimum_required(VERSION 3.14)
project(cppDES)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
  libcppdes
  include/cppdes/des.h
  include/cppdes/des3.h
  include/cppdes/descbc.h
  include/cppdes/fileencryption.h
  lib/des_key.h
  lib/des_lookup.h
  lib/des.cpp
  lib/des3.cpp
  lib/descbc.cpp
  lib/fileencryption.cpp)

target_include_directories(libcppdes PUBLIC include)

add_executable(cppDES src/main.cpp)
target_link_libraries(cppDES libcppdes)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(cppDESTest test/main.cpp)
target_link_libraries(cppDESTest libcppdes GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(cppDESTest)
