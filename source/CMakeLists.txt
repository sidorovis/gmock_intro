add_subdirectory(netlib)
set(PROGRAM mylib)
add_library(${PROGRAM} STATIC mylib.cpp)
