#pragma once

#include <string>

using namespace std::chrono;

/**
 * MEasuring time function
 * @tparam T
 * @param i
 * @return
 */
template<typename T>
double Timer(T i) {
    auto start = high_resolution_clock::now();// Start the counter
    i();// our function
    auto end = high_resolution_clock::now();// Get value after executing function
    auto duration = end - start;// get time difference
    auto elapsed_time = duration_cast<nanoseconds>(duration).count();// calculate time
    return elapsed_time;// Return executing time in nanoseconds
}

class Essentials {

public:
    // Get data from given filename
    static int *getDataFromFile(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &filename);

    // random data generator, file emulation
    static int *randomData(int amount);

    // return random value [-int, int]
    static int randomValue();
};