/*
 * Motor.hpp
 *
 *  Created on: 2019/04/14
 *      Author: Moryu
 */

#ifndef MOTOR_HPP_
#define MOTOR_HPP_

#include "gpio.h"
#include "stm32g4xx.h"

class Motor{
public:
	Motor(uint32_t* _u32p_pwmcntmax,
			  uint32_t* _u32p_ccer, uint32_t  _u32_cnls,
			  uint32_t* _u32p_fccr, uint32_t* _u32p_iccr);

	void set_periph(uint32_t* _u32p_pwmcntmax,
			  uint32_t* _u32p_ccer, uint32_t  _u32_cnls,
			  uint32_t* _u32p_fccr, uint32_t* _u32p_iccr);

	void set_VM(float _fl_vm){ fl_VM_ = _fl_vm; fl_invVM_ = 1.0f/_fl_vm; };

	void set_duty(float _d);
	void set_voltage(float _v);

	float get_nowdrvVol(){ return fl_drvVol_; };

	void enable_Motor();
	void disable_Motor();

private:
	uint32_t* u32p_PWM_CNT_MAX_;
	uint32_t* u32p_CCR_Enable_Register_;
	uint32_t  u32_PWM_Channels_;
	uint32_t* u32p_forwardCCR_;
	uint32_t* u32p_inverseCCR_;

	float fl_VM_;
	float fl_invVM_;
	float fl_drvVol_;
};






#endif /* MOTOR_HPP_ */
