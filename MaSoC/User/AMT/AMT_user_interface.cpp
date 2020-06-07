#include "AMT_user_interface.hpp"
#include "Button.hpp"

namespace AMT{

struct LED_State{
    uint16_t u16_tim_cnt_ms = 0;
    uint16_t u16_tim_period_ms = 0;
    GPIO_TypeDef* GPIOx;
    uint32_t Pinmsk;
};

LED_State led_state[3] = {
    {0,0,GPIOA,LL_GPIO_PIN_12},
    {0,0,GPIOA,LL_GPIO_PIN_10},
    {0,0,GPIOA,LL_GPIO_PIN_11}
};

Button btn(GPIOC, LL_GPIO_PIN_13);

void LED_blink(LEDColor _c, uint16_t _period_ms){
    if(_c == LEDColor::ALL){
        for(int i=0;i<LEDColor::ALL;i++){
            led_state[i].u16_tim_period_ms = _period_ms;
            led_state[i].u16_tim_cnt_ms = 0;
        }
    }else{
        led_state[_c].u16_tim_period_ms = _period_ms;
        led_state[_c].u16_tim_cnt_ms = 0;
    }
}

void LED_on(LEDColor _c){
    if(_c == LEDColor::ALL){
        for(int i=0;i<LEDColor::ALL;i++){
            led_state[i].u16_tim_period_ms = 0xFFFF;
            led_state[i].u16_tim_cnt_ms = 0;
        }
    }else{
        led_state[_c].u16_tim_period_ms = 0xFFFF;
        led_state[_c].u16_tim_cnt_ms = 0;
    }
}

void LED_off(LEDColor _c){
    if(_c == LEDColor::ALL){
        for(int i=0;i<LEDColor::ALL;i++){
            led_state[i].u16_tim_period_ms = 0;
            led_state[i].u16_tim_cnt_ms = 0;
        }
    }else{
        led_state[_c].u16_tim_period_ms = 0;
        led_state[_c].u16_tim_cnt_ms = 0;
    }
}

void UI_update(){
    /* 外部情報の取得（エンコーダ、壁センサ） */


    /* Switchの更新 */
    btn.update(AMTaskPeriod_ms);


    /* LEDの点灯状況の更新 */
    for(int i=0;i<LEDColor::ALL;i++){
        // periodが0xFFFFのときは常に点灯。0のときは常に消灯
        if(led_state[i].u16_tim_period_ms == 0xFFFF) LL_GPIO_SetOutputPin(led_state[i].GPIOx, led_state[i].Pinmsk);
        else if(led_state[i].u16_tim_period_ms == 0) LL_GPIO_ResetOutputPin(led_state[i].GPIOx, led_state[i].Pinmsk);
        else{
            led_state[i].u16_tim_cnt_ms += AMTaskPeriod_ms;
            if((led_state[i].u16_tim_period_ms) <= (led_state[i].u16_tim_cnt_ms)){
                // 周期よりも大きくなったらカウントを0リセットする
                led_state[i].u16_tim_cnt_ms = 0;
                LL_GPIO_ResetOutputPin(led_state[i].GPIOx, led_state[i].Pinmsk);
            }else if((led_state[i].u16_tim_period_ms >> 1) <= (led_state[i].u16_tim_cnt_ms)){
                // 周期の半分より大きくなったらLEDを点灯
                LL_GPIO_SetOutputPin(led_state[i].GPIOx, led_state[i].Pinmsk);
            }else{
                LL_GPIO_ResetOutputPin(led_state[i].GPIOx, led_state[i].Pinmsk);
            }
        }
    }


}



};