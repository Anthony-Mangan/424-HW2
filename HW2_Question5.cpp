#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Question5GeneralAviation.h"
#include "Question5Airliner.h"
#include "Question4Plane.h"
#include "Question3FlightPaths.h"
using namespace std;

int main() {
    // Create aircraft objects
    Airliner aa1("AA", "SCE", "PHL");
    Airliner ua1("UA", "SCE", "ORD");
    Airliner ua2("UA", "SCE", "EWR");
    Airliner aa2("AA", "SCE", "ORD");
    GeneralAviation ga1("SCE", "PHL");
    GeneralAviation ga2("SCE", "EWR");
    GeneralAviation ga3("SCE", "ORD");

    // Set the speeds (in mph) for each aircraft
    aa1.setVel(470);
    ua1.setVel(515);
    ua2.setVel(480);
    aa2.setVel(500);
    ga1.setVel(140);
    ga2.setVel(160);
    ga3.setVel(180);

    // Define a random number generator for timestep between 10 and 100
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> timestepDistribution(10, 100);

    // Initialize variables to keep track of time and position
    double time = 0;
    double timestep = 60.0 / 3600;// static_cast<double>(timestepDistribution(gen));
    cout << "Time: " << time << " hours" << endl;
    cout << "AA1 Position: " << aa1.getPos() << " miles" << endl;
    cout << "UA1 Position: " << ua1.getPos() << " miles" << endl;
    cout << "UA2 Position: " << ua2.getPos() << " miles" << endl;
    cout << "AA2 Position: " << aa2.getPos() << " miles" << endl;
    cout << "GA1 Position: " << ga1.getPos() << " miles" << endl;
    cout << "GA2 Position: " << ga2.getPos() << " miles" << endl;
    cout << "GA3 Position: " << ga3.getPos() << " miles" << endl;
    // Simulate aircraft movements
    while (true) {
        // Print the current time
        cout << "Time: " << time + timestep << " hours" << endl;

        // Call the "operate" function for each aircraft with the timestep
        aa1.operate(timestep);
        ua1.operate(timestep);
        ua2.operate(timestep);
        aa2.operate(timestep);
        ga1.operate(timestep);
        ga2.operate(timestep);
        ga3.operate(timestep);

        // Print the position of each aircraft
        cout << "AA1 Position: " << aa1.getPos() << " miles" << endl;
        cout << "UA1 Position: " << ua1.getPos() << " miles" << endl;
        cout << "UA2 Position: " << ua2.getPos() << " miles" << endl;
        cout << "AA2 Position: " << aa2.getPos() << " miles" << endl;
        cout << "GA1 Position: " << ga1.getPos() << " miles" << endl;
        cout << "GA2 Position: " << ga2.getPos() << " miles" << endl;
        cout << "GA3 Position: " << ga3.getPos() << " miles" << endl;

        // Update time
        time += timestep;
        //timestep = static_cast<double>(timestepDistribution(gen));
    }

    return 0;

}
