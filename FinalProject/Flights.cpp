
#include "Flights.h"

Flights::Flights() {}

Flights::Flights(float _seats, float _passengers, string _name, float _distance)
{
    seats = _seats;
    passengers = _passengers;
    efficiency = _passengers / _seats;
    name = _name;
    distance = _distance;

    if (_seats == 0)
    {
        efficiency = 0;
    }
}

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

bool Flights::EfficiencyComp(Flights *a, Flights *b, bool ascending) {
    if (ascending)
        return a->efficiency < b->efficiency;
    else
        return a->efficiency > b->efficiency;
}
