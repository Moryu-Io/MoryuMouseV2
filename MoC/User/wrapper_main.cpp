#include "wrapper_main.hpp"
#include "wrapper_interrupt.hpp"
#include "IMU.hpp"

void cpp_wrapper_main_setup(void){
    HAL_Delay(1000);
    LL_GPIO_ResetOutputPin(GPIOG, GPIO_PIN_10);
    LL_GPIO_SetOutputPin(GPIOG, GPIO_PIN_10);
    HAL_Delay(100);

    IMU imu(SPI3, GPIOG, GPIO_PIN_10, DMA1, LL_DMA_CHANNEL_1, LL_DMA_CHANNEL_2);
    imu.init_config();
    HAL_Delay(100);
    imu.getwhoamI();
    HAL_Delay(100);
    IMUdata _imudata={};
    imu.getIMUdata(&_imudata);


    int ax = (int)(_imudata.accel_x);
    int ay = (int)(_imudata.accel_y);
    int gz = (int)(_imudata.gyro_z);
        HAL_Delay(100);
}

void cpp_wrapper_main_loop(void){

}

