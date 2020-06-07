#include "Machine.hpp"
#include "mymath.hpp"
#include "tim_counter.hpp"

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

    // 初期位置設定
    nowPos_.x = 0.0f;
    nowPos_.y = 0.0f;
    nowPos_.th = PI/2;

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
    uint32_t u32_ctrl_start_time_us = T_CNT::get_nowCount_us();

    // 初めにIMUの取得のDMAを回しておく
    imu_->routine_config_for_get_IMUdata();

    rEnc_->update();
    lEnc_->update();

    /* 目標位置算出 */


    /* 自己位置推定 */
    // IMUデータの取得待ち
    while((!imu_->is_imudata_updated())
          && ((T_CNT::get_nowCount_us() - u32_ctrl_start_time_us) < 50));
    if(imu_->is_imudata_updated()){
        imu_->getIMUdata(&imudata_);
    }else{
        imu_->rx_dma_TC();
    }

    // 角度
    nowVel_.th = imudata_.gyro_z;
    nowPos_.th += (preVel_.th + nowVel_.th)*0.5*ctrl_dt_;
    nowPos_.th = mymath::normalize_rad_0to2pi(nowPos_.th);
    preVel_.th = nowVel_.th;

    // 並進量
    float _vel = (rEnc_->get_dpos() + lEnc_->get_dpos())*0.5f;
    float _sin = 0.0f;
    float _cos = 0.0f;
    arm_sin_cos_f32(mymath::rad2deg(nowPos_.th), &_sin, &_cos);
    nowVel_.x = _vel*_cos;
    nowVel_.y = _vel*_sin;

    nowPos_.x += nowVel_.x;
    nowPos_.y += nowVel_.y;


    /* 制御量の計算 */
    float _rot_val_duty = rotCtrl_->update(nowPos_.th );


    // Motorへの電圧入力
    //rMotor_->set_duty(_rot_val_duty);
    //lMotor_->set_duty(-_rot_val_duty);


    set_OpenMemData();
    
    uint32_t delta_us = T_CNT::get_nowCount_us();
    //prev_us = TIM7->CNT;
    _rot_val_duty=0.0f;
}


void Machine::set_OpenMemData(){
    /* OpenMemoryの値を配置 */
    MoC_OpenMemoryMap* _ptr_moc_mem = get_ptr_MoC_OpenMemory()->ptr_now_oMem;
    _ptr_moc_mem->flt_nowAccel_X = imudata_.accel_x;
    _ptr_moc_mem->flt_nowAccel_Y = imudata_.accel_y;
    _ptr_moc_mem->flt_nowGyro_Z = imudata_.gyro_z;
    _ptr_moc_mem->flt_nowPos_X = nowPos_.x;
    _ptr_moc_mem->flt_nowPos_Y = nowPos_.y;
    _ptr_moc_mem->flt_nowVel_X = nowVel_.x;
    _ptr_moc_mem->flt_nowVel_Y = nowVel_.y;
    _ptr_moc_mem->flt_nowPos_THETA = nowPos_.th;
    _ptr_moc_mem->u16_rEncCNT = rEnc_->get_nowCNT();
    _ptr_moc_mem->u16_lEncCNT = lEnc_->get_nowCNT();

}