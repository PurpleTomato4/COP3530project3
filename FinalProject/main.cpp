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

bool validateSelection(string userInput, int lowRange, int highRange);

int main()
{
    cout << "Loading flight database..." << endl << endl; 

    FlightData data;
    data.LoadData("flightdata.csv");

    cout << "Welcome to the Airline Sorter 1000. What would you like to do?" << endl << endl;

    while (true) {
        int analysisType;
        bool subMenu = true;
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

        if (analysisType == 0)
            break;

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

        if (sortOption == 0)
            break;

        float shellSortGap;

        if (sortOption == 2) {
            while (true) {
                cout << "ShellSort Gap: ";
                string input;
                cin >> input;
                cout << endl;
                if (!validateSelection(input, 0, 100))
                    cout << "Invalid selection. Please try again." << endl << endl;
                else {
                    shellSortGap = stof(input);
                    break;
                }
            }
        }

        int direction;
        while (true) {
            cout << "In what order would you like to sort?" << endl << endl;
            cout << "1. Descending" << endl;
            cout << "2. Ascending" << endl;
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
            ascending = 0;
        else
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

bool validateSelection(string userInput, int lowRange, int highRange) {
    if(userInput.size() > 2 || !isdigit(userInput[0]))
        return false;
    if (stoi(userInput) < lowRange || stoi(userInput) > highRange)
        return false;
    return true;
}

