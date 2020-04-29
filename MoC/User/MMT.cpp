
#include "MMT.hpp"


void MMT::init(){
    if(LL_SPI_GetMode(SPIx_) == LL_SPI_MODE_SLAVE) isSlaveMode = true;

}