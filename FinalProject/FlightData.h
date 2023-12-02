/** COP3530 Project 3 - Airline Sorter 1000
 ** University of Florida - Fall 2023
 ** Authors: Jack Goldstein, Benjamin Uppgard, Ryan Wilson
 ** Date: 12/07/2023
 ** Description: Custom class for processing data loaded from T100-Domestic
 **              Segment reports from the USDOT Bureau of Transportation
 **              Statistics.
 **/

#pragma once
#include <vector>
#include <string>
#include "Flights.h"
using namespace std;

class FlightData {
public:
    vector<Flights*> _flightData;
    vector<Flights*> _airCarrierData;
    vector<Flights*> _cityPairs;

    ~FlightData();
    void LoadData(string filename);
    void PrintCarrierTop20();
    void PrintCityPairTop20();
    void PrintDistanceTop20();

private:
    void GetCarrierData();
    void GetCityPairs();

};