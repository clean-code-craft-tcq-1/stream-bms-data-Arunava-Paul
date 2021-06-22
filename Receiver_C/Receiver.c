
/* **************************************************************************************************
* File Name   : Receiver.c
* Description : Source file for BMS Receiver type selection .
                Here we are receiving BMS temperature,SOC,Current and Charge rate parameters and calculating Min ,Max and SMA from incoming stream
* Author      : Harshitha Subramani
* * ************************************************************************************************** */


/**********************************************
Include header files
***********************************************/

#include "Receiver.h"

/***********************************************************************************************************************
Variable declaration
**************************************************************************************************************************/
/*Buffer initialisation for SMA calculation*/
   float BMSParamValueRxd[NUMOFPARAM] = {0};
   float ReadingsBuffer[NUMOFPARAM][SMA_RANGE]= {0};
   float ReadingsSum[NUMOFPARAM]={0};

/* Structure initialisation of battery evaluated parameters */
struct BatteryParam_s BatteryParam[NUMOFPARAM] = {{"Temperature", TEMP_MIN , TEMP_MAX},
    {"Battery_SOC", SOC_MIN , SOC_MAX},{"Current", CURRENT_MIN , CURRENT_MAX},{"Charge_Rate", CHRGRATE_MIN , CHRGRATE_MAX},};

/* Structure initialisation of battery evaluated parameters */
   struct BatteryParamOutput_s BatteryParamEvaluated[NUMOFPARAM]= {{0, TEMP_MAX, TEMP_MIN},{0, SOC_MAX, SOC_MIN},{0, CURRENT_MAX, CURRENT_MIN},{0, CHRGRATE_MAX, CHRGRATE_MIN},};

/***************************************************************************************************************************
Function definitions
****************************************************************************************************************************/

/****************************************************************************************
*Func desc : The function extracts the paramater values from a stream of data received
*Param     :input string read from file with BMS paramater assigned
           
*Return    : Individual Rx values of BMS Paramter received
*****************************************************************************************/
float getParam_FromRxBuffer(char *ReadLine, enum BATTERYPARAM batteryParam)
{
  char token[NUMOFPARAM*4][12]={'\0'};
  char * Chr;
  int k=0;
  float Readvalue;
  char buffer[BUFFER_SIZE];
  
  strcpy(buffer,ReadLine);
  Chr = strtok (buffer," :\t");
  
  while (Chr != NULL)
  {
    
    strcpy((token[k]),Chr);
    //printf("\nsplit=%s",token[k]);   //debug
    k++;
    Chr = strtok (NULL, " :\t");
    //printf("\npch=%s",Chr);
  }
  
  for(int j=0;j < (NUMOFPARAM*4);j=j+2)
  {
      
      if(strcmp((token[j]),BatteryParam[batteryParam].ParamName) == 0)
      {
          if(strcmp((token[j+1]),"ERROR") == 0)
          {
              Readvalue = INVALID_VALUE;
          }
          else
          {
              Readvalue = atof(token[j+1]);
           
          }
         break;
              
      }
      else
      {
          Readvalue = VALUE_NOTFOUND;
      }
  }

    Chr = NULL;
   
  return Readvalue;
}

/****************************************************************************************
*Func desc : The function returns minimum  of two values passed
*Param     : value1   - Value1
             value2   - Value2
*Return    : minimum  of 2 values passed - float type
*****************************************************************************************/
float MinimumOfTwoFloatNumbers(float value1, float value2)
{
    if (value1 < value2)
    {
        return value1;
    }
    else
    {
        return value2;
    }
}

/****************************************************************************************
*Func desc : The function returns maximum of two values passed
*Param     : value1   - Value1
             value2   - Value2
*Return    : maximum of 2 values passed - float type
*****************************************************************************************/
float MaximumOfTwoFloatNumbers(float value1, float value2)
{
    if (value1 > value2)
    {
        return value1;
    }
    else
    {
        return value2;
    }
}
/****************************************************************************************
*Func desc : This function calculates the average value of Temperature over latest 5 data points
*Param     : Array input ,Data range for avg calculation ,BMS Paramtater
            
*Return    : moving average of latest 5 values
*****************************************************************************************/
float movingAverageForRangeofValue(float *ptrArrNumbers, float *ptrSum, int param_id, int range, float nextNum)
{
    static int pos[NUMOFPARAM]= {0};
    
    if(range>1)
    {
   
       *ptrSum = *ptrSum - ptrArrNumbers[pos[param_id]] + nextNum;
  
        ptrArrNumbers[pos[param_id]] = nextNum;
        
        pos[param_id]++;
        if (pos[param_id] >= range)
        {
            pos[param_id] = 0;
        }
        
        return *ptrSum / range;
        
    }
    else if (range == 1)
    {
       return nextNum;
        
    }
    else
    {
        return INVALID_SMARANGE;
    }
 
}


/****************************************************************************************
*Func desc : This function reads the inputs from Rx file and calculates Min, Max and Moving avg for input stream
*Param     :
*Return    : NULL
*****************************************************************************************/
void RxCalculate_FromBMSParam()
{
    int x;
    FILE *fp;
    char InputString[1024];
    fp = fopen("Receiver_C/BMS_RXData.txt", "r");
  while (fgets(InputString,1024,(FILE*)fp))
  {
      for( x=0;x<NUMOFPARAM;x++)
      {
          BMSParamValueRxd[x] = getParam_FromRxBuffer(InputString,(enum BATTERYPARAM)x);
          printf("values are =%f\n",BMSParamValueRxd[x]);
          
        BatteryParamEvaluated[x].MovingAvg =  movingAverageForRangeofValue((ReadingsBuffer[x]), (ReadingsSum+x), x, SMA_RANGE, BMSParamValueRxd[x]);
          
         BatteryParamEvaluated[x].minRx = MinimumOfTwoFloatNumbers(BMSParamValueRxd[x],BatteryParamEvaluated[x].minRx);
                          
         BatteryParamEvaluated[x].maxRx = MaximumOfTwoFloatNumbers(BMSParamValueRxd[x],BatteryParamEvaluated[x].maxRx);
     }
 
}
    printf("Temperature:%f, Battery_SOC:%f,Current:%f, Charge_Rate:%f\n",BMSParamValueRxd[0],BMSParamValueRxd[1],BMSParamValueRxd[2],BMSParamValueRxd[3]);
             printf("SMA Temperature:%f, Battery_SOC:%f,Current:%f, Charge_Rate:%f\n",BatteryParamEvaluated[0].MovingAvg,BatteryParamEvaluated[1].MovingAvg,BatteryParamEvaluated[2].MovingAvg,BatteryParamEvaluated[3].MovingAvg);
            printf("Min Temperature:%f, Battery_SOC:%f,Current:%f, Charge_Rate:%f\n",BatteryParamEvaluated[0].minRx,BatteryParamEvaluated[1].minRx,BatteryParamEvaluated[2].minRx,BatteryParamEvaluated[3].minRx);
            printf("Max Temperature:%f, Battery_SOC:%f,Current:%f, Charge_Rate:%f\n",BatteryParamEvaluated[0].maxRx,BatteryParamEvaluated[1].maxRx,BatteryParamEvaluated[2].maxRx,BatteryParamEvaluated[3].maxRx);
}
 
//#ifdef MAIN
int main()
{
    RxCalculate_FromBMSParam();
   return 0;
}
//#endif
