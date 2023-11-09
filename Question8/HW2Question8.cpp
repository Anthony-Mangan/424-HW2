#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Question5GeneralAviation.h"
#include "Question5Airliner.h"
#include "Question4Plane.h"
#include "Question3FlightPaths.h"
#include "Question7ATC.h"
#include "SDL.h"
#include "HW2_Visualizer.h"

using namespace std;
HW2_VIZ::HW2_VIZ()
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    win = SDL_CreateWindow("Flight Management", // creates a window
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, 0);
    image = SDL_LoadBMP("map.bmp"); // this depends on where you run the binary file
    texture = SDL_CreateTextureFromSurface(renderer, image);
}

void HW2_VIZ::update(double dt)
{
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    for (auto itr = p_viz.planes_info.begin(); itr != p_viz.planes_info.end(); itr++)
    {
        SDL_Vertex vertices[] = { itr->second.v1, itr->second.v2, itr->second.v3 };
        SDL_RenderGeometry(renderer, texture, vertices, 3, NULL, 0);
    }
    SDL_RenderPresent(renderer);

    SDL_Delay(dt);
}

void HW2_VIZ::visualize_plane(std::string airline, std::string origin, std::string des, double pos)
{
    // compute new triangle to draw
    SDL_Color  color = { 0, 0, 0, 255 };
    SDL_FPoint tex_coord = { 1, 1 };

    SDL_Vertex v0 = { {0, 0}, color, tex_coord };

    double x0 = p_viz.airport_location[origin].first;
    double y0 = p_viz.airport_location[origin].second;
    double x1 = p_viz.airport_location[des].first;
    double y1 = p_viz.airport_location[des].second;
    double d = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
    double ratio = pos / d;
    v0.position.x = (1 - ratio) * x0 + ratio * x1;
    v0.position.y = (1 - ratio) * y0 + ratio * y1;

    std::array<std::string, 3> key = { airline, origin, des };
    std::array<std::string, 3> key_temp = { airline, des, origin };

    if (p_viz.planes_info.find(key) == p_viz.planes_info.end() && p_viz.planes_info.find(key_temp) != p_viz.planes_info.end())
        key = key_temp;

    v0.color = p_viz.plane_colors[airline];

    p_viz.planes_info[key].v1 = v0;
    p_viz.planes_info[key].v2 = v0;
    p_viz.planes_info[key].v3 = v0;

    p_viz.planes_info[key].v1.position.y -= 15;
    p_viz.planes_info[key].v2.position.x -= 10;
    p_viz.planes_info[key].v2.position.y += 15;
    p_viz.planes_info[key].v3.position.x += 10;
    p_viz.planes_info[key].v3.position.y += 15;

    double heading = atan2(y1 - y0, x1 - x0) + 1.57079632679;
    double temp_x = 0;

    p_viz.planes_info[key].v1.position.x -= v0.position.x;
    p_viz.planes_info[key].v1.position.y -= v0.position.y;

    p_viz.planes_info[key].v2.position.x -= v0.position.x;
    p_viz.planes_info[key].v2.position.y -= v0.position.y;

    p_viz.planes_info[key].v3.position.x -= v0.position.x;
    p_viz.planes_info[key].v3.position.y -= v0.position.y;

    temp_x = p_viz.planes_info[key].v1.position.x;
    p_viz.planes_info[key].v1.position.x = temp_x * cos(heading) - p_viz.planes_info[key].v1.position.y * sin(heading);
    p_viz.planes_info[key].v1.position.y = temp_x * sin(heading) + p_viz.planes_info[key].v1.position.y * cos(heading);

    temp_x = p_viz.planes_info[key].v2.position.x;
    p_viz.planes_info[key].v2.position.x = temp_x * cos(heading) - p_viz.planes_info[key].v2.position.y * sin(heading);
    p_viz.planes_info[key].v2.position.y = temp_x * sin(heading) + p_viz.planes_info[key].v2.position.y * cos(heading);

    temp_x = p_viz.planes_info[key].v3.position.x;
    p_viz.planes_info[key].v3.position.x = temp_x * cos(heading) - p_viz.planes_info[key].v3.position.y * sin(heading);
    p_viz.planes_info[key].v3.position.y = temp_x * sin(heading) + p_viz.planes_info[key].v3.position.y * cos(heading);

    p_viz.planes_info[key].v1.position.x += v0.position.x;
    p_viz.planes_info[key].v1.position.y += v0.position.y;

    p_viz.planes_info[key].v2.position.x += v0.position.x;
    p_viz.planes_info[key].v2.position.y += v0.position.y;

    p_viz.planes_info[key].v3.position.x += v0.position.x;
    p_viz.planes_info[key].v3.position.y += v0.position.y;
}
int main(int argc, char** argv) {
    HW2_VIZ viz;

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
    double timestep = 10.0/3600;
    /*
    cout << "Time: " << time << " hours" << endl;
    cout << "AA1 Position: " << aa1.getPos() << " miles" << endl;
    cout << "UA1 Position: " << ua1.getPos() << " miles" << endl;
    cout << "UA2 Position: " << ua2.getPos() << " miles" << endl;
    cout << "AA2 Position: " << aa2.getPos() << " miles" << endl;
    cout << "GA1 Position: " << ga1.getPos() << " miles" << endl;
    cout << "GA2 Position: " << ga2.getPos() << " miles" << endl;
    cout << "GA3 Position: " << ga3.getPos() << " miles" << endl;
    */ 

    // Create an ATC object and register airplane objects
    ATC atc;
    atc.register_plane(&aa1);
    atc.register_plane(&ua1);
    atc.register_plane(&ua2);
    atc.register_plane(&aa2);
    atc.register_plane(&ga1);
    atc.register_plane(&ga2);
    atc.register_plane(&ga3);

    // Simulate aircraft movements
    while (true) {
        // Print the current time
        cout << "Time: " << time + timestep << " hours" << endl;

        // Call the "operate" function for each airplane with the timestep
        aa1.operate(timestep);
        ua1.operate(timestep);
        ua2.operate(timestep);
        aa2.operate(timestep);
        ga1.operate(timestep);
        ga2.operate(timestep);
        ga3.operate(timestep);

        viz.visualize_plane(aa1.plane_type(), aa1.getOrigin(), aa1.getDestination(), aa1.getPos());
        viz.visualize_plane(ua1.plane_type(), ua1.getOrigin(), ua1.getDestination(), ua1.getPos());
        viz.visualize_plane(ua2.plane_type(), ua2.getOrigin(), ua2.getDestination(), ua2.getPos());
        viz.visualize_plane(aa2.plane_type(), aa2.getOrigin(), aa2.getDestination(), aa2.getPos());
        viz.visualize_plane(ga1.plane_type(), ga1.getOrigin(), ga1.getDestination(), ga1.getPos());
        viz.visualize_plane(ga2.plane_type(), ga2.getOrigin(), ga2.getDestination(), ga2.getPos());
        viz.visualize_plane(ga3.plane_type(), ga3.getOrigin(), ga3.getDestination(), ga3.getPos());

        // Call the "control_traffic" function for ATC
        atc.control_traffic();

        // Print the position of each airplane
        
        cout << "AA1 Position: " << aa1.getPos() << " miles" << endl;
        cout << "UA1 Position: " << ua1.getPos() << " miles" << endl;
        cout << "UA2 Position: " << ua2.getPos() << " miles" << endl;
        cout << "AA2 Position: " << aa2.getPos() << " miles" << endl;
        cout << "GA1 Position: " << ga1.getPos() << " miles" << endl;
        cout << "GA2 Position: " << ga2.getPos() << " miles" << endl;
        cout << "GA3 Position: " << ga3.getPos() << " miles" << endl;
       
        // Update time
        viz.update(timestep);
        time += timestep;
    
    }


    return 0;
}
