
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

    Flights();
    Flights(float seats, float passengers, string _name, float _distance);
    void Increment(float _seats, float _passengers, float _distance);
    static bool EfficiencyCompGT(Flights* a, Flights* b);
};


#endif //PROJECT3_FLIGHTS_H
