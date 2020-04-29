/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* I2C2 init function */
void MX_I2C2_Init(void)
{
  LL_I2C_InitTypeDef I2C_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**I2C2 GPIO Configuration  
  PA8   ------> I2C2_SDA
  PA9   ------> I2C2_SCL 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);

  /* I2C2 DMA Init */
  
  /* I2C2_RX Init */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_I2C2_RX);

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_LOW);

  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_BYTE);

  /* I2C2_TX Init */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMAMUX_REQ_I2C2_TX);

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_LOW);

  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_BYTE);

  /** I2C Initialization 
  */
  I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
  I2C_InitStruct.Timing = 0x00A039C6;
  I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
  I2C_InitStruct.DigitalFilter = 0;
  I2C_InitStruct.OwnAddress1 = 0;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
  I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
  LL_I2C_Init(I2C2, &I2C_InitStruct);
  LL_I2C_EnableAutoEndMode(I2C2);
  LL_I2C_SetOwnAddress2(I2C2, 0, LL_I2C_OWNADDRESS2_NOMASK);
  LL_I2C_DisableOwnAddress2(I2C2);
  LL_I2C_DisableGeneralCall(I2C2);
  LL_I2C_EnableClockStretching(I2C2);

}

/* USER CODE BEGIN 1 */
void I2C_DMA_Writes(uint8_t _slaveaddr, uint8_t* _dataaddr, uint32_t _datanum){
	//LL_I2C_Enable(I2C2);
  LL_I2C_HandleTransfer(I2C1, _slaveaddr, LL_I2C_ADDRSLAVE_7BIT, _datanum, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
  while (!LL_I2C_IsActiveFlag_STOP(I2C1))
  {
    /* (2.1) Transmit data (TXIS flag raised) *********************************/

    /* Check TXIS flag value in ISR register */
    if (LL_I2C_IsActiveFlag_TXIS(I2C1))
    {
      /* Write data in Transmit Data register.
      TXIS flag is cleared by writing data in TXDR register */
      LL_I2C_TransmitData8(I2C2, (*_dataaddr++));
    }
  }
  LL_I2C_ClearFlag_STOP(I2C1);

/*
	// I2C_FLAG_BUSY
	while(LL_I2C_IsActiveFlag_BUSY(I2C2));
	LL_I2C_Enable(I2C2);
  LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
	while(LL_DMA_IsEnabledStream(DMA1, LL_DMA_CHANNEL_2));

	LL_I2C_GenerateStartCondition(I2C2);
	// I2C_EVENT_MASTER_MODE_SELECT
	while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
			&& LL_I2C_IsActiveFlag_SB(I2C2)
			&& LL_I2C_IsActiveFlag_MSL(I2C2)));

	LL_I2C_TransmitData8(I2C2,_slaveaddr);

	// I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED
	while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
			&& LL_I2C_IsActiveFlag_ADDR(I2C2)
			&& LL_I2C_IsActiveFlag_TXE(I2C2)
			&& LL_I2C_IsActiveFlag_MSL(I2C2)
			&& LL_I2C_GetTransferDirection(I2C2)));

	LL_DMA_SetMemoryAddress(DMA1,LL_DMA_CHANNEL_2, (uint32_t)_dataaddr);
	LL_DMA_SetDataLength(DMA1,LL_DMA_CHANNEL_2, _datanum);

	LL_I2C_EnableDMAReq_TX(I2C2);
	LL_DMA_EnableStream(DMA1, LL_DMA_CHANNEL_2);

	//?��?��?��?��?��?��?��牺?��͊�?��?��?��?��?��荞�݂ɂ�?��ׂ�

	while(!LL_DMA_IsActiveFlag_TC2(DMA1));
	// I2C_EVENT_MASTER_BYTE_TRANSMITTED
	while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
			&& LL_I2C_IsActiveFlag_BTF(I2C2)
			&& LL_I2C_IsActiveFlag_TXE(I2C2)
			&& LL_I2C_IsActiveFlag_MSL(I2C2)
			&& LL_I2C_GetTransferDirection(I2C2)));

	LL_I2C_GenerateStopCondition(I2C2);
	LL_I2C_DisableDMAReq_TX(I2C2);
  LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
	LL_DMA_ClearFlag_TC2(DMA1);
*/
}

void I2C_Reads(uint8_t _slaveaddr, uint16_t _index, uint8_t* _dataaddr, uint32_t _datanum){

  LL_I2C_HandleTransfer(I2C2, _slaveaddr, LL_I2C_ADDRSLAVE_7BIT, 2, LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE);

  while(!LL_I2C_IsActiveFlag_TXE(I2C2));
  LL_I2C_TransmitData8(I2C2,(uint8_t)((_index>>8)&0xFF));
  while(!LL_I2C_IsActiveFlag_TXE(I2C2));
  LL_I2C_TransmitData8(I2C2,(uint8_t)(_index&0xFF));
  while(!LL_I2C_IsActiveFlag_TXE(I2C2));
  
  
  LL_I2C_HandleTransfer(I2C2, _slaveaddr, LL_I2C_ADDRSLAVE_7BIT, _datanum, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_RESTART_7BIT_READ);
  
  for(int i=0;i<_datanum;i++){
    while(!LL_I2C_IsActiveFlag_RXNE(I2C2));
		*_dataaddr = LL_I2C_ReceiveData8(I2C2);
    _dataaddr++;
  }

  while(!LL_I2C_IsActiveFlag_STOP(I2C2));

  LL_I2C_ClearFlag_STOP(I2C2);

/*
	// I2C_FLAG_BUSY
	while(LL_I2C_IsActiveFlag_BUSY(I2C2));
    LL_I2C_Enable(I2C2);

	LL_I2C_GenerateStartCondition(I2C2);
	// I2C_EVENT_MASTER_MODE_SELECT
	while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
			&& LL_I2C_IsActiveFlag_SB(I2C2)
			&& LL_I2C_IsActiveFlag_MSL(I2C2)));

	LL_I2C_TransmitData8(I2C2,_slaveaddr);

	// I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED
	while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
			&& LL_I2C_IsActiveFlag_ADDR(I2C2)
			&& LL_I2C_IsActiveFlag_TXE(I2C2)
			&& LL_I2C_IsActiveFlag_MSL(I2C2)
			&& LL_I2C_GetTransferDirection(I2C2)));

	LL_I2C_TransmitData8(I2C2,(uint8_t)((_index>>8)&0xFF));
	// I2C_EVENT_MASTER_BYTE_TRANSMITTED
	while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
			&& LL_I2C_IsActiveFlag_BTF(I2C2)
			&& LL_I2C_IsActiveFlag_TXE(I2C2)
			&& LL_I2C_IsActiveFlag_MSL(I2C2)
			&& LL_I2C_GetTransferDirection(I2C2)));

	LL_I2C_TransmitData8(I2C2,(uint8_t)(_index&0xFF));
	// I2C_EVENT_MASTER_BYTE_TRANSMITTED
	while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
			&& LL_I2C_IsActiveFlag_BTF(I2C2)
			&& LL_I2C_IsActiveFlag_TXE(I2C2)
			&& LL_I2C_IsActiveFlag_MSL(I2C2)
			&& LL_I2C_GetTransferDirection(I2C2)));

	LL_I2C_GenerateStartCondition(I2C2);
	// I2C_EVENT_MASTER_MODE_SELECT
	while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
			&& LL_I2C_IsActiveFlag_SB(I2C2)
			&& LL_I2C_IsActiveFlag_MSL(I2C2)));

	LL_I2C_AcknowledgeNextData(I2C2,LL_I2C_ACK);
	LL_I2C_TransmitData8(I2C2,_slaveaddr+1);
	// I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED
	while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
			&& LL_I2C_IsActiveFlag_ADDR(I2C2)
			&& LL_I2C_IsActiveFlag_MSL(I2C2)));
	int i=0;
	for(i=0;i<_datanum-1;i++){
		LL_I2C_AcknowledgeNextData(I2C2,LL_I2C_ACK);
		while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
				&& LL_I2C_IsActiveFlag_RXNE(I2C2)
				&& LL_I2C_IsActiveFlag_MSL(I2C2)));
		_dataaddr[i] = LL_I2C_ReceiveData8(I2C2);
	}
	LL_I2C_AcknowledgeNextData(I2C2,LL_I2C_NACK);

	LL_I2C_GenerateStopCondition(I2C2);
	while(!(LL_I2C_IsActiveFlag_BUSY(I2C2)
			&& LL_I2C_IsActiveFlag_RXNE(I2C2)
			&& LL_I2C_IsActiveFlag_MSL(I2C2)));
	_dataaddr[i] = LL_I2C_ReceiveData8(I2C2);

	LL_I2C_AcknowledgeNextData(I2C2,LL_I2C_ACK);
  */
}

void VL6180_init(){
  
  LL_I2C_Enable(I2C2);
	LL_DMA_SetPeriphAddress(DMA1,LL_DMA_CHANNEL_2, (uint32_t)(&(I2C2->TXDR)));
  	//LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_13);
    HAL_Delay(100);
    	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);		//VL6180X on
      HAL_Delay(100);
}

void WriteByte_VL6180X(uint16_t _index, uint8_t _d){
	uint8_t _tdata[3] = {};
	_tdata[0] = (uint8_t)(_index >> 8);
	_tdata[1] = (uint8_t)(_index & 0xFF);
	_tdata[2] = _d;

	I2C_DMA_Writes(0x52, _tdata, 3);
}

uint8_t ReadByte_VL6180X(uint16_t _index){
  LL_I2C_Enable(I2C2);
	uint8_t _rdata = 0;
	I2C_Reads(0x52, _index, &_rdata, 1);

	return _rdata;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
