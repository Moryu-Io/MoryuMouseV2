#include "wrapper_main.hpp"
#include "wrapper_interrupt.hpp"
#include "MMT.hpp"


void cpp_wrapper_main_setup(void){
    LL_mDelay(2000);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH4);
    LL_TIM_EnableCounter(TIM1);
    LL_TIM_EnableAllOutputs(TIM1);
  

    MMT_M &mmt = MMT_M::getInstance();
    mmt.set_periph(SPI1, GPIOA, LL_GPIO_PIN_15,
                   DMA2, LL_DMA_CHANNEL_1, LL_DMA_CHANNEL_2);
    mmt.init(MMT_M::Single);
    

}

void cpp_wrapper_main_loop(void){
    static uint8_t counter = 0;
    TIM1->CCR3 = 5000;
    LL_mDelay(1);
    MMT_M &mmt = MMT_M::getInstance();
    mmt.enable_transfer();
    if(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13) == 1){
        TIM1->CCR4 = 5000;
        counter++;
        get_ptr_MaSoC_OpenMemory()->ptr_now_oMem->isThisMemoryLocked = counter;

        LL_mDelay(1000);
        TIM1->CCR4 = 0;
    }
}

