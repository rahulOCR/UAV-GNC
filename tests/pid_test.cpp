#include <iostream>
#include "PID/PID.h"
#include <chrono>
#include <thread>
#include <vector>
#include "matplotlibcpp.h"
#include <random>

namespace plt = matplotlibcpp;

using namespace std;



int main()
{
    PID_Controller *pid = new PID_Controller(TEST_P, TEST_I, TEST_D);

    // Gaussian noise parameters
    std::default_random_engine gen;
    std::normal_distribution<double> noise(0.0, sigma);
    const double sigma = 0.2;     // std dev of noise on acceleration
    
    float setpoint = 390.0;   // target speed in km/h
    float speed = 0.0;       // current speed
    float dt = 0.1;
    std::vector<double> time, spd, thr;

    for (int i = 0; i < 400; ++i) {
        float throttle = pid->update(setpoint, speed, dt);
        double acc_noise = noise(gen);
        // Simulate system
        speed += throttle * dt - 0.02 * speed + acc_noise;// Add Gaussian noise
       

       

        time.push_back(i*dt);
        spd.push_back(speed);
        thr.push_back(throttle);


         std::cout << "Time: " << i * dt << "s, "
                  << "Speed: " << speed << " km/h, "
                  << "Throttle: " << throttle << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }


     // Plot speed
    plt::figure();
    plt::plot(time, spd, {{"label", "Speed (m/s)"}});

    // Plot throttle
    plt::plot(time, thr, {{"label", "Throttle "}});

    plt::xlabel("Time (s)");
    plt::ylabel("Value");
    plt::title("Speed and Throttle over Time");
    plt::legend();
    plt::grid(true);
    plt::show();

    return 0;
}