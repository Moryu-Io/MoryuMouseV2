#ifndef AMT_MAIN_HPP_
#define AMT_MAIN_HPP_

#include "stm32g4xx.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#include "def_const_param.hpp"

namespace AMT{

void AMT_init();
void AMT_main();


};


#endif