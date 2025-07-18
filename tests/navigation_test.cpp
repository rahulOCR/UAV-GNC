#include "Navigator/Navigator.h"
#include "matplotlibcpp.h"
#include <iostream>
#include <vector>

namespace plt = matplotlibcpp;

int main() {
    Navigator nav(20.0, 0.75, 25.0);

    // Set waypoints (straight line path)
    double lat_A = 28.0000, lon_A = 77.0000;
    double lat_B = 28.0050, lon_B = 77.0050;

    nav.updateWaypoint(lat_A, lon_A, lat_B, lon_B);

    // Simulated aircraft starting position
    double lat = 28.0000;
    double lon = 77.0000;
    double heading = 0.0; // radians (north)

    // Lists for plotting
    std::vector<double> path_lat, path_lon;
    std::vector<double> wp_lat = {lat_A, lat_B};
    std::vector<double> wp_lon = {lon_A, lon_B};

    double dt = 1.0; // time step
    double speed = 25.0; // m/s

    for (int i = 0; i < 100; ++i) {
        // Get L1 lateral acceleration command (here: nav_roll = angle, use as heading correction)
        double nav_roll = nav.guidanceLaw(lat, lon, heading);

        // Simulate turn (just adjust heading slightly toward path)
        heading += nav_roll * 0.05; // damped response

        // Move forward using new heading
        lat += (speed * dt * cos(heading)) / 111320.0; // approx meters to deg lat
        lon += (speed * dt * sin(heading)) / (111320.0 * cos(lat * M_PI / 180.0)); // deg lon

        path_lat.push_back(lat);
        path_lon.push_back(lon);
    }

    // Plot path and waypoints
    plt::figure_size(800, 600);
    plt::plot(path_lon, path_lat, {{"label", "UAV Path"}, {"color", "blue"}});
    plt::plot(wp_lon, wp_lat, "ro");
    plt::xlabel("Longitude");
    plt::ylabel("Latitude");
    plt::title("Navigator Path Following");
    plt::legend();
    plt::grid(true);
    plt::show();

    return 0;
}
