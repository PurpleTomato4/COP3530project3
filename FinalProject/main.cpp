#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <chrono> 
#include <map>
#include <functional>
#include "Flights.h"
#include "Sort.h"
#include "constants.h"
#include "FlightData.h"
using namespace std;
using namespace std::chrono; 

int main()
{
    cout << "Loading flight database..." << endl << endl; 

    FlightData data;
    data.LoadData("flightdata.csv");

    cout << "Welcome to the Airline Sorter 1000. What would you like to do?" << endl << endl;

    bool menu = true;
    int counter = 0;

    while (menu) {
        if (counter > 0) {
            cout << "Would you like to do anything else?" << endl << endl;
        }
        cout << "1. Sort using MergeSort" << endl;
        cout << "2. Sort using ShellSort" << endl;
        cout << "3. Sort using QuickSort" << endl;
        cout << "3. Compare All Sorting Algorithms" << endl;
        cout << "0. Exit" << endl << endl;
        counter += 1;

        int sortOption;
        cin >> sortOption;
        cout << endl;

        float shellSortGap;

        if (sortOption == 2) {
            cout << "ShellSort Gap: ";
            cin >> shellSortGap;
            cout << endl;
        }

        cout << "What would you like to sort?" << endl << endl;
        cout << "1. Air Carriers by Efficiency (Passengers/Available Seats)"
             << endl;
        cout << "2. Routes by Efficiency (Passengers/Available Seats)" << endl;
        cout << "3. All Flights by Distance" << endl;
        cout << "0. Exit" << endl << endl;

        int analysisType;
        cin >> analysisType;
        cout << endl;

        Sort<Flights *> sorter;

        vector<Flights *> *source;
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

        cout << "In what order would you like to sort?" << endl << endl;
        cout << "1. Descending" << endl;
        cout << "2. Ascending" << endl;

        int direction;
        cin >> direction;
        cout << endl;

        bool ascending;
        if (direction == 1)
            ascending = 0;
        else if (direction == 2)
            ascending = 1;

        sorter.SetSortDirection(ascending);

        if (sortOption == 1)
            sorter.MergeSort(*source, 0, source->size() - 1);
        else if (sortOption == 2)
            sorter.ShellSort(*source, shellSortGap);
        else if (sortOption == 3)
            sorter.QuickSort(*source, 0, source->size() - 1);

        if (analysisType == 1)
            data.PrintCarrierTop20();
        else if (analysisType == 2)
            data.PrintCityPairTop20();
        else if (analysisType == 3)
            data.PrintDistanceTop20();
    }
    return 0; 
}

