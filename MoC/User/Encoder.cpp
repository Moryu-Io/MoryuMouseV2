/*
 * Encoder.cpp
 *
 *  Created on: 2019/04/14
 *      Author: Moryu
 */

#include "Encoder.hpp"


Encoder::Encoder(TIM_TypeDef *_tim, float _cnt2pos):
TIMx_(_tim), coef_conv_CNTtoPos_(_cnt2pos)
{
	set_periph(_tim);
}


void Encoder::set_periph(TIM_TypeDef *_tim){
	TIMx_ = _tim;
	u32p_ENC_CNT_MAX_ 	= (uint32_t*)&(TIMx_->ARR);
	u32p_enc_CNT_		= (uint32_t*)&(TIMx_->CNT);
	u32_prev_enc_CNT_	= 0;

	enable();
}

void Encoder::enable(){
	LL_TIM_EnableCounter(TIMx_);
}

int32_t Encoder::update(){
	int32_t _dCNT = *u32p_enc_CNT_ - u32_prev_enc_CNT_;
	u32_prev_enc_CNT_ = *u32p_enc_CNT_;

	if(_dCNT > (int32_t)((*u32p_ENC_CNT_MAX_)>>1)){
		_dCNT = _dCNT - *u32p_ENC_CNT_MAX_;
	}else if(_dCNT < -(int32_t)((*u32p_ENC_CNT_MAX_)>>1)){
		_dCNT = _dCNT + *u32p_ENC_CNT_MAX_;
	}

	u32_now_dCNT_ = _dCNT;

	return _dCNT;
}

