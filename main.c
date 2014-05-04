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


#include <stm32f4xx.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stdio.h>
#include <stm32f4xx_conf.h>
#include <stm32f4xx_dma.h>
#include "string.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
//==Definitions==
#include <stdlib.h>


#include "stm32f4xx_adc.h"

#include "stm32f4xx_gpio.h"

#include "stm32f4xx_rcc.h"








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




// This method for usart including convert string printout method (PA2 & PA3)

void init_usart(void){

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* enable peripheral clock for USART2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);


	/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* GPIOA Configuration:  USART2 TX on PA2 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect USART2 pins to AF2 */
	// TX = PA2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	USART_Cmd(USART2, ENABLE); // enable USART2

}

void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

void USART_puts (USART_TypeDef* USARTx, volatile char *s) {
	while( *s) {
		while (!(USARTx ->SR & 0x00000040));
			USART_SendData(USARTx, *s);
		*s++;
	}
}


/****************************************************************************************************/

// This is ADC part which use to convert PC0 sensor
int ConvertedValue = 0; //Converted value readed from ADC


unsigned char *buffer[4];
unsigned int val = 1023;

void adc_configure(){

 ADC_InitTypeDef ADC_init_structure; //Structure for adc confguration

 GPIO_InitTypeDef GPIO_initStructre; //Structure for analog input pin

 //Clock configuration

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//The ADC1 is connected the APB2 peripheral bus thus we will use its clock source

 RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN,ENABLE);//Clock for the ADC port!! Do not forget about this one ;)

 //Analog pin configuration

 GPIO_initStructre.GPIO_Pin = GPIO_Pin_0;//The channel 10 is connected to PC0

 GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN; //The PC0 pin is configured in analog mode

 GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL; //We don't need any pull up or pull down

 GPIO_Init(GPIOC,&GPIO_initStructre);//Affecting the port with the initialization structure configuration

 //ADC structure configuration

 ADC_DeInit();

 ADC_init_structure.ADC_DataAlign = ADC_DataAlign_Right;//data converted will be shifted to right

 ADC_init_structure.ADC_Resolution = ADC_Resolution_12b;//Input voltage is converted into a 12bit number giving a maximum value of 4096

 ADC_init_structure.ADC_ContinuousConvMode = ENABLE; //the conversion is continuous, the input data is converted more than once

 ADC_init_structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;// conversion is synchronous with TIM1 and CC1 (actually I'm not sure about this one :/)

 ADC_init_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//no trigger for conversion

 ADC_init_structure.ADC_NbrOfConversion = 1;//I think this one is clear :p

 ADC_init_structure.ADC_ScanConvMode = DISABLE;//The scan is configured in one channel

 ADC_Init(ADC1,&ADC_init_structure);//Initialize ADC with the previous configuration

 //Enable ADC conversion

 ADC_Cmd(ADC1,ENABLE);

 //Select the channel to be read from

 ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_144Cycles);

}

int adc_convert(){

 ADC_SoftwareStartConv(ADC1);//Start the conversion

 while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//Processing the conversion

 return ADC_GetConversionValue(ADC1); //Return the converted data

}



/****************************************************************************************************/
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



	adc_configure();//Start configuration the adc


	init_usart(); // starr configuration of the usart
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
		 
		// return the adc reading value 
		ConvertedValue = adc_convert();
		int a = 1;
		char buf[80];
		//char *something = itoa (ConvertedValue, buffer, 10);
		snprintf(buf, "%d", a);
		
		USART_puts(USART2, (uint8_t)a);
		USART_SendData(USART2, buf);

		Delay(0x3FFFFF); 
	}
}
