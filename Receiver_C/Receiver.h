
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//#ifdef _WIN32
//#include <Windows.h>
//#else
//#include <unistd.h>
//#endif



#define SOC_MIN      0.0
#define SOC_MAX      20.0
#define CHRGRATE_MIN 0.0
#define CHRGRATE_MAX 50.0
#define TEMP_MIN     20.0
#define TEMP_MAX     80.0
#define CURRENT_MIN  20.0
#define CURRENT_MAX  80.0

#define SMA_RANGE 5
#define MAXLENGTH_INPUTSTRING 1024

#define VALUE_NOTFOUND 65532
#define ERROR_VALUE_FROM_RX 65535
//define INVALID_VALUE 65535
enum BATTERYPARAM {TEMPERATURE,SOC,CURRENT,CHARGERATE,NUMOFPARAM};


struct BatteryParam_s
{
    char ParamName[20];
    float minValue;
    float maxValue;
};

struct BatteryParamOutput_s
{
    float SMA;
    float minRxd;
    float maxRxd;
};

extern struct BatteryParam_s BatteryParam[NUMOFPARAM];
