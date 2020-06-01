#include "Machine.hpp"


void Machine::init(TIM_TypeDef *_tim, Motor* _rm, Motor* _lm, Encoder* _re, Encoder* _le, 
                   PID* _c, IMU* _imu){
    TIMx_ = _tim;

    rMotor_ = _rm;
    lMotor_ = _lm;
    rEnc_ = _re;
    lEnc_ = _le;

    rotCtrl_ = _c;

    imu_ = _imu;

    imu_->init_config();

    rEnc_->enable();
    lEnc_->enable();

    // Motor関連
    LL_TIM_EnableUpdateEvent(TIM1);
	LL_TIM_EnableCounter(TIM1);
    TIM1->BDTR |= TIM_BDTR_MOE;

    rMotor_->enable_Motor();
    lMotor_->enable_Motor();
    rMotor_->set_duty(0.0f);
    lMotor_->set_duty(0.0f);
}

void Machine::enable(){
    LL_TIM_EnableIT_UPDATE(TIMx_);
	LL_TIM_EnableCounter(TIMx_);
}

void Machine::disable(){
    LL_TIM_DisableIT_UPDATE(TIMx_);
	LL_TIM_DisableCounter(TIMx_);
}


void Machine::control_routine(){
    // 初めにIMUの取得のDMAを回しておく
    imu_->routine_config_for_get_IMUdata();

    rEnc_->update();
    lEnc_->update();


    // IMUデータの取得待ち
    while(!imu_->is_imudata_updated());
    imu_->getIMUdata(&imudata_);
    get_ptr_MoC_OpenMemory()->ptr_now_oMem->flt_accel_x = imudata_.accel_x;
    get_ptr_MoC_OpenMemory()->ptr_now_oMem->flt_accel_y = imudata_.accel_y;
    get_ptr_MoC_OpenMemory()->ptr_now_oMem->flt_gyro_z = imudata_.gyro_z;

    nowPos_.th += imudata_.gyro_z * ctrl_dt_;
    float _rot_val_duty = rotCtrl_->update(nowPos_.th );
    rMotor_->set_duty(_rot_val_duty);
    lMotor_->set_duty(-_rot_val_duty);
}