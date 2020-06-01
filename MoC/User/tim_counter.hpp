#ifndef TIM_COUNTER_HPP_
#define TIM_COUNTER_HPP_

#include "tim.h"


namespace T_CNT{


void tim17_update_event();
void tim17_cnt_enable();
void tim17_cnt_reset();
uint32_t get_nowCount_us();


}


#endif