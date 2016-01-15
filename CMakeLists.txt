cmake_minimum_required(VERSION 3.3)
project(PredictiveText)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.c trieStructure.c trieStructure.h textio.c textio.h)
add_executable(PredictiveText ${SOURCE_FILES})