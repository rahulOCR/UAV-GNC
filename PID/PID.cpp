/*
*   source file for definition of PID_Controller Class
*
*/
#include "PID.h"
#include <cmath>     // for isnan
#include <limits>    // for quiet_NaN

const float M_2PI = 3.14;
#define FILT_E_HZ_DEFAULT 20.0f   // default input filter frequency
#define FILT_E_HZ_MIN     0.01f   // minimum input filter frequency
#define FILT_D_HZ_DEFAULT 10.0f   // default input filter frequency
#define FILT_D_HZ_MIN     0.005f  // minimum input filter frequency


//Constructor

PID_Controller::PID_Controller(float kp, float ki, float kd, float i_max, float ff)
{
    _kp = kp;
    _ki = ki;
    _kd = kd;
    _ki_max = i_max;
    _kff = ff;
    _filt_E_hz = FILT_E_HZ_DEFAULT;
    _filt_D_hz = FILT_D_HZ_DEFAULT;

}

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
    float rc = 1.0f / (M_2PI * cutoff_freq);
    return dt / (dt + rc);
}

float constrain_float(float val,float low, float high )
{
    if(val < low)
        return low;

    else if(val > high)
        return high;
    
    return val;

}




float PID_Controller::update_all(float target, float measurement, float dt, bool limit)
{
    return update_all(target, measurement, dt, (limit && (_integrator < 0)), (limit && (_integrator > 0)));
}

float PID_Controller::update_all(float target, float measurement, float dt, bool limit_neg, bool limit_pos)
{
    // don't process inf or NaN
    if ((std::isnan(target)) || std::isnan(measurement)) {
        return 0.0f;
    }

    _target = target;

    // reset input filter to value received
    if (_reset_filter) {
        _reset_filter = false;
        _error = _target - measurement;
        _derivative = 0.0f;
    } else {
        float error_last = _error;
        _error += get_filt_E_alpha(dt) * ((_target - measurement) - _error);

        // calculate and filter derivative
        if (dt > 0) {
            float derivative = (_error - error_last) / dt;
            _derivative += get_filt_D_alpha(dt) * (derivative - _derivative);
        }
    }

    // update I term
    update_i(dt, limit_neg, limit_pos);

    const float P_out = _error * _kp;
    const float D_out = _derivative * _kd;


    return P_out + _integrator + D_out + _target * _kff;
}



float PID_Controller::update(float setpoint, float measured, float dt) {
    _error = setpoint - measured;
    _integrator += _error * dt;
    double derivative = (_error - _last_error) / dt;
    _last_error = _error;
    return _kp * _error + _ki * _integrator + _kd * derivative;
}


float PID_Controller::get_filt_E_alpha(float dt) const
{
    return calc_lowpass_alpha_dt(dt, _filt_E_hz);
}

float PID_Controller::get_filt_D_alpha(float dt) const
{
    return calc_lowpass_alpha_dt(dt, _filt_D_hz);
}


//  update_i - update the integral
//  if limit_neg is true, the integral can only increase
//  if limit_pos is true, the integral can only decrease
void PID_Controller::update_i(float dt, bool limit_neg, bool limit_pos)
{
    if (_ki> 0) {
        // Ensure that integrator can only be reduced if the output is saturated
        if (!((limit_neg && (_error < 0)) || (limit_pos && (_error > 0)))) {
            _integrator += ((float)_error * _ki) * dt;
            _integrator = constrain_float(_integrator, -_ki_max, _ki_max);
        }
    } else {
        _integrator = 0.0f;
    }
}


void PID_Controller::set_integrator(float target, float measurement, float i)
{
    set_integrator(target - measurement, i);
}

void PID_Controller::set_integrator(float error, float i)
{
    set_integrator(i - error * _kp);
}

void PID_Controller::set_integrator(float i)
{
    _integrator = constrain_float(i, -_ki_max, _ki_max);
    
}
