cmake_minimum_required(VERSION 3.0)
project(processing-cpp)

set(SRC src/core/main.cpp
src/core/PCFunctions.h
src/core/PCFunctions.cpp

src/core/PCQuad.h
src/core/PCQuad.cpp

src/core/PCTriangle.h
src/core/PCTriangle.cpp

src/core/PCShape.h
src/core/PCShape.cpp

src/core/PCShaderProgram.h
src/core/PCShaderProgram.cpp

src/core/PCSketch.h
src/core/PCSketch.cpp

src/test/Sketch.h
src/test/Sketch.cpp

src/core/Settings.h

src/core/shader.frag
src/core/shader.vert

src/PImage.h
src/PImage.cpp
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
add_executable(sketch.o ${SRC})

find_package(OpenGL)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SOIL REQUIRED)

set(INCLUDE_DIRS ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${SOIL_INCLUDE_LIBS} ${OPENGL_INCLUDE_DIRS})
include_directories(${INCLUDE_DIRS})

set(LIBS glfw ${GLEW_LIBRARIES} ${PNG_LIBRARIES} ${SOIL_LIBRARIES} ${OPENGL_LIBRARY})

target_link_libraries(sketch.o ${LIBS})
