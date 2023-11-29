#pragma once
#include <vector>
#include <string>
#include "Flights.h"
using namespace std;


struct FlightData {
    vector<Flights*> _flightData;
    // Specific vector for getting air carrier efficiency
    vector<Flights*> _airCarrierData;
    vector<Flights*> _cityPairs;
    ~FlightData();
    void LoadData(string filename);
    void GetCarrierData();
    void GetCityPairs();
    void PrintCarrierTop20();
    void PrintCityPairTop20();
    void PrintDistanceTop20();
};

