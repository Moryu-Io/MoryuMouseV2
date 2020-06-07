#ifndef MST_MAIN_HPP_
#define MST_MAIN_HPP_

#include "stm32g4xx.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#include "def_const_param.hpp"


namespace MST{

void MST_init();
void MST_main();


};


#endif