#include "WST_main.hpp"
#include "WallSensor_PD.hpp"
#include <stdio.h>
#include "WST_open_info.hpp"

namespace WST{

WallSensorPD wspd;
WST_OpenInfo* oInfo;

void WST_init(){
    wspd.init();
    wspd.enable();
    oInfo = WST::get_ptr_oInfo();
}

void WST_main(){
    uint16_t _u16_ws_raw[4] = {};

    wspd.get_raw_adc(_u16_ws_raw);


    oInfo->u16_raw_WSPD_RightFront = _u16_ws_raw[WallSensorPD::R_Front];
    oInfo->u16_raw_WSPD_RightSide  = _u16_ws_raw[WallSensorPD::R_Side];
    oInfo->u16_raw_WSPD_LeftFront  = _u16_ws_raw[WallSensorPD::L_Front];
    oInfo->u16_raw_WSPD_LeftSide   = _u16_ws_raw[WallSensorPD::R_Side];
    

    printf("%d,%d,%d,%d\r\n", _u16_ws_raw[WallSensorPD::L_Front]
                            , _u16_ws_raw[WallSensorPD::L_Side]
                            , _u16_ws_raw[WallSensorPD::R_Side]
                            , _u16_ws_raw[WallSensorPD::R_Front]);
}

};


