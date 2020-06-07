#ifndef WALLSENSOR_PD_HPP_
#define WALLSENSOR_PD_HPP_

#include "stm32g4xx.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#include "def_const_param.hpp"

namespace WST{

class WallSensorPD{
public:
    WallSensorPD(){};
    
    enum WS_Dire{
        R_Front,
        R_Side,
        L_Front,
        L_Side
    };

    void init();

    void update();

    void enable();
    void disable();

    void change_ampgain(WS_Dire _dir, uint32_t _g);
    
    void get_raw_adc(uint16_t* _d);

private:
    uint16_t u16_adc1_buf[2] = {};
    uint16_t u16_adc2_buf[2] = {};



};




};


#endif