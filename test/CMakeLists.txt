cmake_minimum_required(VERSION 3.0)
project(processing-cpp-test)

set(SRC src/main.cpp)

include_directories(include /usr/local/include)
add_executable(processing-cpp-test ${SRC})
target_link_libraries(processing-cpp-test "/usr/local/lib/libprocessing-cpp.dylib")
