#include <iostream>
#include "PID/PID.h"
#include <chrono>
#include <thread>
#include <vector>
#include "matplotlibcpp.h"
#include <random>

namespace plt = matplotlibcpp;

using namespace std;

const float g = 9.8;        // 9.8 m/s acceleration due to gravity
const float mass = 2.0;     // mass of the body
const float dt = 0.1;             // delta time

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
    

    float set_altitude = 100.0f;
    float measured_altitude;
    float thrust = 0.0f;
    float step_alt = 0.0f;
    float dz = 0.0f;
    float ddz = 0.0f;

    float measured_roll = 0.0f;
    float measured_pitch = 0.0f;

    double roll = deg2rad(1.0);   // roll
    double pitch = deg2rad(3.0);  // pitch

    std::vector<double> tmp, alt, set_alt;
    
    PID_Controller *pid = new PID_Controller(kp, ki, kd);

    for(int i = 0; i < 400; i++)
    {
        // generate noise in attitude
        measured_roll = roll + distribution(generator);
        measured_pitch = pitch + distribution(generator);

        // get the steer command for the system
        const float steer_cmd = pid->update(set_altitude, measured_altitude, dt);

        // update the system
        thrust  = mass * g + steer_cmd;
        step_alt = (thrust * cos(measured_pitch) * cos(measured_roll) / mass) - g + noise(gen);
        dz += step_alt * dt;
        measured_altitude += dz * dt;

        // Log the data to visualize
        tmp.push_back(dt * i);
        alt.push_back(measured_altitude);
        set_alt.push_back(set_altitude);

        printf("measured alt = %f time = %f\n", measured_altitude, dt * i);

    }

     // Plot measured altitude
    plt::figure();
    plt::plot(tmp, alt, {{"label", "measured altitude (m)"}});

    // Plot set_altitude
    plt::plot(tmp, set_alt, {{"label", "target altitude "}});

    plt::xlabel("Time (s)");
    plt::ylabel("Value");
    plt::title("measured alt and target alt over Time");
    plt::legend();
    plt::grid(true);
    plt::show();


}