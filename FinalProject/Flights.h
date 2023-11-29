#ifndef PROJECT3_FLIGHTS_H
#define PROJECT3_FLIGHTS_H
#include <string>
using namespace std;

class Flights {

public:

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

#endif //PROJECT3_FLIGHTS_H
