#ifndef MMT_HPP_
#define MMT_HPP_

#include "spi.h"
#include "stm32g4xx.h"
#include "ShareMemoryMap.hpp"


class MMT{
public:
    MMT(SPI_TypeDef *_spix, GPIO_TypeDef* _csGPIO, uint32_t _csPinmsk,
		DMA_TypeDef *_dmax, uint32_t _rx_dma_ch, uint32_t _tx_dma_ch):
		SPIx_(_spix), csGPIOx_(_csGPIO), csPinmsk_(_csPinmsk),
		DMAx_(_dmax), rx_DMA_CH_(_rx_dma_ch), tx_DMA_CH_(_tx_dma_ch)
		{ 		};

    void init();

private:
	SPI_TypeDef *SPIx_;
	GPIO_TypeDef* csGPIOx_;
	uint32_t csPinmsk_;
	DMA_TypeDef* DMAx_;
	uint32_t rx_DMA_CH_;
	uint32_t tx_DMA_CH_;

    bool isSlaveMode = false;

};


#endif