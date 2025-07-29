#include <iostream>
#include "PID/PID.h"
#include <chrono>
#include <thread>
#include <vector>
#include "matplotlibcpp.h"
#include <random>

namespace plt = matplotlibcpp;

using namespace std;

// System variables
float target_distance = 50.0f;
float alt = 100.0f;
float cruise_speed = 10.0f // 10 m/s

const float kp = 30.0;
const float ki = 0.0;
const float kd = 10.0;

double deg2rad(double deg) { return deg * M_PI / 180.0; }
double rad2deg(double rad) { return rad * 180.0 / M_PI; }

int main()
{

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, deg2rad(1.0)); // 1 deg noise

    



    // Gaussian noise parameters
    const double sigma = 9.2;     // standard deviation of noise on acceleration
    std::default_random_engine gen;
    std::normal_distribution<double> noise(0.0, sigma);
    std::vector<double> tmp, alt, set_alt;
    
    PID_Controller *pid = new PID_Controller(kp, ki, kd);

    for(int i = 0; i < 400; i++)
    {
       
        // Log the data to visualize
        tmp.push_back(dt * i);
        alt.push_back(measured_altitude);
        set_alt.push_back(set_altitude);

    }
}