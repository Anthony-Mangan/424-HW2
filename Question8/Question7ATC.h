#include <iostream>
#include <vector>
#include "Question4Plane.h"
using namespace std;

class ATC : public Plane {
private:
    vector<Plane*> registered_planes;
    const int MAX_LANDED_PLANE_NUM;
    const int AIRSPACE_DISTANCE;

public:
    ATC() : Plane("", ""), MAX_LANDED_PLANE_NUM(2), AIRSPACE_DISTANCE(50) {
        // Constructor
    }

    ~ATC() {
        // Destructor
    }

    void register_plane(Plane* airplane) {
        // Register an airplane in the container
        registered_planes.push_back(airplane);
    }

    void control_traffic() {
        double landed_planes = 0;
        int i = 0;
        if (i < registered_planes.size()) {
            Plane* current_plane = registered_planes[i];
            landed_planes += current_plane->getAtSCE();
            i = i + 1;
        }
        else {
            if (landed_planes >= MAX_LANDED_PLANE_NUM) {
                i = 0;
                if (i < registered_planes.size()) {
                    for (int i = 0; i < registered_planes.size(); i++) {
                        Plane* current_plane = registered_planes[i];
                        if (current_plane->getAtSCE() == 0 && distance_to_SCE() < -AIRSPACE_DISTANCE && current_plane->getLoiter_time() == 0) {
                            current_plane->setLoiter_time(100);
                            i++;
                        }
                    }

                }
            }
        }
    }
private:
    int calculate_distance(Plane* plane1, Plane* plane2) {
        // Calculate the distance between two airplanes (you need to implement this)
        // You can use a formula or method to calculate the distance between them.
        // Return the distance as an integer.
    }
};