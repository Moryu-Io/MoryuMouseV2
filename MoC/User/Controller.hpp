#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "stm32g4xx.h"

class Controller{
public:
    Controller(float _c_freq):
    freq_(_c_freq), dt_(1.0f/_c_freq){};
    
    virtual float update(float _nowval) = 0;
    virtual void reset() = 0;

    void set_target(float _tgtval){ now_tgt_ = _tgtval; };

protected:
    float freq_ = 1.0f;
    float dt_ = 1.0f;

    float now_val_ = 0.0f;
    float prev_val_ = 0.0f;
    float now_tgt_ = 0.0f;

    float now_error_ = 0.0f;
    float prev_error_ = 0.0f;

    float now_ctrl_ = 0.0f;
};


class PID : Controller{
public:
    PID(float _c_freq, float _p_gain, float _i_gain, float _d_gain,
        float _i_limit):
        Controller(_c_freq), Pgain_(_p_gain), Igain_(_i_gain), Dgain_(_d_gain),
        I_limit_(_i_limit){};

    float update(float _nowval) override;
    void  reset() override;

    void  set_PIDgain(float _pg, float _ig, float _dg);
    void  set_I_limit(float _i_lim){ I_limit_ = _i_lim; };

private:
    float Pgain_ = 0.0f;
    float Igain_ = 0.0f;
    float Dgain_ = 0.0f;

    float Integ_ = 0.0f;
    float I_limit_ = 0.0f;
};


#endif