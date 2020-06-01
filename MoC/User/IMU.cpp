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
	int16_t _s16_hoge = (int16_t)(((uint16_t)rxbuffer_[1]<<8) | (uint16_t) rxbuffer_[2]);
	_imudata->accel_x = -(float)_s16_hoge * LSBtoACCEL;

	_s16_hoge = (int16_t)(((uint16_t)rxbuffer_[3]<<8) | (uint16_t) rxbuffer_[4]);
	_imudata->accel_y = -(float)_s16_hoge * LSBtoACCEL;

	_s16_hoge = (int16_t)(((uint16_t)rxbuffer_[11]<<8) | (uint16_t) rxbuffer_[12]);
	_imudata->gyro_z = (float)_s16_hoge * LSBtoGYRO;

	_s16_hoge = (int16_t)(((uint16_t)rxbuffer_[13]<<8) | (uint16_t) rxbuffer_[14]);
	_imudata->temp = (float)(_s16_hoge - 21) * LSBtoTEMP + 21.0f;

	is_IMUdata_Updated = false;
}

void IMU::routine_config_for_get_IMUdata(){
	is_rxDMA_completed = false;
	is_txDMA_completed = false;
	is_IMUdata_Updated = false;
	is_IMUdata_Routine = true;

	txbuffer_[0] = 0b10000000 | 0x2D;
	for(int i=1;i<15;i++){
		txbuffer_[i] = 0xFF;
	}
	// 受信DMAの設定
	LL_DMA_ConfigAddresses(DMAx_, rx_DMA_CH_,
						   LL_SPI_DMA_GetRegAddr(SPIx_),(uint32_t)(this->rxbuffer_),
						   LL_DMA_GetDataTransferDirection(DMAx_, rx_DMA_CH_));
	LL_DMA_SetDataLength(DMAx_, rx_DMA_CH_, 15);

	// 送信DMAの設定
	LL_DMA_ConfigAddresses(DMAx_, tx_DMA_CH_, 
						   (uint32_t)(this->txbuffer_),LL_SPI_DMA_GetRegAddr(SPIx_),
                           LL_DMA_GetDataTransferDirection(DMAx_, tx_DMA_CH_));
	LL_DMA_SetDataLength(DMAx_, tx_DMA_CH_, 15);


	this->select();

	// DMA RX リクエストを有効化
	LL_SPI_EnableDMAReq_RX(SPIx_);

	// DMAを有効化
	LL_DMA_EnableChannel(DMAx_, tx_DMA_CH_);
	LL_DMA_EnableChannel(DMAx_, rx_DMA_CH_);

	// DMA TX リクエストを有効化
	LL_SPI_EnableDMAReq_TX(SPIx_);

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
	LL_mDelay(10);
	//osDelay(10);
	WriteByte(0x06, 0b00000001);
	LL_mDelay(10);
	//osDelay(10);
	WriteByte(0x05, 0b00000000);
	LL_mDelay(10);
	//osDelay(10);

	ChangeBank(2);
	LL_mDelay(10);
	//osDelay(10);
	WriteByte(0x01, 0b00000111);	// ジャイロ2000dps, DLPF on
	LL_mDelay(10);
	//osDelay(10);
	WriteByte(0x14, 0b00000011);	// 加速度4g, DLPF on
	LL_mDelay(10);
	//osDelay(10);
	WriteByte(0x53, 0b00000101);	// temp config, DLPF on
	LL_mDelay(10);
	//osDelay(10);
	
	ChangeBank(0);
	LL_mDelay(10);
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
	is_IMUdata_Routine = false;
	//while(LL_DMA_IsActiveFlag_TC2(DMAx_));
	this->txbuffer_[0] = _data;

	is_rxDMA_completed = false;
	is_txDMA_completed = false;
	LL_DMA_SetDataLength(DMAx_, rx_DMA_CH_, 1);
	LL_DMA_SetDataLength(DMAx_, tx_DMA_CH_, 1);

	// DMA RX リクエストを有効化
	LL_SPI_EnableDMAReq_RX(SPIx_);

	// DMAを有効化
	LL_DMA_EnableChannel(DMAx_, tx_DMA_CH_);
	LL_DMA_EnableChannel(DMAx_, rx_DMA_CH_);

	// DMA TX リクエストを有効化
	LL_SPI_EnableDMAReq_TX(SPIx_);

	while(!this->is_txDMA_completed);
	while(!this->is_rxDMA_completed);

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


void IMU::rx_dma_TC(){
	if(is_IMUdata_Routine)	this->deselect();
	LL_DMA_DisableChannel(DMAx_, tx_DMA_CH_);
	LL_DMA_DisableChannel(DMAx_, rx_DMA_CH_);
	LL_SPI_DisableDMAReq_RX(SPIx_);
	LL_SPI_DisableDMAReq_TX(SPIx_);

	is_rxDMA_completed = true;
	is_IMUdata_Updated = true;
	is_IMUdata_Routine = false;
}
void IMU::tx_dma_TC(){
	is_txDMA_completed = true;
}



static IMU imu(SPI3, GPIOF, LL_GPIO_PIN_1, DMA1, LL_DMA_CHANNEL_1, LL_DMA_CHANNEL_2);
IMU* get_ptr_IMU(){return &imu;};