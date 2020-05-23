#include "wrapper_interrupt.hpp"
#include "OpenMemoryMap.hpp"
#include "MMT.hpp"


void SPI1_RX_DMA_HT(){
    MMT_M &mmt = MMT_M::getInstance();
    mmt.rx_halfcplt_routine();
}
void SPI1_RX_DMA_TC(){
    MMT_M &mmt = MMT_M::getInstance();
    mmt.rx_cplt_routine();
}
void SPI1_TX_DMA_TC(){
    MMT_M &mmt = MMT_M::getInstance();
    mmt.tx_cplt_routine();
}

void SPI1_ERROR_ITR(){
    MMT_M &mmt = MMT_M::getInstance();
    mmt.error_handler();
}