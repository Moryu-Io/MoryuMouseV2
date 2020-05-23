#include "wrapper_main.hpp"
#include "wrapper_interrupt.hpp"
#include "IMU.hpp"
#include "MMT.hpp"
#include "Encoder.hpp"
#include "Motor.hpp"
#include "ADCC.hpp"

static Motor RightMotor((uint32_t*)(&(TIM1->ARR)), (uint32_t*)(&(TIM1->CCER)),
						LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH2,
						(uint32_t*)(&(TIM1->CCR1)), (uint32_t*)(&(TIM1->CCR2)));

static Motor LeftMotor((uint32_t*)(&(TIM1->ARR)), (uint32_t*)(&(TIM1->CCER)),
					   LL_TIM_CHANNEL_CH3 | LL_TIM_CHANNEL_CH4,
					   (uint32_t*)(&(TIM1->CCR3)), (uint32_t*)(&(TIM1->CCR4)));

static Encoder RightEncoder((uint32_t*)(&(TIM8->ARR)), (uint32_t*)(&(TIM8->CNT)), 1.0f);
static Encoder LeftEncoder((uint32_t*)(&(TIM2->ARR)), (uint32_t*)(&(TIM2->CNT)), 1.0f);

uint16_t adc1_data = 0;
uint16_t adc2_data = 0;

void cpp_wrapper_main_setup(void){
    LL_mDelay(100);
    LL_GPIO_ResetOutputPin(GPIOG, LL_GPIO_PIN_10);
    LL_GPIO_SetOutputPin(GPIOG, LL_GPIO_PIN_10);
    LL_mDelay(100);

    IMU imu(SPI3, GPIOG, LL_GPIO_PIN_10, DMA1, LL_DMA_CHANNEL_1, LL_DMA_CHANNEL_2);
    imu.init_config();
    LL_mDelay(100);
    //imu.getwhoamI();

    MMT_S &mmt = MMT_S::getInstance();
    mmt.set_periph(SPI1, GPIOA, LL_GPIO_PIN_4,
                   DMA2, LL_DMA_CHANNEL_1, LL_DMA_CHANNEL_2);
    mmt.init(MMT_S::Single);
    
	LL_TIM_EnableCounter(TIM2);
	LL_TIM_EnableCounter(TIM8);
        
    LL_TIM_EnableUpdateEvent(TIM1);
	LL_TIM_EnableCounter(TIM1);
    TIM1->BDTR |= TIM_BDTR_MOE;	
    RightMotor.enable_Motor();
    LeftMotor.enable_Motor();
    //RightMotor.set_duty(-0.1f);
    //LeftMotor.set_duty(0.1f);
    LL_mDelay(1000);

}

void cpp_wrapper_main_loop(void){
    static uint8_t counter = 0;
    static uint32_t l_enc = 0;
    static uint32_t r_enc = 0;
    
    counter++;
    MMT_S &mmt = MMT_S::getInstance();
    LL_mDelay(1000);
    r_enc = RightEncoder.get_nowCNT();
    l_enc = LeftEncoder.get_nowCNT();
    ADC_TypeDef* _adc = ADC1;
    
    get_ptr_MoC_OpenMemory()->ptr_now_oMem->isThisMemoryLocked = counter;
    //mmt.set_single_TXdata(counter);
    
}

