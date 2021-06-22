
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "Receiver_C/test/catch.hpp"
#include "Receiver.h"

TEST_CASE("To check if file was successfully opened to read") 
{
 
  REQUIRE(BMS_ReadfromConsole()== Success); 
}

TEST_CASE("To check Minimum, Maximum and SMA of data from a file") 
{
  REQUIRE(ReceiveDatafromSender()== Success);
  
}

TEST_CASE("Test case to test the Maximum Value in an array")
{
  
  float AttributeArray[]={10,20,30,40,10};
  float actualMaxValue= 40;
  float MaximumValue=0;
  int ArraySize= sizeof(AttributeArray)/sizeof(AttributeArray[0]);
  Calculate_MaxParameterValue(AttributeArray, ArraySize, &MaximumValue);
  REQUIRE(MaximumValue == actualMaxValue);
}

TEST_CASE("Test case to test the Maximum Value in an array with negative values")
{
  
  float AttributeArray[]={10,20,30,40,10,-20};
  float actualMaxValue= 40;
  float MaximumValue=0;
  int ArraySize= sizeof(AttributeArray)/sizeof(AttributeArray[0]);
  Calculate_MaxParameterValue(AttributeArray, ArraySize, &MaximumValue);
  REQUIRE(MaximumValue == actualMaxValue);
}

TEST_CASE("Test case to test the Minimum Value in an array")
{
  
  float AttributeArray[]={10,20,30,40,10,5,2,8};
  float actualMinValue= 2;
  float MinimumValue=100;
  int ArraySize= sizeof(AttributeArray)/sizeof(AttributeArray[0]);
  Calculate_MinParameterValue(AttributeArray, ArraySize, &MinimumValue);
  REQUIRE(MinimumValue == actualMinValue);
}

TEST_CASE("Test case to test the Minimum Value in an array with negative values")
{
  
  float AttributeArray[]={10,20,30,40,10,5,2,8,-20,-18};
  float actualMinValue= -20;
  float MinimumValue=-10;
  int ArraySize= sizeof(AttributeArray)/sizeof(AttributeArray[0]);
  Calculate_MinParameterValue(AttributeArray, ArraySize, &MinimumValue);
  REQUIRE(MinimumValue == actualMinValue);
}

TEST_CASE("Test case to test the Simple Moving Average")
{
  float AttributeArray[]={10,20,30,40,10,5,2,8};
  float Actualaverage = (40+10+5+2+8)/5;
  float average = 0;
  float epsilon = 0.001;
  int ArraySize= sizeof(AttributeArray)/sizeof(AttributeArray[0]);
  average = Calculate_SimpleMovingAverage(AttributeArray, ArraySize);
  REQUIRE(abs(average - Actualaverage) < epsilon);
}
