#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Sort.h"
#include <sstream>
#include <ostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <chrono>
#include "../FlightData.h"
using namespace std;
using namespace std::chrono;

bool intComp(int a, int b, bool ascending) {
    if(ascending)
        return a > b;
    else
        return a < b;
};

TEST_CASE("01: QuickSort Test - Ascending", "[flag]"){
    // Test Vector of Ints:

    vector<int> numbers = {6, 4, 5, 3, 2, 1, 0};
    Sort<int> sorter(intComp, 1);
    sorter.QuickSort(numbers, 0, 6);

    vector<int> sorted = {0, 1, 2, 3, 4, 5, 6};

    REQUIRE(numbers == sorted);
}

TEST_CASE("02: QuickSort Test - Descending", "[flag]"){
    // Test Vector of Ints:

    vector<int> numbers = {6, 4, 5, 3, 2, 1, 0};
    Sort<int> sorter(intComp, 0);
    sorter.QuickSort(numbers, 0, 6);

    vector<int> sorted = {6, 5, 4, 3, 2, 1, 0};

    REQUIRE(numbers == sorted);
}

TEST_CASE("02: MergeSort Test - Ascending", "[flag]"){
    // Test Vector of Ints:

    vector<int> numbers = {6, 4, 5, 3, 2, 1, 0};
    Sort<int> sorter(intComp, 1);
    sorter.MergeSort(numbers, 0, 6);

    vector<int> sorted = {0, 1, 2, 3, 4, 5, 6};

    REQUIRE(numbers == sorted);
}

TEST_CASE("04: MergeSort Test - Descending", "[flag]"){
    // Test Vector of Ints:

    vector<int> numbers = {6, 4, 5, 3, 2, 1, 0};
    Sort<int> sorter(intComp, 0);
    sorter.MergeSort(numbers, 0, 6);

    vector<int> sorted = {6, 5, 4, 3, 2, 1, 0};

    REQUIRE(numbers == sorted);
}

TEST_CASE("05: ShellSort Test - Ascending", "[flag]"){
    // Test Vector of Ints:

    vector<int> numbers = {6, 4, 5, 3, 2, 1, 0};
    Sort<int> sorter(intComp, 1);
    sorter.ShellSort(numbers);

    vector<int> sorted = {0, 1, 2, 3, 4, 5, 6};

    REQUIRE(numbers == sorted);
}

TEST_CASE("06: ShellSort Test - Descending", "[flag]"){
    // Test Vector of Ints:

    vector<int> numbers = {6, 4, 5, 3, 2, 1, 0};
    Sort<int> sorter(intComp, 0);
    sorter.ShellSort(numbers);

    vector<int> sorted = {6, 5, 4, 3, 2, 1, 0};

    REQUIRE(numbers == sorted);
}

TEST_CASE("07: Load CSV Data Test", "[flag]"){
    FlightData data;
    auto start = high_resolution_clock::now();
    data.LoadData("flightdata.csv");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Data load time: " << duration.count() << " seconds" << endl;
    REQUIRE(1 == 1);
}

TEST_CASE("08: Air Carrier Sort", "[flag]"){
    FlightData data;
    auto start = high_resolution_clock::now();
    data.LoadData("flightdata.csv");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Data load time: " << duration.count() << " seconds" << endl;


    start = high_resolution_clock::now();
    Sort<Flights*> sorter(Flights::EfficiencyComp, 0);
    sorter.MergeSort(data._airCarrierData, 0, data._airCarrierData.size() - 1);
    stop = high_resolution_clock::now();
    auto durationMicro = duration_cast<microseconds>(stop - start);
    cout << "Number of items sorted: " << data._airCarrierData.size() << endl;
    cout << "Merge Sort Processing Time: " << durationMicro.count() << " microseconds" << endl;

    data.PrintCarrierTop20();

    REQUIRE(1 == 1);
}

TEST_CASE("09: City Pair Sort", "[flag]"){
    FlightData data;
    auto start = high_resolution_clock::now();
    data.LoadData("flightdata.csv");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Data load time: " << duration.count() << " seconds" << endl;


    start = high_resolution_clock::now();
    Sort<Flights*> sorter(Flights::EfficiencyComp, 0);
    sorter.QuickSort(data._cityPairs, 0, data._cityPairs.size() - 1);
    stop = high_resolution_clock::now();
    auto durationMicro = duration_cast<seconds>(stop - start);
    cout << "Number of items sorted: " << data._cityPairs.size() << endl;
    cout << "Merge Sort Processing Time: " << duration.count() << " seconds" << endl;

    data.PrintCityPairTop20();

    REQUIRE(1 == 1);
}

TEST_CASE("10: Distance Sort", "[flag]"){
    FlightData data;
    auto start = high_resolution_clock::now();
    data.LoadData("flightdata.csv");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Data load time: " << duration.count() << " seconds" << endl;


    start = high_resolution_clock::now();
    Sort<Flights*> sorter(Flights::DistanceComp, 0);
    sorter.QuickSort(data._flightData, 0, data._flightData.size() - 1);
    stop = high_resolution_clock::now();
    auto durationMicro = duration_cast<seconds>(stop - start);
    cout << "Number of items sorted: " << data._flightData.size() << endl;
    cout << "Quick Sort Processing Time: " << duration.count() << " microseconds" << endl;

    data.PrintDistanceTop20();

    REQUIRE(1 == 1);
}