#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Question3FlightPaths.h"

using namespace std;

class Plane {
protected:
    double wait_time;

private:
    double pos;
    double vel;
    double distance;
    double loiter_time;
    bool at_SCE;
    string origin;
    string destination;
    vector<FlightPaths> airports;

public:
    Plane(const string& from, const string& to) : origin(from), destination(to) {
        pos = 0.0;
        vel = 0.0;
        distance = 0.0;
        loiter_time = 0.0;
        at_SCE = 0.0;
    }
    int getDistance(const string& origin, const string& destination) const {
        for (const FlightPaths& flight : airports) {
            if (flight.getOrigin() == origin && flight.getDestination() == destination) {
                return flight.getDistance();
            }
        }
        return -1; // Return -1 if the flight doesn't exist
    }
    virtual ~Plane() {}

    void operate(double dt) {
        if (loiter_time != 0) {
            loiter_time -= dt;
        }
        else {
            if (wait_time != 0) {
                wait_time -= dt;
            }
            else {
                if (pos < distance) {
                    pos += vel * dt;
                    at_SCE = 0;
                }
                else {
                    if (destination == "SCE") {
                        at_SCE = 1;
                        time_on_ground();
                        string swap = origin;
                        origin = destination;
                        destination = swap;
                        pos = 0.0;

                    }
                    else {
                        time_on_ground();
                        string swap = origin;
                        origin = destination;
                        destination = swap;
                        pos = 0.0;
                    }
                }
            }
        }
    }

    double getPos() {
        return pos;
    }

    double getVel() {
        return vel;
    }

    double getLoiter_time() {
        return loiter_time;
    }

    string getOrigin() {
        return origin;
    }

    string getDestination() {
        return destination;
    }

    bool getAtSCE() {
        return at_SCE;
    }

    void setVel(double newVel) {
        vel = newVel;
    }

    void setLoiter_time(double newLoiterTime) {
        loiter_time = newLoiterTime;
    }

    double distance_to_SCE() {
        if (destination == "SCE") {
            return distance - pos;
        }
        else {
            return -1.0;
        }
    }

    virtual double time_on_ground() {
        return 0.0;
    }

    virtual string plane_type() {
        return "GA";
    }

    static double draw_from_normal_dist(double m, double sd) {
        random_device rd{};
        mt19937 gen{ rd() };
        normal_distribution<> d{m, sd};
        return d(gen);
    }

    ~Plane() {}
};



