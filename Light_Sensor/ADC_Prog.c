#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Int.h"

u8 Busyflag;

void ADC_Init(ADC_VREF_t vref,ADC_Prescaler_t scaler)
{
	/*clk*/
	
	/*vref*/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS1);
		CLR_BIT(ADMUX,REFS0);
		break;
		case VREF_VCC:
		CLR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
		
	}
	
	/*ADC enable*/
	SET_BIT(ADCSRA,ADEN);
	/*Prescaler*/
	ADCSRA&=0XF8;
	scaler&=0x07;
	ADCSRA|=scaler;
	
	
	
}

u16 ADC_Read(ADC_Channel_t ch)
{
	//u16 adc;
	
	/*select channel*/
	ADMUX&=0XE0; //0B11100000
	ADMUX|=ch;
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait until ADC end conversion*/
	//_delay_ms(1);
	while(GET_BIT(ADCSRA,ADSC));  //busy wait or blocking
	/*read register*/
	//adc=(ADCH<<8)|(ADCL);     //ADLAR=0
	//adc=(ADCL<<2)|(ADCL>>6);  //ADLAR=1
	
	return ADC;
	
}
void ADC_StartConversion(ADC_Channel_t ch)
{
	if (Busyflag==0)
	{
		/*select channel*/
		ADMUX&=0XE0; //0B11100000
		ADMUX|=ch;
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		Busyflag=1;
	}
	
}

u16 ADC_GetRead(void)
{
	while(GET_BIT(ADCSRA,ADSC));  //busy wait or blocking
	 
	return ADC;
} 

u8 ADC_GetReadPeriodic(u16*pdata)  //polling
{
	if(GET_BIT(ADCSRA,ADSC))
	{
		return 0;
	}
	else
	{
		*pdata=ADC;
		Busyflag=0;
		return 1;   
	}  
	
}

u16 ADC_GetReadNoBlock(void)
{
	return ADC;
}

u16 ADC_ReadVolt(ADC_Channel_t ch)
{
	u16 adc=ADC_Read(ch);
	
	u16 volt=((u32)5000*adc)/1024;
	
	
	return volt;
}