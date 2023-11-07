#include <iostream>
#include <string>
#include <vector>
#include<map>

using namespace std;

class FlightPaths {
public:
    FlightPaths(const string& origin, const string& destination, int distance)
        : originAirport(origin), destAirport(destination), flightDistance(distance) {}

    const string& getOrigin() const {
        return originAirport;
    }

    const string& getDestination() const {
        return destAirport;
    }

    int getDistance() const {
        return flightDistance;
    }

private:
    string originAirport;
    string destAirport;
    int flightDistance;
};
