#include "Controller.hpp"



void PID::reset(){
    Integ_ = 0.0f;

    now_val_ = 0.0f;
    prev_val_ = 0.0f;
    now_tgt_ = 0.0f;
    now_error_ = 0.0f;
    prev_error_ = 0.0f;

    now_ctrl_ = 0.0f;
}


float PID::update(float _nowval){
    now_val_ = _nowval;
    now_error_ = now_tgt_ - now_val_;
    
    // 積分計算
    Integ_ += Igain_ * now_error_ * dt_;
    Integ_ = (Integ_ >= I_limit_) ? I_limit_ : 
             ((Integ_ <= -I_limit_) ? -I_limit_ : Integ_);

    // 制御量計算
    now_ctrl_ = Pgain_ * now_error_ + Igain_ * Integ_;

    prev_val_ = now_val_;
    prev_error_ = now_error_;

    return now_ctrl_;
}

void PID::set_PIDgain(float _pg, float _ig, float _dg){
    Pgain_ = _pg;
    Igain_ = _ig;
    Dgain_ = _dg;
}
