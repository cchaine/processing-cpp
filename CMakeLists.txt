cmake_minimum_required(VERSION 3.0)
project(processing-cpp)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules")

set(SRC src/sketch.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
add_library(processing-cpp STATIC ${SRC})

find_package(OpenGL)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SOIL REQUIRED)

set(INCLUDE_DIRS ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${SOIL_INCLUDE_LIBS} ${OPENGL_INCLUDE_DIRS} "include")
include_directories(${INCLUDE_DIRS})

set(LIBS glfw ${GLEW_LIBRARIES} ${PNG_LIBRARIES} ${SOIL_LIBRARIES} ${OPENGL_LIBRARY})
target_link_libraries(processing-cpp ${LIBS})

install(TARGETS processing-cpp DESTINATION "lib")
install(FILES "include/sketch.h" DESTINATION "include")
