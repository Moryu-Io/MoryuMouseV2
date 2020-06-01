#include "wrapper_main.hpp"
#include "wrapper_interrupt.hpp"
#include "IMU.hpp"
#include "MMT.hpp"
#include "Encoder.hpp"
#include "Motor.hpp"
#include "Controller.hpp"
#include "Machine.hpp"
#include "ADCC.hpp"
#include "tim_counter.hpp"
#define ARM_MATH_CM4
#include "arm_math.h"

static Motor RightMotor((uint32_t*)(&(TIM1->ARR)), (uint32_t*)(&(TIM1->CCER)),
						LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH2,
						(uint32_t*)(&(TIM1->CCR2)), (uint32_t*)(&(TIM1->CCR1)));

static Motor LeftMotor((uint32_t*)(&(TIM1->ARR)), (uint32_t*)(&(TIM1->CCER)),
					   LL_TIM_CHANNEL_CH3 | LL_TIM_CHANNEL_CH4,
					   (uint32_t*)(&(TIM1->CCR4)), (uint32_t*)(&(TIM1->CCR3)));

static Encoder RightEncoder(TIM8, 2.0f*PI*MOTOR_REDUCTION_RATIO*RIGHT_WHEEL_DIAMETER_mm);
static Encoder LeftEncoder(TIM2, 2.0f*PI*MOTOR_REDUCTION_RATIO*LEFT_WHEEL_DIAMETER_mm);

static PID RotationController(CONTROLL_FREQ, 0.2f, 0.3f, 0.0f, 0.3f);
uint16_t adc1_data = 0;
uint16_t adc2_data = 0;

void cpp_wrapper_main_setup(void){
    static Machine &MoryuMouse = Machine::getInstance();

    LL_mDelay(100);
    LL_GPIO_ResetOutputPin(GPIOF, LL_GPIO_PIN_1);
    LL_GPIO_SetOutputPin(GPIOF, LL_GPIO_PIN_1);
    LL_mDelay(100);

    static MMT_S &mmt = MMT_S::getInstance();
    mmt.set_periph(SPI1, GPIOA, LL_GPIO_PIN_4,
                   DMA2, LL_DMA_CHANNEL_1, LL_DMA_CHANNEL_2);
    mmt.init(MMT_S::Single);
 
    MoryuMouse.init(TIM7, &RightMotor, &LeftMotor, &RightEncoder, &LeftEncoder, &RotationController, get_ptr_IMU());

    LL_mDelay(100);
    MoryuMouse.enable();

    //T_CNT::tim17_cnt_enable();
}

void cpp_wrapper_main_loop(void){
    static uint8_t counter = 0;
    static uint32_t l_enc = 0;
    static uint32_t r_enc = 0;
    
    counter++;
    static MMT_S &mmt = MMT_S::getInstance();
    LL_mDelay(10);
    r_enc = RightEncoder.get_nowCNT();
    l_enc = LeftEncoder.get_nowCNT();


    get_ptr_MoC_OpenMemory()->ptr_now_oMem->u16_rEncCNT = r_enc;
    get_ptr_MoC_OpenMemory()->ptr_now_oMem->u16_lEncCNT = l_enc;
    
    //mmt.set_single_TXdata(counter);
}

