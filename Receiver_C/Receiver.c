
#include "Receiver.h"

/* Structure initialisation of battery parameters */
struct BatteryParam_s BatteryParam[NUMOFPARAM] =
{{"Battery_Temperature", TEMP_MIN , TEMP_MAX},
{"Battery_SOC", CHRGRATE_MIN , CHRGRATE_MAX},
{"Battery_Current",CURRENT_MIN, CURRENT_MAX},
{"Battery_Charge_Rate",CURRENT_MIN, CURRENT_MAX}
};

float getParamValuefromConsoleCustom(char *scanLine, enum BATTERYPARAM batteryParam)
{
  char splitStr[NUMOFPARAM*4][20]={'\0'};
  char * pch;
  int k=0;
  float temp;
  char buffer[MAXLENGTH_INPUTSTRING];
  
  strcpy(buffer,scanLine);
  pch = strtok(buffer," :\t");
  
  while (pch != NULL)
  {
    
    strcpy((splitStr[k]),pch);
      printf("\n%s",splitStr[k]); //debug
    k++;
    pch = strtok (NULL, " :\t");
  }
  
  for(int j=0; j < (NUMOFPARAM*4);j=j+2)
  {
        
      if(strcmp((splitStr[j]),BatteryParam[batteryParam].ParamName) == 0)
      {
          if(strcmp((splitStr[j+1]),"ERROR") == 0)
         {
          temp = ERROR_VALUE_FROM_RX;
          }
        else
        {
         temp = atof(splitStr[j+1]);
          }
         break;
      }
      else
      {
          temp = VALUE_NOTFOUND;
      }
  }

  pch = NULL;

  return temp;
}

int main()
{
//        char str[1024] = "Battery_Temperature:54.5  Battery_SOC:0.4  Battery_Current:10  Battery_Charge_Rate:0.12";
//   char *p;
//    p = str;
//   float value = getParamValuefromConsoleCustom(p,CHARGERATE);
//    printf("%f",value);
    char str[MAXLENGTH_INPUTSTRING];
  
    if(fgets(str,MAXLENGTH_INPUTSTRING, stdin)==NULL)
           {
               strcpy(str,"EoF detected");
               printf("EoF detected, stopping reception\n");
              // EoFDetected  = 1;
           }
         
          
           for (int i=0 ; i < NUMOFPARAM; i++)
           {
               float BMSParamValueRxd[NUMOFPARAM] = {0};
               BMSParamValueRxd[i] = getParamValuefromConsoleCustom(str,(enum BATTERYPARAM)i);
               printf("%f", BMSParamValueRxd[i]);
           }
}
