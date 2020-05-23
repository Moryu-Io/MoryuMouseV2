#ifndef MMT_HPP_
#define MMT_HPP_

#include "spi.h"
#include "stm32g4xx.h"
#include "OpenMemoryMap.hpp"
#include "def_const_param.hpp"


class MMT_M{
public:
	static MMT_M &getInstance(){
		static MMT_M _mmt_instance;
		return _mmt_instance;
	}

	enum MMT_Mode{
		Single,
		OpenMemory
	};

	void set_periph(SPI_TypeDef *_spix, GPIO_TypeDef* _csGPIO, uint32_t _csPinmsk,
					DMA_TypeDef *_dmax, uint32_t _rx_dma_ch, uint32_t _tx_dma_ch);
    void init(MMT_Mode _m);
	void enable_transfer();

	void set_single_TXdata(uint8_t);

	void rx_halfcplt_routine();
	void rx_cplt_routine();
	void tx_cplt_routine();
	void error_handler();

private:
	MMT_M(){}
	MMT_M(const MMT_M &other);
	MMT_M &operator=(const MMT_M &other);

	SPI_TypeDef *SPIx_;
	GPIO_TypeDef* csGPIOx_;
	uint32_t csPinmsk_;
	DMA_TypeDef* DMAx_;
	uint32_t rx_DMA_CH_;
	uint32_t tx_DMA_CH_;

	uint16_t _single_tx_buf = MMT_MASTER_WHO_AM_I;
	uint16_t _single_rx_buf[2] = {};		//CRC分

	void select();
	void deselect();

	MMT_Mode nowMode_ = Single;

	MoC_OpenMemory* ptr_moc_OpenMemory_;
	MaSoC_OpenMemory* ptr_masoc_OpenMemory_;

	DMA_Channel_TypeDef *dma_rx_ch_def = DMA2_Channel1;
	DMA_Channel_TypeDef *dma_tx_ch_def = DMA2_Channel2;
};


#endif