#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
  Failure,
  Success
} OperationMode;

#define Max_ArraySize 1024
#define NumberOfAttributes 2
extern float Temperature[Max_ArraySize];
extern float SoC[Max_ArraySize];
extern int NoOfEntery;
extern float MinimumAttributeValueArray[NumberOfAttributes];
extern float MaximumAttributeValueArray[NumberOfAttributes];


extern OperationMode BMS_ReadfromConsole();
extern void Calculate_TemperatureMinandMaxRange(int NoOfEnteries);
extern void Calculate_SoCMinandMaxRange(int NoOfEnteries);
extern void Calculate_MaxParameterValue(float AttributeValue[Max_ArraySize], int NoOfEnteries, float *MaximumAttributeValue);
extern void Calculate_MinParameterValue(float AttributeValue[Max_ArraySize], int NoOfEnteries, float *MinimumAttributeValue);
extern void Calculate_TemperatureSimpleMovingAverage(int NoOfEnteries);
extern void Calculate_SoCSimpleMovingAverage(int NoOfEnteries);
extern float Calculate_SimpleMovingAverage(float AttributeValue[Max_ArraySize], int NoOfEnteries);
extern OperationMode ReceiveDatafromSender();
