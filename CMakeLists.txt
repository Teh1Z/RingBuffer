cmake_minimum_required(VERSION 3.21.1)
project(RingBuffer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RingBuffer
        ringbuffer.h
)
