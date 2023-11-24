
#ifndef PROJECT3_FLIGHTS_H
#define PROJECT3_FLIGHTS_H
#include <string>
using namespace std;

class Flights {

public:

    string name;
    float seats = 0;
    float passengers = 0;
    float distance = 0;
    float efficiency = 0;

    Flights(float seats, float passengers, string _name, float _distance);

};


#endif //PROJECT3_FLIGHTS_H
