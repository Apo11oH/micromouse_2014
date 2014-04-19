#include <stm32f4xx.h>
#include <stdio.h>

#define TIM2_CLKFREQ 10000UL

GPIO_InitTypeDef  GPIO_InitStruct;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
NVIC_InitTypeDef NVIC_InitStructure;

void initPins()
{
	initLED();
	initMotors();
	initPWM();
	/*
	initSensors();
	initINTR();
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

void initMotors()
{
	/**
	 * PB13	(AIN1) and PB14 (BIN1) should be set high
	 * PB12 (AIN2) and PB15 (BIN2) should be set low
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
	/*
	// Enable GPIO pins for Low
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	*/
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
	uint16_t pulse_width = 0;

	initPins();

	GPIOB->BSRRL = 0x6000; //0110 0000 0000 0000
	GPIOB->BSRRH = 0x9000; //1001 0000 0000 0000
	pwm_config(100);

	pwm_set_power(1,50);
	pwm_set_power(2,50);

    while(1)
    {
    	/*
    	pwm_set_power(1,pulse_width++);
    	pwm_set_power(2,pulse_width++);
        if (pulse_width > 800)
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