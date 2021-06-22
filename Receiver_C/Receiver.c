**********************************************
Include header files
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bms_receiver.h"

/***********************************************************************************************************************
Variable declaration
**************************************************************************************************************************/
float MinimumAttributeValueArray[NumberOfAttributes]= {100,100};
float MaximumAttributeValueArray[NumberOfAttributes]= {0,0};
float Temperature[Max_ArraySize]={};
float SoC[Max_ArraySize]={};
int NoOfEntery=0;

/***************************************************************************************************************************
Function definitions
****************************************************************************************************************************/

/**************************************************************************************************************************
 * Function: BMS_Readfromdatafile
 * Description: This function reads the BMS parameter readings from the suitable 
   data log file and stores into a buffer  
 * input: void
 * returns: Read status is Success(True) if the data is successfully read from the file.
 ***************************************************************************************************************************/
OperationMode BMS_ReadfromConsole()
{
  FILE *BMS_datafile;
  int line=1, Index=0;
  OperationMode ReadStatus= Failure;

  BMS_datafile=fopen("BMS_attributelog.txt", "r");
  if (BMS_datafile==NULL)
    {
      printf("File open attempt failed\n");

    }
	
  else
    {

	float ReadTemperature=0,ReadSoC=0;
         printf("File open attempt successful\n");

	      while(line != EOF)
		{
		  line=fscanf(BMS_datafile,"%f %f",&ReadTemperature,&ReadSoC);
		  Temperature[Index]=ReadTemperature;
		  SoC[Index]=ReadSoC;
		  Index++;
		}
		NoOfEntery= Index;
		ReadStatus= Success;
	    }
	
	fclose(BMS_datafile);
	return ReadStatus;
}
/***********************************************************************************************************************************
 * Function: Calculate_TemperatureMinandMaxRange
 * Description: This function calculates the maximum and minimum range of temperature in a given
                data array.
 * input: The number of data values available.	  
 * returns: NULL, it prints the minimum and maximum value on the console
 ***********************************************************************************************************************************/

void Calculate_TemperatureMinandMaxRange(int NoOfEnteries)
{
 Calculate_MinParameterValue(Temperature, NoOfEnteries, &MinimumAttributeValueArray[0]);
 Calculate_MaxParameterValue(Temperature, NoOfEnteries, &MaximumAttributeValueArray[0]);
 printf("Minimum and Maximum Temperature in the given range is %0.2f F and %0.2f F respectively\n",MinimumAttributeValueArray[0],MaximumAttributeValueArray[0]);
}


/**********************************************************************************************************************************
 * Function: Calculate_StateOfChargeMinandMaxRange
 * Description: This function calculates the maximum and minimum range of SoC (State-Of-Charge) in a given
                data array. 
 * input: The number of data values available.  
 * returns: NULL, it prints the minimum and maximum value on the console
 **********************************************************************************************************************************/
void Calculate_SoCMinandMaxRange(int NoOfEnteries)
{
  
  Calculate_MinParameterValue(SoC, NoOfEnteries, &MinimumAttributeValueArray[1]);
  Calculate_MaxParameterValue(SoC, NoOfEnteries, &MaximumAttributeValueArray[1]);
  printf("Minimum and Maximum State-of-Charge in the given range is %0.2f%% and %0.2f%% respectively\n",MinimumAttributeValueArray[1],MaximumAttributeValueArray[1]);
}


/*****************************************************************************************************************************
 * Function: Calculate_MaxParameterValue
 * Description: This function calculates the maximum value of an attribute in a given range. 
 * input: The number of data values available, data values and the threshold/reference value.
 * returns: The maximum value in the given range
 ****************************************************************************************************************************/
 void Calculate_MaxParameterValue(float AttributeValue[], int NoOfEnteries, float *MaximumAttributeValue)
 {
   for(int i=0; i< NoOfEnteries; i++)
   {
        if(AttributeValue[i] > *MaximumAttributeValue)
        {
            *MaximumAttributeValue = AttributeValue[i];
        }
   }
   
 }


/****************************************************************************************************************************
 * Function: Calculate_MinParameterValue
 * Description: This function calculates the minimum value of an attribute in a given range. 
 * input: The number of data values available, data values and the threshold/reference value.	  
 * returns: The minimum value in the given range
 ****************************************************************************************************************************/
void Calculate_MinParameterValue(float AttributeValue[], int NoOfEnteries, float *MinimumAttributeValue)
 {
  for(int i=0; i< NoOfEnteries; i++)
   {
     
     if(AttributeValue[i] < *MinimumAttributeValue)
          {
              *MinimumAttributeValue = AttributeValue[i];
          }
   }
}


/*********************************************************************************************************************************
 * Function: Calculate_TemperatureSimpleMovingAverage
 * Description: This function calculates the average value of Temperature over latest 5 data points.   
 * input: The number of data values available.	  
 * returns: The average value of temperature in the given range
 *********************************************************************************************************************************/
void Calculate_TemperatureSimpleMovingAverage(int NoOfEnteries)
{
  float Temperature_SMA= Calculate_SimpleMovingAverage(Temperature, NoOfEnteries);
  printf("Simple moving average of Temperature is %0.2f F\n",Temperature_SMA);
}


/********************************************************************************************************************************
 * Function: Calculate_SoCSimpleMovingAverage
 * Description: This function calculates the average value of SoC over latest 5 data points.
 * input: The number of data values available	  
 * returns: The average value of temperature in the given range
 ******************************************************************************************************************************/
void Calculate_SoCSimpleMovingAverage(int NoOfEnteries)
{
  float SoC_SMA= Calculate_SimpleMovingAverage(SoC, NoOfEnteries);
  printf("Simple moving average of State-of-Charge is %0.2f%%\n",SoC_SMA);
}



/***********************************************************************************************
 * Function: Calculate_SimpleMovingAverage
 * Description: This function calculates the average value of an attribute in a over latest 5 data points. 
 * input: The number of data values available.	  
 * returns: The average value of attribute in the given range
 ***********************************************************************************************/

float Calculate_SimpleMovingAverage(float AttributeValue[], int NoOfEnteries)
{
  float AttributeAverage = 0;
  float AttributeSum = 0;
  for(int i=(NoOfEnteries-5); i< NoOfEnteries; i++)
   {
     AttributeSum+= AttributeValue[i];
     
   }
   AttributeAverage = AttributeSum/5;

   return AttributeAverage;
  
}



/******************************************************************************************************************************
 * Function: ReceiveDatafromSender
 * Description: This function reads the data from Sender, calculates the Min, max and average value of BMS_attribute.	  
 * returns: The operation was successful
 *****************************************************************************************************************************/
OperationMode ReceiveDatafromSender ()
{
    OperationMode ReadStatus= Failure;
    ReadStatus= BMS_ReadfromConsole();
    //printf("%d\n",NoOfEntery);
    if (ReadStatus)
    	{
	    Calculate_TemperatureMinandMaxRange(NoOfEntery);
	    Calculate_SoCMinandMaxRange(NoOfEntery);
	    Calculate_TemperatureSimpleMovingAverage(NoOfEntery);
	    Calculate_SoCSimpleMovingAverage(NoOfEntery);
        }
    return (ReadStatus);
}
