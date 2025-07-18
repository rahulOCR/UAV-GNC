/*
*   source file for definition of PID_Controller Class
*
*/
#include "PID.h"
#include <cmath>     // for isnan
#include <limits>    // for quiet_NaN
#define FILT_E_HZ_DEFAULT 20.0f   // default input filter frequency
#define FILT_E_HZ_MIN     0.01f   // minimum input filter frequency
#define FILT_D_HZ_DEFAULT 10.0f   // default input filter frequency
#define FILT_D_HZ_MIN     0.005f  // minimum input filter frequency


/*
  calculate a low pass filter alpha value
 */
float calc_lowpass_alpha_dt(float dt, float cutoff_freq)
{
    if ((dt < 0) || (cutoff_freq < 0)) {
        return 1.0;
    }
    if ((cutoff_freq <= 0.0f)) {
        return 1.0;
    }
    if ((dt <= 0.0f)) {
        return 0.0;
    }
    float rc = 1.0f / (M_PI * cutoff_freq);
    return dt / (dt + rc);
}

//Constructor

PID_Controller::PID_Controller(float kp, float ki, float kd)
{
    _kp = kp;
    _ki = ki;
    _kd = kd;
    _filt_E_hz = FILT_E_HZ_DEFAULT;
    _filt_D_hz = FILT_D_HZ_DEFAULT;

}

float PID_Controller::update(float setpoint, float measured, float dt) {
    _error = setpoint - measured;
    _integrator += _error * dt;
    _derivative = (_error - _last_error) / dt;
    _last_error = _error;
    return _kp * _error + _ki * _integrator + _kd * _derivative;
}


float PID_Controller::get_filt_E_alpha(float dt) const
{
    return calc_lowpass_alpha_dt(dt, _filt_E_hz);
}

float PID_Controller::get_filt_D_alpha(float dt) const
{
    return calc_lowpass_alpha_dt(dt, _filt_D_hz);
}
