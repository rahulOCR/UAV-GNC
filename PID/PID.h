#pragma once

// default PID values for testings
#define TEST_P 0.5f
#define TEST_I 0.1f
#define TEST_D 0.05f
#define TEST_IMAX 10
#define TEST_FILTER 5.0f
#define TEST_DT 0.01f
#define TEST_INITIAL_FF 0.0f

class PID_Controller
{
    public:
        PID_Controller(float kp, float ki, float kd, float i_max, float ff);

        // gains setters
        void set_kp(float kp) { _kp = kp; }
        void set_ki(float ki) { _ki = ki; }
        void set_kd(float kd) { _kd = kd; }

        // gains getters
        float get_kp() { return _kp; }
        float get_ki() { return _ki; }
        float get_kd() { return _kd; }

        // get results from pid controller
        float get_p() const { return _error * _kp; }
        float get_i() const { return _integrator; }
        float get_d() const { return _derivative * _kd; }
        float get_ff() const { return _target * _kff; }
        float get_error() const { return _error; }

        void relax_integrator(float integrator, float dt);

        // integrator setting functions
        void set_integrator(float target, float measurement, float i);
        void set_integrator(float error, float i);
        void set_integrator(float i);

        // set target and measured inputs to PID controller and calculate outputs
        // target and error are filtered
        // the derivative is then calculated and filtered
        // the integral is then updated based on the setting of the limit flag
        float update_all(float target, float measurement, float dt, bool limit = false);
        float update_all(float target, float measurement, float dt, bool limit_neg, bool limit_pos);

        // update the integral
        // if the limit flags are set the integral is only allowed to shrink
        void update_i(float dt, bool limit_neg, bool limit_pos);

        void reset_i() { _integrator = 0.0f;}
        float update(float setpoint, float measured, float dt);

    private:
        float _kp;
        float _ki;
        float _ki_max;
        float _kff;
        float _kd;
        float _filt_E_hz;           // PID error filter frequency in Hz
        float _filt_D_hz;           // PID derivative filter frequency in Hz

        float _target;              // target value to enable filtering
        bool _reset_filter;         // true when input filter should be reset during next call to set_input              
        float _error;               // error value to enable filtering
        float _derivative;          // Last derivative to Low-Pass filter
        float _integrator;
        float _last_error;

        float get_filt_E_alpha(float dt) const;
        float get_filt_D_alpha(float dt) const;
};
