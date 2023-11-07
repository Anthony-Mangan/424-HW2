#include <iostream>
#include <string>
#include <vector>
#include<map>

using namespace std;

// This class represents the flight path between two different airports, using the origin, destination, and distance as the input parameters.
// Additionally, it uses getter methods to access the different parameters.
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
