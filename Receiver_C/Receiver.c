
#include "Receiver.h"

/* Structure initialisation of battery parameters */
struct BatteryParam_s BatteryParam[NUMOFPARAM] =
{{"Battery_Temperature", TEMP_MIN , TEMP_MAX},
{"Battery_SOC", CHRGRATE_MIN , CHRGRATE_MAX},
{"Battery_Current",CURRENT_MIN, CURRENT_MAX},
{"Battery_Charge_Rate",CURRENT_MIN, CURRENT_MAX}
};

int GetParamDataString(char *appendStr, int stringSize)
{
	int EoFDetected = 0;
	
	/*Released only for console, if in future, it is from file, it can be adapted here*/
	while ((int ch = getchar()) != '\n' && ch != EOF);
	if(fgets(appendStr,stringSize,stdin)== NULL)
	{
		//strcpy(appendStr,"EoF detected");
		printf("EoF detectedstatus, stopping reception\n");
	    EoFDetected  = 1;
	}
	
	return EoFDetected;
}

float getParamValuefromConsoleCustom(char *scanLine, enum BATTERYPARAM batteryParam)
{
  char splitStr[NUMOFPARAM*4][10]={'\0'};
  char * pch;
  int k=0;
  float temp;
  char buffer[MAXLENGTH_INPUTSTRING];
//   char str[1024] = "Battery_Temperature:54.5  Battery_SOC:0.4  Battery_Current:10  Battery_Charge_Rate:0.12";
//  char *p;
//    p = str;
  strcpy(buffer,scanLine);
 printf("\npch is null0=%s",scanLine);//DEBUG
 pch = strtok (buffer," :\t");
 printf("\npch is null0=%s",pch); //DEBUG
	
  
  if(pch == NULL)
  {
  printf("\npch is null=%s",pch); //DEBUG
  }
  
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
    int EoFDetected =0;
  do
    {
    EoFDetected = GetParamDataString(str,MAXLENGTH_INPUTSTRING);
	 // if(gets(str)==NULL)
	 while ((int ch = getchar()) != '\n' && ch != EOF);
        if(fgets(str,MAXLENGTH_INPUTSTRING, stdin)!=NULL)
           {
		printf("%d\n",ferror(stdin));
             //  strcpy(str,"EoF detected");
               printf("EoF detected, stopping reception\n");
              EoFDetected  = 1;
           }
         
          
           for (int i=0 ; i < NUMOFPARAM; i++)
           {
               float BMSParamValueRxd[NUMOFPARAM] = {0};
               BMSParamValueRxd[i] = getParamValuefromConsoleCustom(str,(TEMPERATURE));
               printf("\n%f", BMSParamValueRxd[i]);
           }
    }while(!(EoFDetected == 1));
}
