#ifndef MCT_MAIN_HPP_
#define MCT_MAIN_HPP_

#include "stm32g4xx.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#include "def_const_param.hpp"
#include "MMT.hpp"


namespace MCT{

void MCT_init();
void MCT_main();


};


#endif