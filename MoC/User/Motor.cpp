/*
 * Motor.cpp
 *
 *  Created on: 2019/04/14
 *      Author: Moryu
 */

#include "Motor.hpp"

Motor::Motor(uint32_t* _u32p_pwmcntmax,
		  uint32_t* _u32p_ccer, uint32_t  _u32_cnls,
		  uint32_t* _u32p_fccr, uint32_t* _u32p_iccr):
u32p_PWM_CNT_MAX_(_u32p_pwmcntmax),
u32p_CCR_Enable_Register_(_u32p_ccer),u32_PWM_Channels_(_u32_cnls),
u32p_forwardCCR_(_u32p_fccr),u32p_inverseCCR_(_u32p_iccr),
fl_VM_(4.2f),fl_invVM_(1.0f/4.2f),fl_drvVol_(0.0f)
{

}

void Motor::set_periph(uint32_t* _u32p_pwmcntmax,
			  uint32_t* _u32p_ccer, uint32_t  _u32_cnls,
			  uint32_t* _u32p_fccr, uint32_t* _u32p_iccr){
	u32p_PWM_CNT_MAX_ 			= _u32p_pwmcntmax;
	u32p_CCR_Enable_Register_ 	= _u32p_ccer;
	u32_PWM_Channels_ 			= _u32_cnls;
	u32p_forwardCCR_ 			= _u32p_fccr;
	u32p_inverseCCR_ 			= _u32p_iccr;
}


void Motor::set_duty(float _d){
	if(_d > 1.0f) 		_d =  1.0f;
	else if(_d < -1.0f) _d = -1.0f;

	fl_drvVol_ = _d*fl_VM_;

	if(_d >= 0.0f){
		*u32p_forwardCCR_ = (uint32_t) (_d * (float)(*u32p_PWM_CNT_MAX_));
		*u32p_inverseCCR_ = 0;
	}else{
		*u32p_forwardCCR_ = 0;
		*u32p_inverseCCR_ = (uint32_t) (-_d * (float)(*u32p_PWM_CNT_MAX_));
	}
}

void Motor::set_voltage(float _v){
	float _duty = _v*fl_invVM_;
	set_duty(_duty);
}

void Motor::enable_Motor(){
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_12);	// �h���C�o��NSLEEP����
	SET_BIT(*(u32p_CCR_Enable_Register_), u32_PWM_Channels_);
}

void Motor::disable_Motor(){
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_12);	// �h���C�o��NSLEEP�L����
	CLEAR_BIT(*(u32p_CCR_Enable_Register_), u32_PWM_Channels_);
}
