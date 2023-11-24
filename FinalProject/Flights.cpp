
#include "Flights.h"


Flights::Flights(float _seats, float _passengers, string _name, float _distance)
{
    seats = _seats;
    passengers = _passengers;
    efficiency = _seats / _passengers;
    name = _name;
    distance = _distance;

    if (_passengers == 0)
    {
        efficiency = 0;
    }
}
