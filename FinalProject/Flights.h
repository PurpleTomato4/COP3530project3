/** COP3530 Project 3 - Airline Sorter 1000
 ** University of Florida - Fall 2023
 ** Authors: Jack Goldstein, Benjamin Uppgard, Ryan Willson
 ** Date: 12/05/2023
 ** Description: Custom class for processing data loaded from T100-Domestic
 **              Segment reports from the USDOT Bureau of Transportation
 **              Statistics.
 **/

#pragma once

#include <string>
using namespace std;

struct Flights {

    string _carrier = "";
    string _origin = "";
    string _destination = "";
    int _distance = 0;
    int _seats = 0;
    int _passengers = 0;
    float _efficiency = 0;

    Flights();
    Flights(string carrier, string origin, string destination, int seats,
            int passengers, int distance);
    static bool EfficiencyComp(Flights* a, Flights* b, bool ascending);
    static bool DistanceComp(Flights* a, Flights* b, bool ascending);
};