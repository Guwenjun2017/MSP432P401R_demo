/*
 * С���ж�ģ�飺  ʹ����TIMER_A0
 * ���ģ�飺        Ԥ����ʹ��TIMER_A1
 *
 *
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include<stdint.h>
#include<stdbool.h>
#include"base_move.h"

/**
 * main.c
 */
void main(void)
{
    MAP_WDT_A_holdTimer();   //�ع�

    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    MAP_CS_initClockSignal(CS_MCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_2);
    MAP_PCM_setPowerState(PCM_AM_LF_VCORE0);

    //PWM����˿�����P2.4 P2.5
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4+GPIO_PIN5,
            GPIO_PRIMARY_MODULE_FUNCTION);

    //���ж�����P1.0   Button S1,-->��������-->����жϱ�־-->ʹ���ж�
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    //���ж�����P1.4   Button S2,-->��������-->����жϱ�־-->ʹ���ж�
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

    //����PWM��
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Left_Go);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_Right_Go);

    //���ж�ʹ��
    MAP_Interrupt_enableInterrupt(INT_PORT1);
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    while(1)
    {
        //MAP_PCM_gotoLPM0();   //����
    }

    //return;
}

/*****���ж�P1�ڴ�����*****/
void PORT1_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);

    if(status & GPIO_PIN1)       //���P1.0(S1)���£�����10%��ռ�ձ�
    {
        Turn_Left();
    }

    if(status & GPIO_PIN4)
    {
        Turn_Right();
    }

    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);
}
