/* *************************************************************************
* File Name   : Receiver.h
* Description : Header file for BMS Receiver type selection
* Author      : Harshitha Subramani
* ************************************************************************* */


/* ******************************* Includes ******************************* */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


/* ******************************* Defines ******************************* */



#define CHRGRATE_MIN  -100
#define CHRGRATE_MAX  100
#define TEMP_MIN     -100
#define TEMP_MAX      100
#define SOC_MIN      -100
#define SOC_MAX       100
#define CURRENT_MIN  -100
#define CURRENT_MAX   100

#define SMA_RANGE     5
#define BUFFER_SIZE  1024

#define VALUE_NOTFOUND   65535
#define INVALID_SMARANGE 65534
#define INVALID_VALUE    0

enum BATTERYPARAM {TEMPERATURE,SOC,CURRENT,CHARGERATE, NUMOFPARAM};


struct BatteryParam_s
{
    char ParamName[200];
    float minValue;
    float maxValue;
};

struct BatteryParamOutput_s
{
    float MovingAvg;
    float minRx;
    float maxRx;
};

extern struct BatteryParam_s BatteryParam[NUMOFPARAM];

/* ***************************** Prototypes ***************************** */
float getParam_FromRxBuffer(char *ReadLine, enum BATTERYPARAM batteryParam);
float MinimumOfTwoFloatNumbers(float value1, float value2);
float MaximumOfTwoFloatNumbers(float value1, float value2);
float movingAverageForRangeofValue(float *ptrArrNumbers, float *ptrSum, int param_id, int range, float nextNum);
void RxCalculate_FromBMSParam(void);
