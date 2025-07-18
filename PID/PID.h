#pragma once

// default PID values for testings
#define TEST_P 0.5f
#define TEST_I 0.1f
#define TEST_D 0.05f

class PID_Controller
{
    public:
        PID_Controller(float kp, float ki, float kd);

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
        float get_error() const { return _error; }
        void reset_i() { _integrator = 0.0f;}
        float update(float setpoint, float measured, float dt);

    private:
        float _kp;
        float _ki;
        float _kd;
        float _filt_E_hz;           // PID error filter frequency in Hz
        float _filt_D_hz;           // PID derivative filter frequency in Hz
        
        float _error;               // error value to enable filtering
        float _derivative;          // Last derivative to Low-Pass filter
        float _integrator;
        float _last_error;

        float get_filt_E_alpha(float dt) const;
        float get_filt_D_alpha(float dt) const;
};
