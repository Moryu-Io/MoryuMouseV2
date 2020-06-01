/*
 * IMU.hpp
 *
 *  Created on: 2019/04/14
 *      Author: Moryu
 */

#ifndef IMU_HPP_
#define IMU_HPP_

#include "spi.h"
#include "stm32g4xx.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

struct IMUdata{
	float accel_x;
	float accel_y;
	float gyro_z;
	float temp;
};


class IMU{
public:
	IMU(SPI_TypeDef *_spix, GPIO_TypeDef* _csGPIO, uint32_t _csPinmsk,
		DMA_TypeDef *_dmax, uint32_t _rx_dma_ch, uint32_t _tx_dma_ch):
		SPIx_(_spix), csGPIOx_(_csGPIO), csPinmsk_(_csPinmsk),
		DMAx_(_dmax), rx_DMA_CH_(_rx_dma_ch), tx_DMA_CH_(_tx_dma_ch)
		{ 		};

	void getIMUdata(IMUdata* _imudata);
	bool is_imudata_updated(){ return is_IMUdata_Updated; };

	void routine_config_for_get_IMUdata();

	void getwhoamI();
	void init_config();

	void dma_config();
	void rx_dma_TC();
	void tx_dma_TC();

private:
	SPI_TypeDef *SPIx_;
	GPIO_TypeDef* csGPIOx_;
	uint32_t csPinmsk_;
	DMA_TypeDef* DMAx_;
	uint32_t rx_DMA_CH_;
	uint32_t tx_DMA_CH_;
	bool is_rxDMA_completed = false;
	bool is_txDMA_completed = false;

	uint8_t rxbuffer_[16] = {};
	uint8_t txbuffer_[16] = {};

	void ChangeBank(uint8_t _banknumber);

	void WriteByte(uint8_t _index, uint8_t _data);
	uint8_t ReadByte(uint8_t _index);
	void ReadBytes(uint8_t _startindex, uint8_t* _rdata, int _readnum);

	uint8_t spiSendByte(uint8_t _data);
	void select(){LL_GPIO_ResetOutputPin(csGPIOx_, csPinmsk_);}
	void deselect(){LL_GPIO_SetOutputPin(csGPIOx_, csPinmsk_);}

	bool is_IMUdata_Updated = false;
	bool is_IMUdata_Routine = false;

};



IMU* get_ptr_IMU();


#endif /* IMU_HPP_ */
