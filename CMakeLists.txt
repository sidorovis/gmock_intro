cmake_minimum_required(VERSION 3.3)

add_definitions("-std=c++11")

add_subdirectory(source)

SET(PROGRAM testgmock_unittests)

enable_testing()

add_subdirectory(googletest)

FILE(GLOB SOURCES_TESTS
    source_tests/*.hpp
    source_tests/*.cpp
    )

set(SOURCES ${SOURCES_TESTS} ${GTEST_SOURCES} ${GTEST_ALL_HEADERS})
add_executable(${PROGRAM} ${SOURCES})

find_package(Threads QUIET REQUIRED)
target_link_libraries( ${PROGRAM} PRIVATE ${CMAKE_THREAD_LIBS_INIT} )

target_link_libraries(${PROGRAM} PRIVATE gtest gmock mylib)
target_include_directories(${PROGRAM} PRIVATE "source")

add_test(${PROGRAM} ${PROGRAM})
