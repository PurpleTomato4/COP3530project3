/** COP3530 Project 3 - Airline Sorter 1000
 ** University of Florida - Fall 2023
 ** Authors: Jack Goldstein, Benjamin Uppgard, Ryan Wilson
 ** Date: 12/07/2023
 ** Description: This command line program imports T100-Domestic Segment data
 **              from the USDOT Bureau of Transportation Statistics. A sample
 **              dataset downloaded 10/27/2023 is used. The user is provided
 **              with tools to analyze the data in three ways:
 **                1) Sort the data by Air Carrier efficiency.
 **                2) Sort the data by Route efficiency.
 **                3) Sort the data by Route length.
 **              There user is allowed to choose from a list of sorting
 **              algorithms to use and specify sort order. After sorting, the
 **              program prints the top 20 results to the command line along
 **              with performance data of the search operations.
 **/

#include <iostream>
#include <string>
#include <vector>
#include "Flights.h"
#include "Sort.h"
#include "FlightData.h"
using namespace std;
using namespace std::chrono;

bool validateSelection(string userInput, int lowRange, int highRange);
steady_clock::time_point startTimer();
int elapsedMillis(steady_clock::time_point start);
int elapsedMicros(steady_clock::time_point start);

int main() {

    cout << "Welcome to the Airline Sorter 1000." << endl << endl;

    // Load the database
    cout << "Loading flight database..." << endl;
    string filename = "flightdata.csv";
    FlightData data;
    auto timer = startTimer();
    data.LoadData(filename);
    int loadTime = elapsedMillis(timer);
    cout << "Success! Loaded \"" << filename << "\" in " << loadTime
         << " milliseconds." << endl << endl;

    // Get user input, process data, print results
    while (true) {
        // Get analysis type
        int analysisType;
        while(true) {
            cout << "What would you like to sort?" << endl << endl;
            cout << "1. Air Carriers by Efficiency (Passengers/Available Seats)"
                 << endl;
            cout << "2. Routes by Efficiency (Passengers/Available Seats)"
                 << endl;
            cout << "3. All Flights by Distance" << endl;
            cout << "0. Exit" << endl << endl;

            string input;
            cin >> input;
            cout << endl;
            if (!validateSelection(input, 0, 3))
                cout << "Invalid selection. Please try again." << endl << endl;
            else {
                analysisType = stoi(input);
                break;
            }
        }

        // Exit on "0"
        if (analysisType == 0) {
            cout << "Airline Sorter 1000 logging off. Goodbye." << endl;
            break;
        }

        // Set sort comparison function
        Sort<Flights *> sorter;
        vector<Flights *> *source = nullptr;
        if (analysisType == 1) {
            source = &data._airCarrierData;
            sorter.SetSortFunction(Flights::EfficiencyComp);
        } else if (analysisType == 2) {
            source = &data._cityPairs;
            sorter.SetSortFunction(Flights::EfficiencyComp);
        } else if (analysisType == 3) {
            source = &data._flightData;
            sorter.SetSortFunction(Flights::DistanceComp);
        }

        // Get sort type
        int sortOption;
        while(true) {
            cout << "How would you like to sort the data?" << endl << endl;
            cout << "1. Sort using MergeSort" << endl;
            cout << "2. Sort using ShellSort" << endl;
            cout << "3. Sort using QuickSort" << endl;
            cout << "4. Compare All Sorting Algorithms" << endl;
            cout << "0. Exit" << endl << endl;

            string input;
            cin >> input;
            cout << endl;
            if (!validateSelection(input, 0, 4))
                cout << "Invalid selection. Please try again." << endl << endl;
            else {
                sortOption = stoi(input);
                break;
            }
        }

        // Exit on "0"
        if (sortOption == 0) {
            cout << "Airline Sorter 1000 logging off. Goodbye." << endl;
            break;
        };

        // Get sort direction
        int direction;
        while (true) {
            cout << "In what order would you like to sort?" << endl << endl;
            cout << "1. Ascending" << endl;
            cout << "2. Descending" << endl << endl;
            string input;
            cin >> input;
            cout << endl;
            if (!validateSelection(input, 1, 2))
                cout << "Invalid selection. Please try again." << endl << endl;
            else {
                direction = stoi(input);
                break;
            }
        }

        bool ascending;
        if (direction == 1)
            ascending = 1;
        else
            ascending = 0;

        sorter.SetSortDirection(ascending);

        // MergeSort
        if (sortOption == 1) {
            timer = startTimer();
            sorter.MergeSort(*source, 0, source->size() - 1);
            int sortTime = elapsedMicros(timer);
            cout << "Sorted " << source->size() << " elements in " << sortTime
                 << " microseconds using MergeSort" << endl << endl;
        }
        // ShellSort
        else if (sortOption == 2) {
            timer = startTimer();
            sorter.ShellSort(*source);
            int sortTime = elapsedMicros(timer);
            cout << "Sorted " << source->size() << " elements in " << sortTime
                 << " microseconds using ShellSort" << endl << endl;
        }
        // QuickSort
        else if (sortOption == 3) {
            timer = startTimer();
            sorter.QuickSort(*source, 0, source->size() - 1);
            int sortTime = elapsedMicros(timer);
            cout << "Sorted " << source->size() << " elements in " << sortTime
                 << " microseconds using QuickSort" << endl << endl;
        }
        // All three sorting algorithms
        else if (sortOption == 4) {
            // Create two copies of the data to be sorted
            vector<Flights*> shellCopy = *source;
            vector<Flights*> quickCopy = *source;

            timer = startTimer();
            sorter.MergeSort(*source, 0, source->size() - 1);
            int sortTime = elapsedMicros(timer);
            cout << "Sorted " << source->size() << " elements in " << sortTime
                 << " microseconds using MergeSort" << endl;

            timer = startTimer();
            sorter.ShellSort(shellCopy);
            sortTime = elapsedMicros(timer);
            cout << "Sorted " << source->size() << " elements in " << sortTime
                 << " microseconds using ShellSort" << endl;

            timer = startTimer();
            sorter.QuickSort(quickCopy, 0, source->size() - 1);
            sortTime = elapsedMicros(timer);
            cout << "Sorted " << source->size() << " elements in " << sortTime
                 << " microseconds using QuickSort" << endl << endl;
        }

        // Print the results
        if (analysisType == 1)
            data.PrintCarrierTop20();
        else if (analysisType == 2)
            data.PrintCityPairTop20();
        else if (analysisType == 3)
            data.PrintDistanceTop20();

    }
    return 0; 
}


// Selection validation
bool validateSelection(string userInput, int lowRange, int highRange) {
    if (!isdigit(userInput[0]))
        return false;
    size_t position;
    int value = stoi(userInput, &position);
    if (position != userInput.length())
        return false;
    if (value < lowRange || value > highRange)
        return false;
    return true;
}

// Performance tracking
steady_clock::time_point startTimer() {
    return high_resolution_clock::now();
}

int elapsedMillis(steady_clock::time_point start) {
    steady_clock::time_point stop = high_resolution_clock::now();
    return duration_cast<milliseconds>(stop - start).count();
}

int elapsedMicros(steady_clock::time_point start) {
    steady_clock::time_point stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}