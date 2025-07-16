#pragma once

#include <cmath>

class Navigator {
public:
    Navigator(double L1_dist, double L1_damping, double L1_period);

    void updateWaypoint(double lat_A, double lon_A, double lat_B, double lon_B);
    double guidanceLaw(double lat_now, double lon_now, double track_angle);

private:
    double _L1_dist;
    double _L1_damping;
    double _L1_period;

    double _lat_A, _lon_A;
    double _lat_B, _lon_B;

    double getBearingRad(double lat1, double lon1, double lat2, double lon2);
    double getDistance(double lat1, double lon1, double lat2, double lon2);
    double wrapPI(double angle);
};
