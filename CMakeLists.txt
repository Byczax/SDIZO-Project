cmake_minimum_required(VERSION 3.17)
project(sdizo1)

set(CMAKE_CXX_STANDARD 20)

add_executable(sdizo1
        src/single_list.cpp
        src/DoubleList.cpp
        src/main.cpp
        src/DoubleList.h
        src/Array.cpp
        src/Array.h
        src/BinaryHeap.cpp
        src/BinaryHeap.h
        src/RedBlackTree.cpp
        src/RedBlackTree.h
        src/AVLTree.cpp src/AVLTree.h)