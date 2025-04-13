cmake_minimum_required(VERSION 3.20.0)

project(large_integer_arithmetic)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GTEST_ROOT $ENV{HOME}/gtest)
link_directories(${GTEST_ROOT}/lib)

add_executable(large_integer_arithmetic "src/test.cpp")

target_link_libraries(large_integer_arithmetic gtest gtest_main)

target_include_directories(large_integer_arithmetic PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${GTEST_ROOT}/include
)
