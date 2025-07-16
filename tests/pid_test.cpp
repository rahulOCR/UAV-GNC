#include <iostream>
#include "PID/PID.h"
#include <chrono>
#include <thread>
#include <vector>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

using namespace std;

int main()
{
    PID_Controller *pid = new PID_Controller(TEST_P, TEST_I, TEST_D, TEST_IMAX , TEST_FILTER);

    // create a system initial values
    float setpoint = 390.0;   // target speed in km/h
    float speed = 0.0;       // current speed
    float dt = 0.1;
    std::vector<double> time, spd, thr;

    for (int i = 0; i < 400; ++i) {
        float throttle = pid->update(setpoint, speed, dt);
        // Simulate physics
        speed += throttle * dt - 0.02 * speed;

       

        time.push_back(i*dt);
        spd.push_back(speed);
        thr.push_back(throttle);



        // const float control_P = pid->get_p();
        // const float control_I = pid->get_i();
        // const float control_D = pid->get_d();


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