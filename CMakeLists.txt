cmake_minimum_required(VERSION 3.14)

project(ScalaExercise)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR})

add_library(ScalaExerciseCore
  parser.cpp
  solver.cpp
  )

add_executable(ScalaExercise
  main.cpp)

add_executable(ScalaExerciseTest
  test.cpp)

target_link_libraries( ScalaExercise ScalaExerciseCore )
target_link_libraries( ScalaExerciseTest ScalaExerciseCore )
