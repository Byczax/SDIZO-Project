#pragma once

#include <string>
#include <chrono>
#include "Matrix.h"
#include "List.h"

using namespace std::chrono;
using std::string;

/**
 * Measuring time function
 * @tparam T
 * @param i
 * @return
 */
template<typename T>
long Timer(T i) {
    auto start = high_resolution_clock::now();// Start the counter
    i();// our function
    auto end = high_resolution_clock::now();// Get edgeWeight after executing function
    auto duration = end - start;// get time difference
    auto elapsed_time = duration_cast<nanoseconds>(duration).count();// calculate time
    return static_cast<long>(elapsed_time);// Return executing time in nanoseconds
}

class Essentials {

public:
    // Get data from given filename
    static void
    getDataFromFile(const string &filename, Matrix *&matrixGraph, AdjacencyList *&matrixList, bool directed);

    // generate random edgeWeight between minimum and maximum
    static int randomNumber(int minimum, int maximum);

    // generate random graph for algorithms
    static void
    generateRandomGraph(int vertices, int density, Matrix *&matrixGraph, AdjacencyList *&listGraph, bool directed);
};