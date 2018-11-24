#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include<stdint.h>
#include<stdbool.h>


//Timer_A_PWMConfig�ṹ������
Timer_A_PWMConfig pwmConfig  =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_1,
     32000,
     TIMER_A_CAPTURECOMPARE_REGISTER_1,
     TIMER_A_OUTPUTMODE_RESET_SET,
     3200
};

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

    //PWM����˿�����P2.4
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4,
            GPIO_PRIMARY_MODULE_FUNCTION);
    //���ж�����P1.0   Button S1,-->��������-->����жϱ�־-->ʹ���ж�
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    //���ж�����P1.4   Button S2,-->��������-->����жϱ�־-->ʹ���ж�
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

    //����PWN��
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

    //���ж�ʹ��
    MAP_Interrupt_enableInterrupt(INT_PORT1);
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    while(1)
    {
        MAP_PCM_gotoLPM0();   //����
    }

    return;
}

/*****���ж�P1�ڴ�����*****/
void PORT1_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if(status & GPIO_PIN1)       //���P1.0(S1)���£�����10%��ռ�ձ�
    {
        if(pwmConfig.dutyCycle == 28000)
            pwmConfig.dutyCycle = 28000;
        else
            pwmConfig.dutyCycle += 3200;

        MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig); //����PWM����
    }

    if(status & GPIO_PIN4)       //���P1.4(S2)���£�����10%��ռ�ձ�
    {
        if(pwmConfig.dutyCycle == 3200)
            pwmConfig.dutyCycle = 3200;
        else
            pwmConfig.dutyCycle -= 3200;

        MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig); //����PWM����
    }
}
