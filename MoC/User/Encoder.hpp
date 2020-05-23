/*
 * Encoder.hpp
 *
 *  Created on: 2019/04/14
 *      Author: Moryu
 */

#ifndef ENCODER_HPP_
#define ENCODER_HPP_

#include "stm32g4xx.h"

class Encoder
{
public:
	Encoder(uint32_t* _u32p_enccntmax, uint32_t* _u32p_enccnt, float _cnt2pos);

	void set_periph(uint32_t* _u32p_enccntmax, uint32_t* _u32p_enccnt);

	int32_t  get_dCNT();
	uint32_t get_nowCNT(){ return *u32p_enc_CNT_; };

	float get_dpos();

private:
	uint32_t* u32p_ENC_CNT_MAX_;
	uint32_t* u32p_enc_CNT_;
	uint32_t  u32_prev_enc_CNT_;

	float coef_conv_CNTtoPos_;

};






#endif /* ENCODER_HPP_ */
