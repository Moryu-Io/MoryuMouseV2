
#include "MMT.hpp"



void MMT_S::set_periph(SPI_TypeDef *_spix, GPIO_TypeDef* _csGPIO, uint32_t _csPinmsk,
					DMA_TypeDef *_dmax, uint32_t _rx_dma_ch, uint32_t _tx_dma_ch){
	SPIx_ = _spix;
	csGPIOx_ = _csGPIO;
	csPinmsk_ = _csPinmsk;
	DMAx_ = _dmax;
	rx_DMA_CH_ = _rx_dma_ch;
	tx_DMA_CH_ = _tx_dma_ch;
	
	ptr_moc_OpenMemory_ = get_ptr_MoC_OpenMemory();
    ptr_masoc_OpenMemory_ = get_ptr_MaSoC_OpenMemory();
}

void MMT_S::init(MMT_Mode _m){
	nowMode_ = _m;
	switch (_m)
	{
	case OpenMemory:
		// MoCの場合、MaSoCのメモリーを受信
		LL_DMA_ConfigAddresses(DMAx_, rx_DMA_CH_,
							   LL_SPI_DMA_GetRegAddr(SPIx_),(uint32_t)(this->ptr_masoc_OpenMemory_->ptr_now_oMem),
							   LL_DMA_GetDataTransferDirection(DMAx_, rx_DMA_CH_));
		LL_DMA_SetDataLength(DMAx_, rx_DMA_CH_, ((this->ptr_masoc_OpenMemory_->memory_byte_size)>>1));

		LL_DMA_ConfigAddresses(DMAx_, tx_DMA_CH_, 
							(uint32_t)(this->ptr_moc_OpenMemory_->ptr_now_oMem),LL_SPI_DMA_GetRegAddr(SPIx_),
							LL_DMA_GetDataTransferDirection(DMAx_, tx_DMA_CH_));
		LL_DMA_SetDataLength(DMAx_, tx_DMA_CH_, (this->ptr_moc_OpenMemory_->memory_byte_size)>>1);
		break;
	case Single:
	default:
		// 受信DMAの設定
		LL_DMA_ConfigAddresses(DMAx_, rx_DMA_CH_,
							   LL_SPI_DMA_GetRegAddr(SPIx_),(uint32_t)&(this->_single_rx_buf[0]),
							   LL_DMA_GetDataTransferDirection(DMAx_, rx_DMA_CH_));
		LL_DMA_SetDataLength(DMAx_, rx_DMA_CH_, 1);	

		// 送信DMAの設定
		LL_DMA_ConfigAddresses(DMAx_, tx_DMA_CH_, 
							(uint32_t)&(this->_single_tx_buf),LL_SPI_DMA_GetRegAddr(SPIx_),
							LL_DMA_GetDataTransferDirection(DMAx_, tx_DMA_CH_));
		LL_DMA_SetDataLength(DMAx_, tx_DMA_CH_, 1);
		break;
	}

	enable_transfer();
}

void MMT_S::enable_transfer(){
	LL_DMA_EnableIT_TC(DMAx_, rx_DMA_CH_);
	LL_DMA_EnableIT_TE(DMAx_, rx_DMA_CH_);
    LL_DMA_EnableIT_TC(DMAx_, tx_DMA_CH_);
	LL_DMA_EnableIT_TE(DMAx_, tx_DMA_CH_);

	LL_SPI_EnableIT_ERR(SPIx_);

	// DMA RX リクエストを有効化
	LL_SPI_EnableDMAReq_RX(SPIx_);

	// DMAを有効化
	LL_DMA_EnableChannel(DMAx_, tx_DMA_CH_);
	LL_DMA_EnableChannel(DMAx_, rx_DMA_CH_);

	// DMA TX リクエストを有効化
	LL_SPI_EnableDMAReq_TX(SPIx_);

	LL_SPI_Enable(SPIx_);
}

void MMT_S::set_single_TXdata(uint8_t _txd){
	_single_tx_buf = _txd;
	// DMA TX リクエストを有効化
	//LL_SPI_EnableDMAReq_TX(SPIx_);
	LL_DMA_EnableChannel(DMAx_, tx_DMA_CH_);
}

void MMT_S::rx_cplt_routine(){
	// Slaveでは必要ない
	// deselect();
	LL_DMA_DisableChannel(DMAx_, tx_DMA_CH_);
	LL_DMA_DisableChannel(DMAx_, rx_DMA_CH_);
	LL_SPI_Disable(SPIx_);
	LL_SPI_DisableDMAReq_RX(SPIx_);
	LL_SPI_DisableDMAReq_TX(SPIx_);
	
	switch(nowMode_){
	case Single:
		if(_single_rx_buf[0] == MMT_MASTER_WHO_AM_I){
			init(OpenMemory);
		}else{
			init(Single);
		}
		break;
	case OpenMemory:
		if((ptr_masoc_OpenMemory_->ptr_now_oMem->header == MMT_MASOC_HEADER) 
			&&(ptr_masoc_OpenMemory_->ptr_now_oMem->footer == MMT_MASOC_FOOTER)){
			// 通信カウントをインクリメント
			(ptr_moc_OpenMemory_->memory0.u32_nowMMT_CNT)++;

			// 二面バッファ切り替え
			if(ptr_masoc_OpenMemory_->ptr_now_oMem == &(ptr_masoc_OpenMemory_->memory0)){
				ptr_masoc_OpenMemory_->set_oMem_to_memory1();
			}else{
				ptr_masoc_OpenMemory_->set_oMem_to_memory0();
			}
			init(OpenMemory);
		}else{
			init(Single);
		}
		break;
	default:
		break;
	}
	is_rx_cplt = true;
}

void MMT_S::tx_cplt_routine(){
	switch(nowMode_){
	case Single:
		// DMA TX リクエストを無効化
		LL_DMA_DisableChannel(DMAx_, tx_DMA_CH_);
		LL_SPI_DisableDMAReq_TX(SPIx_);
		break;
	case OpenMemory:
		// OpenMemory側
		break;
	default:
		break;
	}
}

void MMT_S::error_handler(){
	deselect();
	LL_DMA_DisableChannel(DMAx_, tx_DMA_CH_);
	LL_DMA_DisableChannel(DMAx_, rx_DMA_CH_);
	LL_SPI_Disable(SPIx_);
	
	LL_SPI_DisableDMAReq_RX(SPIx_);
	LL_SPI_DisableDMAReq_TX(SPIx_);

	init(Single);
}

void MMT_S::select(){
	// Slaveでは必要ない
}
void MMT_S::deselect(){
	// Slaveでは必要ない
}