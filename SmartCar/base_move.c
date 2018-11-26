/*
 * base_move.c
 *
 *  Created on: 2018年11月26日
 *      Author: Jack
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void Go_Forward();
void Go_Back();
void Turn_Left();
void Turn_Right();




//左轮PWM设置
Timer_A_PWMConfig pwmConfig_Left_Go  =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_1,
     32000,
     TIMER_A_CAPTURECOMPARE_REGISTER_1,
     TIMER_A_OUTPUTMODE_RESET_SET,
     28800
};
Timer_A_PWMConfig pwmConfig_Left_Back  =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_1,
     32000,
     TIMER_A_CAPTURECOMPARE_REGISTER_3,
     TIMER_A_OUTPUTMODE_RESET_SET,
     28800
};

//右轮PWM设置
Timer_A_PWMConfig pwmConfig_Right_Go  =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_1,
     32000,
     TIMER_A_CAPTURECOMPARE_REGISTER_2,
     TIMER_A_OUTPUTMODE_RESET_SET,
     28800
};
Timer_A_PWMConfig pwmConfig_Right_Back  =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_1,
     32000,
     TIMER_A_CAPTURECOMPARE_REGISTER_4,
     TIMER_A_OUTPUTMODE_RESET_SET,
     28800
};


void Go_Forward()
{
    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN5+GPIO_PIN6+GPIO_PIN7);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN5,
            GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Left_Go);    //更新PWM波形
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Right_Go);
}

void Go_Back()
{
    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN5+GPIO_PIN6+GPIO_PIN7);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN6+GPIO_PIN7,
            GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Left_Back);    //更新PWM波形
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Right_Back);
}

void Turn_Left()  //左转
{
    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN5+GPIO_PIN6+GPIO_PIN7);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5+GPIO_PIN6,
            GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Left_Back);    //更新PWM波形
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Right_Go);
}

void Turn_Right()  //右转
{
    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN5+GPIO_PIN6+GPIO_PIN7);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN7,
            GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Left_Go);  //更新PWM波形
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Right_Back);
}



