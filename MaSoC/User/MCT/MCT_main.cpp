#include "MCT_main.hpp"



void MCT::MCT_init(){
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_14);
    vTaskDelay(500);
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_14);
    vTaskDelay(1000);

    MMT_M &mmt = MMT_M::getInstance();
    mmt.set_periph(SPI1, GPIOA, LL_GPIO_PIN_15,
                   DMA2, LL_DMA_CHANNEL_1, LL_DMA_CHANNEL_2);
    mmt.init(MMT_M::Single);

}

void MCT::MCT_main(){
    MMT_M &mmt = MMT_M::getInstance();
    mmt.enable_transfer();
}
