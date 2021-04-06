cmake_minimum_required(VERSION 3.17)
project(sdizo1)

set(CMAKE_CXX_STANDARD 20)

add_executable(sdizo1 single_list.cpp DoubleList.cpp main.cpp DoubleList.h array.cpp array.h BinaryHeap.cpp BinaryHeap.h RedBlackTree.cpp RedBlackTree.h)