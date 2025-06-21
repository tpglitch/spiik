cmake_minimum_required(VERSION 3.15)
project(spiik)

file(GLOB_RECURSE SRCS src/*.c)

add_executable(${PROJECT_NAME} ${SRCS})
