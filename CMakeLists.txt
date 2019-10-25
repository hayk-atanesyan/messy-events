cmake_minimum_required(VERSION 3.10)
project(MessyEvents)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pthread")

include_directories(include)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_library(messy-events SHARED ${SOURCES} ${HEADERS})

install(TARGETS messy-events DESTINATION /usr/lib)

file(GLOB_RECURSE TEST_SOURCE_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
add_executable(test_boost ${TEST_SOURCE_FILES})
target_link_libraries(test_boost boost_unit_test_framework messy-events)