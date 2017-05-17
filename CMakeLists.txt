cmake_minimum_required(VERSION 3.7)
project(SmdComponents)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SOURCE_FILES main.cpp test.cpp Contour.cpp Contour.h HelpFunc.cpp HelpFunc.h)
add_executable(SmdComponents ${SOURCE_FILES})

target_link_libraries( SmdComponents ${OpenCV_LIBS} )


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

