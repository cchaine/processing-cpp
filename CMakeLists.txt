cmake_minimum_required(VERSION 3.0)
project(processing-cpp)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules")

set(SRC src/psketch.cpp
        src/pshader.cpp
        src/pquad.cpp
        src/pcircle.cpp
	src/pline.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
add_library(processing-cpp SHARED ${SRC})

find_package(OpenGL)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SOIL REQUIRED)
set(INCLUDE_DIRS ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${SOIL_INCLUDE_LIBS} ${OPENGL_INCLUDE_DIRS} "include")
set(LIBRARIES glfw ${GLEW_LIBRARIES} ${PNG_LIBRARIES} ${SOIL_LIBRARIES} ${OPENGL_LIBRARY})

include_directories(${INCLUDE_DIRS})
target_link_libraries(processing-cpp ${LIBRARIES})

install(TARGETS processing-cpp DESTINATION "lib")
install(FILES "include/pline.h" "include/shaders/line.vert" "include/shaders/line.frag" "include/psketch.h" "include/pcircle.h" "include/shaders/point.frag" "include/shaders/point.vert" "include/pquad.h" "include/pshader.h" "include/shaders/main.vert" "include/shaders/main.frag" DESTINATION "include/processing-cpp")
