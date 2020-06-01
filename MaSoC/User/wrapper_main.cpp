#include "wrapper_main.hpp"
#include "wrapper_interrupt.hpp"
#include "MMT.hpp"

#include "FreeRTOS.h"
#include "task.h"


// RTOS Task一覧
static void MachineControlTask(void *pvParameters);
static void WallSensingTask(void *pvParameters);
static void MazeSolverTask(void *pvParameters);
static void UIControlTask(void *pvParameters);

void cpp_wrapper_rtos_initialize(void){
    // RTOSタスク設定
    xTaskCreate(MachineControlTask, "MCTask", MCTaskStackSize, NULL, MCTaskPriority, NULL);
    xTaskCreate(WallSensingTask, "WSTask", WSTaskStackSize, NULL, WSTaskPriority, NULL);
    xTaskCreate(MazeSolverTask, "MSTask", MSTaskStackSize, NULL, MSTaskPriority, NULL);
    xTaskCreate(UIControlTask, "UICTask", UICTaskStackSize, NULL, UICTaskPriority, NULL);

    vTaskStartScheduler();
}


static void MachineControlTask(void *pvParameters){
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_14);
    vTaskDelay(500);
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_14);
    vTaskDelay(1000);
    MMT_M &mmt = MMT_M::getInstance();
    mmt.set_periph(SPI1, GPIOA, LL_GPIO_PIN_15,
                   DMA2, LL_DMA_CHANNEL_1, LL_DMA_CHANNEL_2);
    mmt.init(MMT_M::Single);

    while(1){
        mmt.enable_transfer();
        vTaskDelay(10);
    }
}


static void WallSensingTask(void *pvParameters){

    while(1){
        vTaskDelay(10);
    }
}


static void MazeSolverTask(void *pvParameters){

    while(1){
        vTaskDelay(10);
    }
}


static void UIControlTask(void *pvParameters){
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH4);
    LL_TIM_EnableCounter(TIM1);
    LL_TIM_EnableAllOutputs(TIM1);

    while(1){
        if(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13) == 1){
            MMT_M &mmt = MMT_M::getInstance();
            vTaskDelay(10);
        }
        LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_12);
        vTaskDelay(100);
        LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_12);
        vTaskDelay(100);
    }
}