
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "Receiver.h"
#include "stddef.h"
#include "string.h"

TEST_CASE("Test for extracting values from Read string - Valid data")
{
    float tempCalc,soc,Current, ChrgRateCalc;
    char InputString[1024];
    strcpy(InputString,"Temperature:54.5        Battery_SOC:0.4        Current:10       Charge_Rate:0.12");
    tempCalc = getParam_FromRxBuffer(InputString,(TEMPERATURE));
    soc = getParam_FromRxBuffer(InputString,(SOC));
    Current = getParam_FromRxBuffer(InputString,(CURRENT));
    ChrgRateCalc = getParam_FromRxBuffer(InputString,(CHARGERATE));
    
    REQUIRE(fabs(tempCalc - 54.5)<0.01);
    REQUIRE(fabs(soc - 0.4)<0.01);
    REQUIRE(fabs(Current - 10)<0.01);
    REQUIRE(fabs(ChrgRateCalc - 0.12)<0.01);
    
}

TEST_CASE("Test for extracting values from Read string - Error data")
{
    float tempCalc,soc,Current, ChrgRateCalc;
    char InputString[1024];
    strcpy(InputString,"Temperature:ERROR        Battery_SOC:ERROR        Current:ERROR       Charge_Rate:ERROR");
    tempCalc = getParam_FromRxBuffer(InputString,(TEMPERATURE));
    soc = getParam_FromRxBuffer(InputString,(SOC));
    Current = getParam_FromRxBuffer(InputString,(CURRENT));
    ChrgRateCalc = getParam_FromRxBuffer(InputString,(CHARGERATE));
    
    REQUIRE(fabs(tempCalc - INVALID_VALUE)<0.01);
    REQUIRE(fabs(soc - INVALID_VALUE)<0.01);
    REQUIRE(fabs(Current - INVALID_VALUE)<0.01);
    REQUIRE(fabs(ChrgRateCalc - INVALID_VALUE)<0.01);
    
}

TEST_CASE("Test for error in Read string - Error data")
{
    float tempCalc,soc,Current, ChrgRateCalc;
    char InputString[1024];
    strcpy(InputString," ");
    tempCalc = getParam_FromRxBuffer(InputString,(TEMPERATURE));
    soc = getParam_FromRxBuffer(InputString,(SOC));
    Current = getParam_FromRxBuffer(InputString,(CURRENT));
    ChrgRateCalc = getParam_FromRxBuffer(InputString,(CHARGERATE));
    
    REQUIRE(fabs(tempCalc - VALUE_NOTFOUND)<0.01);
    REQUIRE(fabs(soc - VALUE_NOTFOUND)<0.01);
    REQUIRE(fabs(Current - VALUE_NOTFOUND)<0.01);
    REQUIRE(fabs(ChrgRateCalc - VALUE_NOTFOUND)<0.01);
    
}

TEST_CASE("Test case to test the Maximum Value in an array")
{
  
    float value1=10;
    float value2=20;
    float max = MaximumOfTwoFloatNumbers(value1,value2);
     REQUIRE(max == 20);
}



TEST_CASE("Test case to test the Minimum Value in an array")
{
  
    float value1=10;
    float value2=20;
    float min = MinimumOfTwoFloatNumbers(value1,value2);
    REQUIRE(min == 10);
}


TEST_CASE("Test case to test the ASimple moving average Value in an array")
{
   float  ptrArrNumbers[1][5] ={1,2,3,4,5};
   float ptrSum[1]={0};
   float avg  = movingAverageForRangeofValue(*ptrArrNumbers,ptrSum,0,5,2);
    REQUIRE(avg == 0.2f);
}



