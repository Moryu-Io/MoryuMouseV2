/*
 * Encoder.hpp
 *
 *  Created on: 2019/04/14
 *      Author: Moryu
 */

#ifndef ENCODER_HPP_
#define ENCODER_HPP_

#include "stm32g4xx.h"
#include "tim.h"

class Encoder
{
public:
	Encoder(TIM_TypeDef *_tim, float _cnt2pos);

	void set_periph(TIM_TypeDef *_tim);
	void enable();

	int32_t update();
	int32_t  get_dCNT(){ return u32_now_dCNT_; };
	uint32_t get_nowCNT(){ return *u32p_enc_CNT_; };

	float get_dpos(){ return ((float)u32_now_dCNT_)*coef_conv_CNTtoPos_; };

private:
	TIM_TypeDef *TIMx_;
	uint32_t* u32p_ENC_CNT_MAX_;
	uint32_t* u32p_enc_CNT_;

	uint32_t  u32_prev_enc_CNT_ = 0;
	int32_t  u32_now_dCNT_ = 0;

	float coef_conv_CNTtoPos_;

};






#endif /* ENCODER_HPP_ */
