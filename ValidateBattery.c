#include <stdio.h>
#include <stdbool.h>
#include "Config.h"
#include "ValidateBattery.h"
#include "SendAlertInfo.h"

//Function to validate if the value is within the limits
BreachType InferBreach(double Value, BatteryParam_st BatteryLimits) 
{
  if(Value < BatteryLimits.lowerLimitTemp) {return TOO_LOW;}
  if(Value > BatteryLimits.higherLimitTemp) { return TOO_HIGH;}
  return NORMAL;
}

//Function to fill the temperature limits based on cooling type.
// Here, status is added to check if the passed cooling type is valid, if not the status would be set to false.
BatteryParam_st ClassifyTemp(CoolingType CoolingTypeInfo)
{
  BatteryParam_st batteryParameters; 
  batteryParameters.status = ValidateRange(CoolingTypeInfo,MAX_COOLING_TYPES);
  batteryParameters.coolingType = CoolingTypeInfo;
  batteryParameters.lowerLimitTemp = BatteryParamValues[CoolingTypeInfo].lowerLimitTemp;
  batteryParameters.higherLimitTemp = BatteryParamValues[CoolingTypeInfo].higherLimitTemp;
  return batteryParameters;
}

// Utility function to validate if the variable 1 is within the specified range.
// NOTE : This is exclusively introduced to check the inputs of the battery that needs to be validated.
// If the user passes information that are not part of configuration, then that needs to be discarded, for which this validation is required.
bool ValidateRange(size_t Var1, size_t Var2)
{
  if((Var1 >= 0) && (Var1 < Var2)) { return true;} 
  return false;
}

// Primary function which takes in user parameters to validate the battery.
// Status is checked if the parameters passed are within permissible range.
bool ValidateBattery(AlertTarget AlertTargetInfo, CoolingType CoolingTypeInfo, double TemperatureInC)
{
  BatteryParam_st batteryTempLimits;
  BreachType processedBreachType;
  bool status = FAILURE;
  batteryTempLimits = ClassifyTemp(CoolingTypeInfo);
  // If invalid CoolingTypeInfo is passed, then ValidateBattery function would return FAILURE
  if(batteryTempLimits.status == SUCCESS)
  {
    processedBreachType = InferBreach(TemperatureInC,batteryTempLimits);
     // If invalid Alert type is passed, then ValidateBattery function would return FAILURE
    status = AlertBreach(AlertTargetInfo , processedBreachType);
  }
  return status;
}
