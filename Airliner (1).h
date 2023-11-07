#include <string>
#include "Question4Plane.h"
using namespace std;

class Airliner : public Plane {
private:
    string Airline;

public:
    Airliner(const string& Airline, const string& from, const string& to)
        : Plane(from, to), Airline(Airline) {
    }

    ~Airliner() {}

    string plane_type() override {
        return Airline;
    }

    double time_on_ground() override {
        return draw_from_normal_dist(1800.0, 600.0);
    }
}; 

