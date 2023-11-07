#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "FlightPaths.h"

using namespace std;

class FlightContainer {
public:
    void addFlight(const FlightPaths& flight) {
        flights.push_back(flight);
    }

    int getDistance(const string& origin, const string& destination) const {
        for (const FlightPaths& flight : flights) {
            if (flight.getOrigin() == origin && flight.getDestination() == destination) {
                return flight.getDistance();
            }
        }
        return -1; // Return -1 if the flight doesn't exist
    }

private:
    vector<FlightPaths> flights;
};
