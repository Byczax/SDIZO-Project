#pragma once

#include <string>
//template<typename T>


template<typename T>
double Timer(T i) {
    auto start = std::chrono::high_resolution_clock::now();// Start the counter
    i();// our function
    auto end = std::chrono::high_resolution_clock::now();// Get value after executing function
    auto duration = end - start;// get time difference
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();// calculate time
    return elapsed_time;// Return executing time in nanoseconds
}

class Essentials {

public:

    static int *getDataFromFile(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &filename);

    static int *randomData(int amount);

    static int randomValue();
};
