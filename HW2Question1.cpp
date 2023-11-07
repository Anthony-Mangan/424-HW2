#include <iostream>
#include <string>
#include <map>
#include <vector>
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
// This class stores the flight information. addFlight allows us to add flight information to the container and get distance allows us to check if
// the origin and destination exist within the 'flight' vector. It also contains a 'flights' vector that stores FlightPaths
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

/*int main() {
    FlightContainer flightData;

    // Add the flights
    flightData.addFlight(FlightPaths("SCE", "PHL", 160));
    flightData.addFlight(FlightPaths("SCE", "ORD", 640));
    flightData.addFlight(FlightPaths("SCE", "EWR", 220));

    // Retrieve flight distances
    int distance1 = flightData.getDistance("SCE", "PHL"); // Should be 160
    int distance2 = flightData.getDistance("SCE", "ORD"); // Should be 640
    int distance3 = flightData.getDistance("SCE", "EWR"); // Should be 220

    // Display the distances
    cout << "Distance from SCE to PHL: " << distance1 << " miles" << endl;
    cout << "Distance from SCE to ORD: " << distance2 << " miles" << endl;
    cout << "Distance from SCE to EWR: " << distance3 << " miles" << endl;

    return 0;
}
*/
