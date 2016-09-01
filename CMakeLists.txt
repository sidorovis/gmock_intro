cmake_minimum_required(VERSION 3.3)

if( WIN32 )
    add_definitions( -D_SCL_SECURE_NO_WARNINGS )
    add_definitions( -D_CRT_SECURE_NO_WARNINGS )
    add_definitions( -D_WIN32_WINNT=0x0501 )
    set(CMAKE_C_FLAGS_DEBUG_INIT "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
    set(CMAKE_C_FLAGS_MINSIZEREL_INIT     "/MT /O1 /Ob1 /D NDEBUG")
    set(CMAKE_C_FLAGS_RELEASE_INIT        "/MT /O2 /Ob2 /D NDEBUG")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "/MT /Zi /O2 /Ob1 /D NDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
    set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "/MT /O1 /Ob1 /D NDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE_INIT        "/MT /O2 /Ob2 /D NDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "/MT /Zi /O2 /Ob1 /D NDEBUG")
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa /wd4373") 
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
    endforeach(flag_var)
else()
    add_definitions("-std=c++11")
endif( WIN32 )

option(BUILD_GMOCK "Please build GMock" ON)
option(BUILD_GTEST "Please build GTest" ON)
add_subdirectory(googletest)


add_subdirectory(source)

SET(PROGRAM testgmock_unittests)

enable_testing()


FILE(GLOB SOURCES_TESTS
    source_tests/*.hpp
    source_tests/*.cpp
    )

set(SOURCES ${SOURCES_TESTS} ${GTEST_SOURCES} ${GTEST_ALL_HEADERS})
add_executable(${PROGRAM} ${SOURCES})

find_package(Threads QUIET REQUIRED)
target_link_libraries( ${PROGRAM} PRIVATE ${CMAKE_THREAD_LIBS_INIT} )

target_link_libraries(${PROGRAM} PRIVATE gtest gtest_main gmock mathlib netlib)
target_include_directories(${PROGRAM} PRIVATE "source")

add_test(${PROGRAM} ${PROGRAM})
