cmake_minimum_required(VERSION 3.15)
project(
  spiik
  LANGUAGES C
)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SRCS src/*.c)

add_executable(${PROJECT_NAME} ${SRCS})
