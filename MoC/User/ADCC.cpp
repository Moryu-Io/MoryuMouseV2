#include "ADCC.hpp"


void ADCC::init(){
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_3,
							   LL_ADC_DMA_GetRegAddr(ADC1,LL_ADC_DMA_REG_REGULAR_DATA),(uint32_t)&(adc1_data),
							   LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_3));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, 1);	
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_4,
							   LL_ADC_DMA_GetRegAddr(ADC2,LL_ADC_DMA_REG_REGULAR_DATA),(uint32_t)&(adc2_data),
							   LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, 1);	
    LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_3, LL_DMAMUX_REQ_ADC1);
    LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_4, LL_DMAMUX_REQ_ADC2);
    
    LL_OPAMP_Enable(OPAMP1);
    LL_OPAMP_Enable(OPAMP2); 
    LL_ADC_Enable(ADC1);
    LL_ADC_Enable(ADC2);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);
    LL_ADC_REG_StartConversion(ADC1);
    LL_ADC_REG_StartConversion(ADC2);
}