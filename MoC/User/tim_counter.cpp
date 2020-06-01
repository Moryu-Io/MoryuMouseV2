#include "tim_counter.hpp"



uint32_t u32_tim17_cnt_us = 0;

void T_CNT::tim17_cnt_enable(){
    LL_TIM_EnableIT_UPDATE(TIM17);
	LL_TIM_EnableCounter(TIM17);
}
void T_CNT::tim17_cnt_reset(){
    u32_tim17_cnt_us = 0;
}
void T_CNT::tim17_update_event(){
    u32_tim17_cnt_us += TIM17->ARR;
}

uint32_t T_CNT::get_nowCount_us(){
    return u32_tim17_cnt_us + TIM17->CNT;
}