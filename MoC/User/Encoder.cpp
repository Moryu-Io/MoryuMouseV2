/*
 * Encoder.cpp
 *
 *  Created on: 2019/04/14
 *      Author: Moryu
 */

#include "Encoder.hpp"


Encoder::Encoder(uint32_t* _u32p_enccntmax, uint32_t* _u32p_enccnt, float _cnt2pos):
u32p_ENC_CNT_MAX_(_u32p_enccntmax), u32p_enc_CNT_(_u32p_enccnt),
u32_prev_enc_CNT_(0), coef_conv_CNTtoPos_(_cnt2pos)
{

}


void Encoder::set_periph(uint32_t* _u32p_enccntmax, uint32_t* _u32p_enccnt){
	u32p_ENC_CNT_MAX_ 	= _u32p_enccntmax;
	u32p_enc_CNT_		= _u32p_enccnt;
	u32_prev_enc_CNT_	= 0;

}


int32_t Encoder::get_dCNT(){
	int32_t _dCNT = *u32p_enc_CNT_ - u32_prev_enc_CNT_;
	u32_prev_enc_CNT_ = *u32p_enc_CNT_;

	if(_dCNT > (int32_t)((*u32p_ENC_CNT_MAX_)>>1)){
		_dCNT = _dCNT - *u32p_ENC_CNT_MAX_;
	}else if(_dCNT < -(int32_t)((*u32p_ENC_CNT_MAX_)>>1)){
		_dCNT = _dCNT + *u32p_ENC_CNT_MAX_;
	}

	return _dCNT;

}


float Encoder::get_dpos(){
	return (float)get_dCNT()*coef_conv_CNTtoPos_;
}
