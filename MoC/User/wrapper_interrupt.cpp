#include "wrapper_interrupt.hpp"
#include "OpenMemoryMap.hpp"
#include "MMT.hpp"
#include "IMU.hpp"
#include "tim_counter.hpp"
#include "Machine.hpp"

void SPI3_RX_DMA_TC(){
    get_ptr_IMU()->rx_dma_TC();
}
void SPI3_TX_DMA_TC(){
    get_ptr_IMU()->tx_dma_TC();
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

void TIM7_ITR(){
    static Machine &MoryuMouse = Machine::getInstance();
    MoryuMouse.control_routine();
}

void TIM17_ITR(){
    T_CNT::tim17_update_event();
}