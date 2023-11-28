#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Sort.h"
#include <sstream>
#include <ostream>
#include <chrono>
#include <vector>
using namespace std;

bool gt(int a, int b) {
    return a > b;
};

bool lt(int a, int b) {
    return a < b;
};

TEST_CASE("01: QuickSort Test - Ascending", "[flag]"){
    // Test Vector of Ints:

    vector<int> numbers = {6, 4, 5, 3, 2, 1, 0};
    Sort<int> sorter(gt);
    sorter.QuickSort(numbers, 0, 6);

    vector<int> sorted = {0, 1, 2, 3, 4, 5, 6};

    REQUIRE(numbers == sorted);
}


TEST_CASE("02: QuickSort Test - Descending", "[flag]"){
    // Test Vector of Ints:

    vector<int> numbers = {6, 4, 5, 3, 2, 1, 0};
    Sort<int> sorter(lt);
    sorter.QuickSort(numbers, 0, 6);

    vector<int> sorted = {6, 5, 4, 3, 2, 1, 0};

    REQUIRE(numbers == sorted);
}
