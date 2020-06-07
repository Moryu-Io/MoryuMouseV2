#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "stm32g4xx.h"
#include "main.h"

namespace AMT{

class Button{
public:
    Button(GPIO_TypeDef* _GPIOx, uint32_t _Pinmsk):
        GPIOx_(_GPIOx), Pinmsk_(_Pinmsk) {};
    
    enum BtnState{
        Pushing,
        LongPushing,
        Release,
        Error
    };

    void update(uint16_t _dcnt_ms){
        if(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13)){
            u16_pushing_cnt_ms_ += _dcnt_ms;
            if(u16_pushing_cnt_ms_ < u16_clickpush_cnt_ms_thre_){
                // 閾値以下の場合は何もしない

            }else if(u16_pushing_cnt_ms_ < u16_longpush_cnt_ms_thre_){
                nowState_ = Pushing;
            }else{
                nowState_ = LongPushing;
            }
        }else{
            // 前回の状態がPushingだった場合、click回数を増やす
            if(nowState_ == Pushing) u32_click_cnt_++;

            nowState_ = Release;
            u16_pushing_cnt_ms_ = 0;
        }
    }

    BtnState get_nowState(){ return nowState_; };
    uint32_t get_click_cnt(){ return u32_click_cnt_; };
    void reset_click_cnt(){u32_click_cnt_ = 0;};

private:
    GPIO_TypeDef* GPIOx_;
    uint32_t Pinmsk_;

    uint16_t u16_longpush_cnt_ms_thre_ = 1500;
    uint16_t u16_clickpush_cnt_ms_thre_ = 50;
    uint16_t u16_pushing_cnt_ms_ = 0;
    uint32_t u32_click_cnt_ = 0;

    BtnState nowState_ = Release;
};


};


#endif