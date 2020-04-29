/*
 * IMU.cpp
 *
 *  Created on: 2019/04/14
 *      Author: Moryu
 */

#include "IMU.hpp"
#include "wrapper_interrupt.hpp"

const float LSBtoGYRO 	= 1.0f/16.4f/180.0f*3.14f;			// LSB �� rad/s
const float LSBtoACCEL 	= 1.0f/8192.0f*9806.0f;			// LSB �� mm/s^2
const float LSBtoTEMP 	= 1.0f/333.87f;					// LSB �� deg

void IMU::getIMUdata(IMUdata* _imudata){
	uint8_t _u8_accel[4] = {};
	uint8_t _u8_gyrotemp[4] = {};
	ReadBytes(0x2D, _u8_accel, 4);
	ReadBytes(0x37, _u8_gyrotemp,4);
	int16_t _s16_hoge = (int16_t)(((uint16_t)_u8_accel[0]<<8) | (uint16_t) _u8_accel[1]);
	_imudata->accel_x = (float)_s16_hoge * LSBtoACCEL;

	_s16_hoge = (int16_t)(((uint16_t)_u8_accel[2]<<8) | (uint16_t) _u8_accel[3]);
	_imudata->accel_y = (float)_s16_hoge * LSBtoACCEL;

	_s16_hoge = (int16_t)(((uint16_t)_u8_gyrotemp[0]<<8) | (uint16_t) _u8_gyrotemp[1]);
	_imudata->gyro_z = (float)_s16_hoge * LSBtoGYRO;

	_s16_hoge = (int16_t)(((uint16_t)_u8_gyrotemp[2]<<8) | (uint16_t) _u8_gyrotemp[3]);
	_imudata->temp = (float)(_s16_hoge - 21) * LSBtoTEMP + 21.0f;
}

void IMU::routine_config(){
	// 受信DMAの設定
	LL_DMA_ConfigAddresses(DMAx_, rx_DMA_CH_,
						   LL_SPI_DMA_GetRegAddr(SPIx_),(uint32_t)(this->rxbuffer_),
						   LL_DMA_GetDataTransferDirection(DMAx_, rx_DMA_CH_));
	LL_DMA_SetDataLength(DMAx_, rx_DMA_CH_, 14);

	// 送信DMAの設定
	LL_DMA_ConfigAddresses(DMAx_, tx_DMA_CH_, 
						   (uint32_t)(this->txbuffer_),LL_SPI_DMA_GetRegAddr(SPIx_),
                           LL_DMA_GetDataTransferDirection(DMAx_, tx_DMA_CH_));
	LL_DMA_SetDataLength(DMAx_, tx_DMA_CH_, 14);

	


}

void IMU::getwhoamI(){
	uint8_t _rxdata[6]={};

	ReadBytes(0x00, _rxdata, 6);

	for(int i=0;i<6;i++){
		//xprintf("%x,",_rxdata[i]);
	}
	//xprintf("\n");
}

void IMU::init_config(){
	this->dma_config();

	WriteByte(0x03, 0b00010000);
	//osDelay(10);
	WriteByte(0x06, 0b00000001);
	//osDelay(10);
	WriteByte(0x05, 0b00000000);
	//osDelay(10);

	ChangeBank(2);
	//osDelay(10);
	WriteByte(0x01, 0b00000111);	// ジャイロ2000dps, DLPF on
	//osDelay(10);
	WriteByte(0x14, 0b00000011);	// 加速度4g, DLPF on
	//osDelay(10);
	WriteByte(0x53, 0b00000101);	// temp config, DLPF on
	//osDelay(10);
	
	ChangeBank(0);
}

void IMU::ChangeBank(uint8_t _banknumber){
	if(_banknumber > 3) return;
	WriteByte(0x7F, _banknumber << 4);
}

void IMU::WriteByte(uint8_t _index, uint8_t _data){
	this->select();

	spiSendByte(0b00000000 | _index);
	spiSendByte(_data);

	this->deselect();
}

uint8_t IMU::ReadByte(uint8_t _index){
	this->select();

	spiSendByte(0b10000000 | _index);
	uint8_t _u8_rxdata = spiSendByte(0xFF);

	this->deselect();

	return _u8_rxdata;
}

void IMU::ReadBytes(uint8_t _startindex, uint8_t* _rdata, int _readnum){
	this->select();

	spiSendByte(0b10000000 | _startindex);

	for(int i=0;i<_readnum;i++){
		_rdata[i] = spiSendByte(0xFF);
	}

	this->deselect();
}

uint8_t IMU::spiSendByte(uint8_t _data){
	//while(LL_DMA_IsActiveFlag_TC2(DMAx_));
	this->txbuffer_[0] = _data;

	LL_DMA_SetDataLength(DMAx_, rx_DMA_CH_, 1);
	LL_DMA_SetDataLength(DMAx_, tx_DMA_CH_, 1);

	// DMA RX リクエストを有効化
	LL_SPI_EnableDMAReq_RX(SPIx_);

	// DMAを有効化
	LL_DMA_EnableChannel(DMAx_, tx_DMA_CH_);
	LL_DMA_EnableChannel(DMAx_, rx_DMA_CH_);

	// DMA TX リクエストを有効化
	LL_SPI_EnableDMAReq_TX(SPIx_);

	while(!this->is_tx_dma_TC());
	while(!this->is_rx_dma_TC());

	// DMAを無効化
	LL_DMA_DisableChannel(DMAx_, tx_DMA_CH_);
	LL_DMA_DisableChannel(DMAx_, rx_DMA_CH_);
	LL_SPI_DisableDMAReq_RX(SPIx_);
	LL_SPI_DisableDMAReq_TX(SPIx_);

	clear_SPI3_RX_DMA_TC();
	clear_SPI3_TX_DMA_TC();

	return this->rxbuffer_[0];
}


void IMU::dma_config(){
	// 受信DMAの設定
	LL_DMA_ConfigAddresses(DMAx_, rx_DMA_CH_,
						   LL_SPI_DMA_GetRegAddr(SPIx_),(uint32_t)(this->rxbuffer_),
						   LL_DMA_GetDataTransferDirection(DMAx_, rx_DMA_CH_));
	LL_DMA_SetDataLength(DMAx_, rx_DMA_CH_, 1);

	// 送信DMAの設定
	LL_DMA_ConfigAddresses(DMAx_, tx_DMA_CH_, 
						   (uint32_t)(this->txbuffer_),LL_SPI_DMA_GetRegAddr(SPIx_),
                           LL_DMA_GetDataTransferDirection(DMAx_, tx_DMA_CH_));
	LL_DMA_SetDataLength(DMAx_, tx_DMA_CH_, 1);

	if(SPIx_ == SPI1){
		LL_DMA_SetPeriphRequest(DMAx_, rx_DMA_CH_, LL_DMAMUX_REQ_SPI1_RX);
		LL_DMA_SetPeriphRequest(DMAx_, tx_DMA_CH_, LL_DMAMUX_REQ_SPI1_TX);
	}else if(SPIx_ == SPI2){
		LL_DMA_SetPeriphRequest(DMAx_, rx_DMA_CH_, LL_DMAMUX_REQ_SPI2_RX);
		LL_DMA_SetPeriphRequest(DMAx_, tx_DMA_CH_, LL_DMAMUX_REQ_SPI2_TX);
	}else if(SPIx_ == SPI3){
		LL_DMA_SetPeriphRequest(DMAx_, rx_DMA_CH_, LL_DMAMUX_REQ_SPI3_RX);
		LL_DMA_SetPeriphRequest(DMAx_, tx_DMA_CH_, LL_DMAMUX_REQ_SPI3_TX);		
	}

	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_2);

	LL_SPI_SetDMAParity_TX(SPIx_, LL_SPI_DMA_PARITY_ODD);
	LL_SPI_SetDMAParity_RX(SPIx_, LL_SPI_DMA_PARITY_ODD);

    LL_SPI_SetRxFIFOThreshold(SPIx_, LL_SPI_RX_FIFO_TH_QUARTER);
	LL_SPI_Enable(SPIx_);
}


bool IMU::is_rx_dma_TC(){
	return is_SPI3_RX_DMA_TC();
}
bool IMU::is_tx_dma_TC(){
	return is_SPI3_TX_DMA_TC();
}