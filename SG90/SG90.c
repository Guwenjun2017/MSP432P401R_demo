/*
 * SG90.c
 *
 *  Created on: 2018��11��26��
 *      Author: Jack
 */

#ifndef SG90_C_
#define SG90_C_
#include<ti/devices/msp432p4xx/driverlib/driverlib.h>

void Servo_TurnLeft_90();
void Servo_TurnRight_90();

Timer_A_PWMConfig pwmConfig_SG90 =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_1,
     1280,                 //32000��Ӧ500ms,��ô20ms��1280
     TIMER_A_CAPTURECOMPARE_REGISTER_3,
     TIMER_A_OUTPUTMODE_RESET_SET,
     96                    //1ms��64��1.5ms��96
};


void Servo_TurnLeft_90()
{
    pwmConfig_SG90.dutyCycle = 160;
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig_SG90);
}

void Servo_TurnRight_90()
{
    pwmConfig_SG90.dutyCycle = 36;       //��ԭ��ӦΪ32������ʵ���������Ϊ36
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig_SG90);
}


#endif /* SG90_C_ */
