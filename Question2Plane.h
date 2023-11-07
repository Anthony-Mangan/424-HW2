#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Question1FlightPaths.h"

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
    virtual ~Plane() {}

    void operate(double dt) {
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
        return distance;
    }

    virtual double time_on_ground() {
        return 0.0;
    }

    virtual string plane_type() {
        return "GA";
    }

    static double draw_from_normal_dist(double mean, double std_dev) {
        default_random_engine generator;
        normal_distribution<double> distribution(mean, std_dev);
        return distribution(generator);
    }
};



#pragma once
