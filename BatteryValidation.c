#include <stdio.h>
#include <stdbool.h>
#include "BatteryValidation.h"

//Function to validate if the value is within the limits
BreachType InferBreach(double Value, BatteryConfig_s currentBatteryInfo) 
{
  if(Value < currentBatteryInfo.lowerLimitTemp) {return TOO_LOW;}
  if(Value > currentBatteryInfo.higherLimitTemp) { return TOO_HIGH;}
  return NORMAL;
}

//Function to fill the temperature limits based on cooling type.
// Here, status is added to check if the passed cooling type is valid, if not the status would be set to false.
BatteryConfig_s ClassifyTemp(CoolingType CoolingTypeInfo)
{
  BatteryConfig_s currentBatteryInfo; 
  currentBatteryInfo.status = ValidateRange(CoolingTypeInfo,MAX_COOLING_TYPES);
  currentBatteryInfo.coolingType = CoolingTypeInfo;
  currentBatteryInfo.lowerLimitTemp = BatteryInfo[CoolingTypeInfo].lowerLimitTemp;
  currentBatteryInfo.higherLimitTemp = BatteryInfo[CoolingTypeInfo].higherLimitTemp;
  return currentBatteryInfo;
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
  BatteryConfig_s batteryTempLimits;
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

//In case of production environment following print functionalities are used.
// Refer test-alerts.cpp file for the stub functions used in the unit test environment
#ifdef PRODUCTION_ENVIRONMENT
void PrintToController (const unsigned short Header, BreachType BreachTypeInfo)
{
      printf("%x : %x\n", Header, BreachTypeInfo);
}

void PrintToEmail (const char* Recepient, char Message[])
{
      printf("To: %s\n%s", Recepient,Message);
}
#endif

// This function is to alert the breach to the user.
// Here the value of the alertTarget is checked to ensure that it is within the possible limits configured in alertConfig files.
bool AlertBreach(AlertTarget AlertTargetIndex, BreachType processedBreachType) 
{
  if(ValidateRange(AlertTargetIndex,MAX_ALERT_TARGET_POSSIBILITIES))
  {
     // Refer to alertConfig files for the configured function pointer.
     // Function pointer is used if in case more alerting mechanisms (other than controller / email) pops in, this can be configured.
    AlertTargetInfo[AlertTargetIndex].alertTargetFunction(processedBreachType);
    return SUCCESS;
  }
   return FAILURE;
}

// This function makes out the parameters required to send the alert information to controller.
// Note : if in case in the future if any other way of conveying the breach information is introduced,
// without touching any other piece of code, just a function similar to this can be added and configured.
void SendAlertToController(BreachType BreachTypeInfo) 
{
  const unsigned short header = 0xfeed;
  // Refer to alertConfig files for the configured function pointer.
  FuncPointerPrintToController(header,BreachTypeInfo);
}

// This function makes out the parameters required to send the alert information through Email.
// Note : if in case in the future if any other way of conveying the breach information is introduced,
// without touching any other piece of code, just a function similar to this can be added and configured.
void SendAlertToEmail(BreachType BreachTypeInfo) 
{
  const char* recepient = "a.b@c.com";
  if(MailNotificationInfo[BreachTypeInfo].mailNotification == REQUIRED)
  {
    // Refer to alertConfig files for the configured function pointer.
    FuncPointerPrintToEmail(recepient,AlertMessageOverEmail[BreachTypeInfo]);
  }
}
