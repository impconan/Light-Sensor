#include "StdTypes.h"
#include "Sensors_Int.h"
#include "ADC_Int.h"
#include "Sensors_Cfg.h"



u16 SENSORS_ReadTemp(void)
{
	u16 adc=ADC_Read(POT_Temp_CH);
	
	u16 temp=(adc*(u32)100)/1024;
	
	return temp;
	
	
}
u16 SENSORS_ReadSmoke(void)
{
	u16 adc=ADC_Read(POT_Smoke_CH);
	
	u16 smoke=(adc*(u32)100)/1024;
	
	return smoke;
	
	
}

u16 SENSORS_ReadPressure(void)
{
	u16 adc=ADC_Read(MPX4115_CH);
	
	//u16 press=(((u32)1000*adc/1024)+182);
	u16 press=(adc-40)+150;
	
	return press;
	
	
}

u16 SENSORS_NTCRead(void)
{
	u16 volt=ADC_ReadVolt(LM35_CH);
	
	u16 temp=volt;
	
	return temp;
}


















