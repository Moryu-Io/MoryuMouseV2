#include "wrapper_main.hpp"
#include "wrapper_interrupt.hpp"

#include "FreeRTOS.h"
#include "task.h"

#include "main.h"
#include "def_const_param.hpp"
#include "AMT_main.hpp"
#include "MCT_main.hpp"
#include "MST_main.hpp"
#include "WST_main.hpp"

#include <stdio.h>

// RTOS Task一覧
static void MachineControlTask(void *pvParameters);
static void WallSensingTask(void *pvParameters);
static void MazeSolverTask(void *pvParameters);
static void ActionManagerTask(void *pvParameters);

void cpp_wrapper_rtos_initialize(void){
    setbuf(stdout, NULL);

    // RTOSタスク設定
    xTaskCreate(MachineControlTask, "MCTask", MCTaskStackSize, NULL, MCTaskPriority, NULL);
    xTaskCreate(WallSensingTask, "WSTask", WSTaskStackSize, NULL, WSTaskPriority, NULL);
    xTaskCreate(MazeSolverTask, "MSTask", MSTaskStackSize, NULL, MSTaskPriority, NULL);
    xTaskCreate(ActionManagerTask, "AMTask", AMTaskStackSize, NULL, AMTaskPriority, NULL);

    vTaskStartScheduler();
}


static void MachineControlTask(void *pvParameters){
    portTickType _xLastWakeTime;
    const portTickType _xFreq = MCTaskPeriod_ms;

    MCT::MCT_init();

    _xLastWakeTime = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&_xLastWakeTime, _xFreq);
        MCT::MCT_main();
    }
}


static void WallSensingTask(void *pvParameters){
    portTickType _xLastWakeTime;
    const portTickType _xFreq = WSTaskPeriod_ms;

    WST::WST_init();

    _xLastWakeTime = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&_xLastWakeTime, _xFreq);
        WST::WST_main();
    }
}


static void MazeSolverTask(void *pvParameters){
    portTickType _xLastWakeTime;
    const portTickType _xFreq = MSTaskPeriod_ms;

    MST::MST_init();

    _xLastWakeTime = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&_xLastWakeTime, _xFreq);
        MST::MST_main();
    }
}


static void ActionManagerTask(void *pvParameters){
    portTickType _xLastWakeTime;
    const portTickType _xFreq = AMTaskPeriod_ms;

    AMT::AMT_init();

    _xLastWakeTime = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&_xLastWakeTime, _xFreq);
        AMT::AMT_main();
    }
}