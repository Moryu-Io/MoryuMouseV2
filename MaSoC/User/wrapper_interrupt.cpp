#include "wrapper_interrupt.hpp"
#include "OpenMemoryMap.hpp"

#include "main.h"
#include "def_const_param.hpp"
#include "AMT_main.hpp"
#include "MCT_main.hpp"
#include "MST_main.hpp"
#include "WST_main.hpp"


void SPI1_RX_DMA_TC(){
    MCT::MMT_M &mmt = MCT::MMT_M::getInstance();
    mmt.rx_cplt_routine();
}
void SPI1_TX_DMA_TC(){
    MCT::MMT_M &mmt = MCT::MMT_M::getInstance();
    mmt.tx_cplt_routine();
}

void SPI1_ERROR_ITR(){
    MCT::MMT_M &mmt = MCT::MMT_M::getInstance();
    mmt.error_handler();
}