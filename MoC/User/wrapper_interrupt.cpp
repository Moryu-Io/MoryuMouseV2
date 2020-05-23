#include "wrapper_interrupt.hpp"
#include "OpenMemoryMap.hpp"
#include "MMT.hpp"

uint8_t SPI3_DMA_CPLT_FLAG = 0;
#define SPI3_RX_DMA_CPLT_MSK (0b00000001)
#define SPI3_TX_DMA_CPLT_MSK (0b00000010)

void set_SPI3_RX_DMA_TC(){
    SPI3_DMA_CPLT_FLAG |= SPI3_RX_DMA_CPLT_MSK;
}
void set_SPI3_TX_DMA_TC(){
    SPI3_DMA_CPLT_FLAG |= SPI3_TX_DMA_CPLT_MSK;
}
void clear_SPI3_TX_DMA_TC(){
    CLEAR_BIT(SPI3_DMA_CPLT_FLAG, SPI3_TX_DMA_CPLT_MSK);
}
void clear_SPI3_RX_DMA_TC(){
    CLEAR_BIT(SPI3_DMA_CPLT_FLAG, SPI3_RX_DMA_CPLT_MSK);
}
uint8_t is_SPI3_RX_DMA_TC(){
    return ((SPI3_DMA_CPLT_FLAG & SPI3_RX_DMA_CPLT_MSK)==SPI3_RX_DMA_CPLT_MSK);
}
uint8_t is_SPI3_TX_DMA_TC(){
    return ((SPI3_DMA_CPLT_FLAG & SPI3_TX_DMA_CPLT_MSK)==SPI3_TX_DMA_CPLT_MSK);
}


void SPI1_RX_DMA_HT(){
    MMT_S &mmt = MMT_S::getInstance();
    mmt.rx_halfcplt_routine();
}
void SPI1_RX_DMA_TC(){
    MMT_S &mmt = MMT_S::getInstance();
    mmt.rx_cplt_routine();
}
void SPI1_TX_DMA_TC(){
    MMT_S &mmt = MMT_S::getInstance();
    mmt.tx_cplt_routine();
}
void SPI1_ERROR_ITR(){
    MMT_S &mmt = MMT_S::getInstance();
    mmt.error_handler();
}