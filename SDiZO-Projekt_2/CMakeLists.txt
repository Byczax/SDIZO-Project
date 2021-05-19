cmake_minimum_required(VERSION 3.19)
project(SDiZO_Projekt_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(SDiZO_Projekt_2
        src/main.cpp
        src/Essentials.cpp
        src/Essentials.h
        src/ManualTests.cpp
        src/ManualTests.h
        src/Prim.cpp
        src/Prim.h
        src/Kruskal.cpp
        src/Kruskal.h
        src/Dijkstra.cpp src/Dijkstra.h src/BellmanFord.cpp src/BellmanFord.h src/FordFulkerson.cpp src/FordFulkerson.h src/AutomatedTests.cpp src/AutomatedTests.h src/Matrix.cpp src/Matrix.h src/List.cpp src/List.h)