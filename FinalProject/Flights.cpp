/** COP3530 Project 3 - Airline Sorter 1000
 ** University of Florida - Fall 2023
 ** Authors: Jack Goldstein, Benjamin Uppgard, Ryan Willson
 ** Date: 12/05/2023
 **/

#include "Flights.h"

Flights::Flights() {}

Flights::Flights(string carrier, string origin, string destination, int seats,
                 int passengers, int distance) : _carrier(carrier),
                 _origin(origin), _destination(destination), _seats(seats),
                 _passengers(passengers), _distance(distance) {
    _efficiency = static_cast<float>(_passengers) / _seats;
}

// Comparison function for efficiency
bool Flights::EfficiencyComp(Flights *a, Flights *b, bool ascending) {
    if (ascending)
        return a->_efficiency > b->_efficiency;
    else
        return a->_efficiency < b->_efficiency;
}

// Comparison function for distance
bool Flights::DistanceComp(Flights *a, Flights *b, bool ascending) {
    if (ascending)
        return a->_distance > b->_distance;
    else
        return a->_distance < b->_distance;
}