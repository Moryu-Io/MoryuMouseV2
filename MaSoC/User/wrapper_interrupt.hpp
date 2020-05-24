#ifndef WRAPPER_INTERRUPT_HPP_
#define WRAPPER_INTERRUPT_HPP_


#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g4xx.h"

void SPI1_RX_DMA_TC();
void SPI1_TX_DMA_TC();
void SPI1_ERROR_ITR();

#ifdef __cplusplus
}
#endif



#endif