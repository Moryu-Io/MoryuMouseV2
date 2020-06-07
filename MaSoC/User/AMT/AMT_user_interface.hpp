#ifndef AMT_USER_INTERFACE_HPP_
#define AMT_USER_INTERFACE_HPP_


#include "stm32g4xx.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#include "def_const_param.hpp"


namespace AMT{

enum LEDColor{
    RED,
    GREEN,
    BLUE,
    ALL
};

void LED_blink(LEDColor _c, uint16_t _period_ms);
void LED_on(LEDColor _c);
void LED_off(LEDColor _c);

void UI_update();



};


#endif