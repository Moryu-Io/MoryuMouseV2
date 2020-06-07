#include "WallSensor_PD.hpp"


namespace WST{


void WallSensorPD::update(){
    /* センサ値の処理 */


    /*  */
}


void WallSensorPD::init(){
    /* adc用のdma初期化 */
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_3,
						   LL_ADC_DMA_GetRegAddr(ADC1,LL_ADC_DMA_REG_REGULAR_DATA),(uint32_t)u16_adc1_buf,
						   LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_3));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, 2);	
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_4,
						   LL_ADC_DMA_GetRegAddr(ADC2,LL_ADC_DMA_REG_REGULAR_DATA),(uint32_t)u16_adc2_buf,
						   LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, 2);

    LL_OPAMP_SetPGAGain(OPAMP1, LL_OPAMP_PGA_GAIN_32_OR_MINUS_31);
    LL_OPAMP_SetPGAGain(OPAMP2, LL_OPAMP_PGA_GAIN_32_OR_MINUS_31);
    LL_OPAMP_SetPGAGain(OPAMP3, LL_OPAMP_PGA_GAIN_32_OR_MINUS_31);
    LL_OPAMP_SetPGAGain(OPAMP4, LL_OPAMP_PGA_GAIN_32_OR_MINUS_31);

    /* 赤外線LED用のTimerPWM初期化 */
    TIM4->CNT = 0;
    TIM4->CCR1 = 20;
    TIM4->CCR2 = 20;
    TIM4->CCR4 = 10;
}

void WallSensorPD::enable(){
    LL_OPAMP_Enable(OPAMP1);
    LL_OPAMP_Enable(OPAMP2);
    LL_OPAMP_Enable(OPAMP3);
    LL_OPAMP_Enable(OPAMP4);

    LL_ADC_Enable(ADC1);
    LL_ADC_Enable(ADC2);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);
    LL_ADC_REG_StartConversion(ADC1);
    LL_ADC_REG_StartConversion(ADC2);

	LL_TIM_EnableCounter(TIM4);
    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH2 | LL_TIM_CHANNEL_CH4);
}

void WallSensorPD::disable(){
	LL_TIM_DisableCounter(TIM4);
    LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH2 | LL_TIM_CHANNEL_CH4);

    LL_ADC_REG_StopConversion(ADC1);
    LL_ADC_REG_StopConversion(ADC2);

    LL_OPAMP_Disable(OPAMP1);
    LL_OPAMP_Disable(OPAMP2);
    LL_OPAMP_Disable(OPAMP3);
    LL_OPAMP_Disable(OPAMP4);

    LL_ADC_Disable(ADC1);
    LL_ADC_Disable(ADC2);
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);
}

void WallSensorPD::change_ampgain(WS_Dire _dir, uint32_t _g){
    switch (_dir)
    {
    case R_Front:  LL_OPAMP_SetPGAGain(OPAMP1, _g);    break;
    case R_Side:   LL_OPAMP_SetPGAGain(OPAMP4, _g);    break;
    case L_Front:  LL_OPAMP_SetPGAGain(OPAMP3, _g);    break;
    case L_Side:   LL_OPAMP_SetPGAGain(OPAMP2, _g);    break;
    default:                                           break;
    }
}

void WallSensorPD::get_raw_adc(uint16_t* _d){
    _d[R_Front] = u16_adc1_buf[0];
    _d[R_Side] = u16_adc1_buf[1];
    _d[L_Front] = u16_adc2_buf[0];
    _d[L_Side] = u16_adc2_buf[1];
}




};