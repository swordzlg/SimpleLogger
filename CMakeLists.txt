cmake_minimum_required (VERSION 2.8.11)

project(SimpleLogger)

set(SOURCE_FILE
SimpleLogger/SimpleLogger.h
SimpleLogger/SimpleLogger.cpp
test/test.cpp
)

include_directories(SimpleLogger)

add_executable(SimpleLogger ${SOURCE_FILE})

set(EXECUTABLE_OUTPUT_PATH bin)
