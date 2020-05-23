#ifndef WRAPPER_INTERRUPT_HPP_
#define WRAPPER_INTERRUPT_HPP_


#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g4xx.h"


void set_SPI3_RX_DMA_TC();
void set_SPI3_TX_DMA_TC();

void clear_SPI3_TX_DMA_TC();
void clear_SPI3_RX_DMA_TC();

uint8_t is_SPI3_RX_DMA_TC();
uint8_t is_SPI3_TX_DMA_TC();

void SPI1_RX_DMA_HT();
void SPI1_RX_DMA_TC();
void SPI1_TX_DMA_TC();
void SPI1_ERROR_ITR();

#ifdef __cplusplus
}
#endif



#endif