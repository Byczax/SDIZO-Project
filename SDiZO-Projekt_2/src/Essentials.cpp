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

