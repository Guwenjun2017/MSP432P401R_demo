/*
 * base_move.c
 *
 *  Created on: 2018��11��26��
 *      Author: Jack
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void Go_Forward();
void Go_Back();
void Turn_Left();
void Turn_Right();




//����PWM����
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

//����PWM����
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
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Left_Go);    //����PWM����
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Right_Go);
}

void Go_Back()
{
    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN5+GPIO_PIN6+GPIO_PIN7);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN6+GPIO_PIN7,
            GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Left_Back);    //����PWM����
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Right_Back);
}

void Turn_Left()  //��ת
{
    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN5+GPIO_PIN6+GPIO_PIN7);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5+GPIO_PIN6,
            GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Left_Back);    //����PWM����
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Right_Go);
}

void Turn_Right()  //��ת
{
    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN5+GPIO_PIN6+GPIO_PIN7);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN7,
            GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Left_Go);  //����PWM����
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Right_Back);
}



