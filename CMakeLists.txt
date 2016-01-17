cmake_minimum_required(VERSION 3.3)
project(PredictiveText)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror")

set(SOURCE_FILES main.c trieStructure.c trieStructure.h words.txt)
add_executable(PredictiveText ${SOURCE_FILES})