cmake_minimum_required(VERSION 3.14)

# set the project name
project(ScalaCppAssignment)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR})

# add the executable
add_executable(ScalaCppAssignment
  parser.cpp
  main.cpp)
