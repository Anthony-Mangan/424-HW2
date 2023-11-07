#include <string>
#include "Question4Plane.h"
using namespace std;
class GeneralAviation : public Plane {
public:
    GeneralAviation(const string& from, const string& to)
        : Plane(from, to) {
    }
    ~GeneralAviation() {}

    double time_on_ground() override {
        return draw_from_normal_dist(600.0, 60.0);
    }
};

