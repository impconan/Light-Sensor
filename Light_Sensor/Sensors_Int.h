

#ifndef SENSORS_INT_H_
#define SENSORS_INT_H_



void SENSORS_Init(void);


/*Function return C*10 */
u16 SENSORS_ReadTemp(void);
u16 SENSORS_ReadSmoke(void);

u16 SENSORS_ReadPressure(void);

u16 POT_Read(void);










#endif /* SENSORS_INT_H_ */