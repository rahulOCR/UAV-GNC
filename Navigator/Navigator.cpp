#include "Navigator.h"

#define DEG2RAD(x) ((x) * M_PI / 180.0)
#define RAD2DEG(x) ((x) * 180.0 / M_PI)
#define EARTH_RADIUS 6371000.0 // meters

Navigator::Navigator(double L1_dist, double L1_damping, double L1_period)
    : _L1_dist(L1_dist), _L1_damping(L1_damping), _L1_period(L1_period) {}

void Navigator::updateWaypoint(double lat_A, double lon_A, double lat_B, double lon_B) {
    _lat_A = DEG2RAD(lat_A);
    _lon_A = DEG2RAD(lon_A);
    _lat_B = DEG2RAD(lat_B);
    _lon_B = DEG2RAD(lon_B);
}

double Navigator::guidanceLaw(double lat_now_deg, double lon_now_deg, double track_angle_rad) {
    double lat_now = DEG2RAD(lat_now_deg);
    double lon_now = DEG2RAD(lon_now_deg);

    // Compute vectors
    double course_AB = getBearingRad(_lat_A, _lon_A, _lat_B, _lon_B);
    double dist_AB = getDistance(_lat_A, _lon_A, _lat_B, _lon_B);
    double dist_AP = getDistance(_lat_A, _lon_A, lat_now, lon_now);
    double course_AP = getBearingRad(_lat_A, _lon_A, lat_now, lon_now);

    // Cross track error
    double xtk = asin(sin(dist_AP / EARTH_RADIUS) * sin(course_AP - course_AB)) * EARTH_RADIUS;

    // Along track
    double along_track = acos(cos(dist_AP / EARTH_RADIUS) / cos(xtk / EARTH_RADIUS)) * EARTH_RADIUS;

    // L1 angle
    double eta = atan2(-xtk, _L1_dist + along_track);

    // Commanded turn rate (normalized)
    double nav_roll = _L1_damping * eta;

    return wrapPI(nav_roll); // radian output
}

double Navigator::getBearingRad(double lat1, double lon1, double lat2, double lon2) {
    double dLon = lon2 - lon1;
    double y = sin(dLon) * cos(lat2);
    double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);
    return atan2(y, x);
}

double Navigator::getDistance(double lat1, double lon1, double lat2, double lon2) {
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2.0) * sin(dlat / 2.0) +
               cos(lat1) * cos(lat2) * sin(dlon / 2.0) * sin(dlon / 2.0);
    return EARTH_RADIUS * 2.0 * atan2(sqrt(a), sqrt(1 - a));
}

double Navigator::wrapPI(double angle) {
    while (angle > M_PI) angle -= 2.0 * M_PI;
    while (angle < -M_PI) angle += 2.0 * M_PI;
    return angle;
}
