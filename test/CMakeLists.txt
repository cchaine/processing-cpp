cmake_minimum_required(VERSION 3.0)
project(processing-cpp-test)

set(SRC src/main.cpp
        src/sketch.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
include_directories(include /usr/local/include /usr/local/include/processing-cpp)
add_executable(processing-cpp-test ${SRC})
if(APPLE)
	target_link_libraries(processing-cpp-test "/usr/local/lib/libprocessing-cpp.dylib")
elseif(UNIX)
	target_link_libraries(processing-cpp-test "/usr/local/lib/libprocessing-cpp.so")
endif(APPLE)
