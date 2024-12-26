
#ifndef DHT_H_
#define DHT_H_

#include "global.h"


typedef struct
{
	float Temperature;
	float Humidity;

	int Temp_Int;
	int Temp_Frac;
	int Humid_Int;
	int Humid_Frac;
}DHT_DataTypedef;


//void DHT_GetData (DHT_DataTypedef *DHT_Data);
void DHT_GetData(global_data_t *data);

#endif /* INC_DHT_H_ */
