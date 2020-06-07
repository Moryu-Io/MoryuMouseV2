#ifndef WST_OPEN_INFO_HPP_
#define WST_OPEN_INFO_HPP_

#include "stm32g4xx.h"
#include "main.h"


namespace WST{

struct WST_OpenInfo
{
    uint16_t u16_raw_WSPD_RightFront;
    uint16_t u16_raw_WSPD_RightSide;
    uint16_t u16_raw_WSPD_LeftFront;
    uint16_t u16_raw_WSPD_LeftSide;
};


WST_OpenInfo* get_ptr_oInfo();



};


#endif