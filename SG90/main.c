#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include<stdint.h>
#include<stdbool.h>
#include"SG90.h"


/**
 * main.c    调试舵机SG90
 */
void main(void)
{
    MAP_WDT_A_holdTimer();   //关狗

    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    MAP_CS_initClockSignal(CS_MCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_2);
    MAP_PCM_setPowerState(PCM_AM_LF_VCORE0);

    //PWM输出端口配置P6.6
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN6,
            GPIO_PRIMARY_MODULE_FUNCTION);

    //产生PWM波
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig_SG90);

    //外中断配置P1.0   Button S1,-->设置输入-->清除中断标志-->使能中断
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    //外中断配置P1.4   Button S2,-->设置输入-->清除中断标志-->使能中断
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

    //总中断使能
    MAP_Interrupt_enableInterrupt(INT_PORT1);
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    while(1)
    {
        //MAP_PCM_gotoLPM0();   //节能
    }
}

/*****外中断P1口处理函数*****/
void PORT1_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);

    if(status & GPIO_PIN1)       //如果P1.0(S1)按下，增加10%的占空比
    {
        Servo_TurnLeft_90();
    }

    if(status & GPIO_PIN4)
    {
        Servo_TurnRight_90();````````````````````````````````````````````
    }

    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);
}
