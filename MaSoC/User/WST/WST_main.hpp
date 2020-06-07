#ifndef WST_MAIN_HPP_
#define WST_MAIN_HPP_

#include "stm32g4xx.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#include "def_const_param.hpp"

namespace WST{

void WST_init();
void WST_main();


};


#endif