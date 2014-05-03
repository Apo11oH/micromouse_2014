#include <stm32f4xx.h>
#include <stdio.h>
#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "i2c_stuff.h"

#define TIM2_CLKFREQ 20000000UL

GPIO_InitTypeDef  GPIO_InitStruct;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
ADC_InitTypeDef ADC_InitStructure;
ADC_CommonInitTypeDef ADC_CommonInitStruct;
I2C_InitTypeDef I2C_InitStructure;

void initAll()
{
	initLED();
	initMotorPins();
	initPWM();
	//initI2C();
	//initSensorPins();
	//initSensors();
	/*
	initIntr();
	initXBee();
	initCompass();
	 */
}

void initLED()
{
	// Enable peripheral clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	// Enable specific GPIO pins
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void initMotorPins()
{
	/**
	 * PB13	(AIN1) and PB15 (BIN1) should be set high
	 * PB12 (AIN2) and PB14 (BIN2) should be set low
	 */
	// Enable peripheral clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	// Enable GPIO pins for High
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void initPWM()
{
	// Enable TIM3 clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// Enable GPIOA clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// Configure TIM3 CH1 (PA6) and TIM3 CH2 (PA7)
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Connect TIM3 pins to AF2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
}

void initSensorPins()
{
	// Enable TIM3 clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	// Enable GPIOA & GPIOC clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);
	// Enable Receiver
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	// Enable Emitter
}

void pwm_config(int period){
	uint16_t prescaler_value = 0;
	// Compute prescaler value
	prescaler_value = (uint16_t)(SystemCoreClock/TIM2_CLKFREQ) - 1;

	// Setup time base structure
	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler_value;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	// Setup PWM output chanell
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	// Enable TIM3 counter
	TIM_Cmd(TIM3, ENABLE);
}

void pwm_set_power(uint16_t ch, uint16_t dutycycle){
	switch(ch){
	case 1: TIM3->CCR1 = dutycycle; break;
	case 2: TIM3->CCR2 = dutycycle; break;
	default: break;
	}
}


int main(void)
{
	int count = 0xFFFFFFFFFFFF;
	uint16_t pulse_width = 20;

	initAll();

	GPIOB->BSRRL = 0xAC18; //1010 1100 0001 1000
	GPIOB->BSRRH = 0x5000; //0101 0000 0000 0000
	while(count-- > 0)
	{
	}
	pwm_config(100);

	pwm_set_power(1,15);
	pwm_set_power(2,15);
	GPIOB->BSRRH = 0x5C18; //0101 0000 0000 0000

	while(1)
	{
		//pwm_set_power(1,pulse_width++);
		//pwm_set_power(2,pulse_width++);

		/*
        if (pulse_width > 50)
        {
        	GPIO_ToggleBits(GPIOB, GPIO_Pin_3);
        	GPIO_ToggleBits(GPIOB, GPIO_Pin_4);
        	GPIO_ToggleBits(GPIOB, GPIO_Pin_10);
        	GPIO_ToggleBits(GPIOB, GPIO_Pin_11);
			pulse_width = 0;
        }
		 */
	}
}
