#include "Flights.h"
#include <unordered_map>

Flights::Flights() {}

// Modified to use initializer lists (a bit faster)
Flights::Flights(string carrier, string origin, string destination, int seats,
                 int passengers, int distance) : _carrier(carrier),
                 _origin(origin), _destination(destination), _seats(seats),
                 _passengers(passengers), _distance(distance) {
    _efficiency = static_cast<float>(_passengers) / _seats;
}

// This functionality was moved into the FlightData Class

/*
void Flights::Increment(float _seats, float _passengers, float _distance)
{
    seats += _seats;
    passengers += _passengers;
    distance += _distance;
    efficiency = passengers / seats;
    if (_seats == 0) {
        efficiency = 0;
    }
}
 */

bool Flights::EfficiencyComp(Flights *a, Flights *b, bool ascending) {
    if (ascending)
        return a->_efficiency > b->_efficiency;
    else
        return a->_efficiency < b->_efficiency;
}

bool Flights::DistanceComp(Flights *a, Flights *b, bool ascending) {
    if (ascending)
        return a->_distance > b->_distance;
    else
        return a->_distance < b->_distance;
}
