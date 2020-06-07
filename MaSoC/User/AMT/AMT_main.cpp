#include "AMT_main.hpp"
#include "MCT_main.hpp"
#include "AMT_user_interface.hpp"

void AMT::AMT_init(){
    //LED_blink(RED, 1000);
}

void AMT::AMT_main(){
    if(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13) == 1){
        MCT::MMT_M &mmt = MCT::MMT_M::getInstance();
    }
    UI_update();
}
