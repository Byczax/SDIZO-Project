#include <chrono>
#include <string>
#include <fstream>

#include "Essentials.h"

using std::string;

/**
 * Read value from file
 * @param filename
 * @return
 */
int *Essentials::getDataFromFile(const string &filename) {
    std::ifstream is(filename);
    int value;
    if (!(is >> value)) { throw; }
    auto data = new int[value + 1];
    unsigned int i = 1;
    data[0] = value;

    while (is >> value) {
        data[i] = value;
        ++i;
    }
    return data;
}

/**
 * Generate random value
 * @param amount
 * @return
 */
int *Essentials::randomData(int amount) {
    int *data_table = new int[amount + 1];
    data_table[0] = amount;
    for (int i = 1; i < amount + 1; ++i) {
        data_table[i] = rand() - rand();
    }
    return data_table;
}

int Essentials::randomValue() {
    return rand() - rand();
}

//-----------------------Time counter----------------------------------------------------------
// Only windows, need windows.h
/**
 * code fragment from https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
 * responsible for the preparation of QueryPerformanceCounter and methods for measuring time
 */
//double PCFreq = 0.0;
//__int64 CounterStart = 0;

/**
 * Start time counter
 */
//void StartCounter() {
//    LARGE_INTEGER li;
//    if (!QueryPerformanceFrequency(&li))
//        cout << "QueryPerformanceFrequency failed!\n";
//
//    PCFreq = double(li.QuadPart) / 1000.0;
//
//    QueryPerformanceCounter(&li);
//    CounterStart = li.QuadPart;
//}

/**
 * Stop time counter
 * @return
 */
//double GetCounter() {
//    LARGE_INTEGER li;
//    QueryPerformanceCounter(&li);
//    return double(li.QuadPart - CounterStart) / PCFreq;
//}

/**
 * Lambda to get runtime
 * @tparam T
 * @param i
 * @return
 */
//template<typename T>
//doubletool.Timer(T i) {
//    StartCounter();
//    i();
//    return GetCounter();
//}
//----------------------------------------------------------------------------------------------
