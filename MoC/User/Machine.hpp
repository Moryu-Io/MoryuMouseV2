#ifndef MACHINE_HPP_
#define MACHINE_HPP_

#include "stm32g4xx.h"
#include "tim.h"

#include "Encoder.hpp"
#include "Motor.hpp"
#include "Controller.hpp"
#include "IMU.hpp"
#include "OpenMemoryMap.hpp"
#include "Position.hpp"

class Machine{
public:
    static Machine &getInstance(){
        static Machine _mc_instance;
        return _mc_instance;
    }

    enum MC_Mode{
        Standby,
        ENKAI_GEI,
        Error
    };

    void init(TIM_TypeDef *_tim, Motor* _rm, Motor* _lm, Encoder* _re, Encoder* _le, 
              PID* _c, IMU* _imu);
    void setMode(MC_Mode _m);

    void control_routine();

    void enable();
    void disable();

private:
    Machine(){}
    Machine(const Machine &other);
    Machine &operator=(const Machine &other);

    /* ペリフェラル系 */
    TIM_TypeDef* TIMx_;

    /* 他モジュールのポインタ */
    Motor* rMotor_;
    Motor* lMotor_;
    Encoder* rEnc_;
    Encoder* lEnc_;
    PID* rotCtrl_;
    IMU* imu_;

    /* Machine固有の変数 */
    MC_Mode nowMode_ = Standby;
    IMUdata imudata_;
    Position nowPos_;
    Position nowVel_;
    Position preVel_;
    float ctrl_freq_ = CONTROLL_FREQ;
    float ctrl_dt_   = CONTROLL_TIME;


    void set_OpenMemData();
};


#endif