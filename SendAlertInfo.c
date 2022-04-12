#include "Config.h"
#include "ValidateBattery.h"
#include "SendAlertInfo.h"
#include <stdio.h>
#include <stdbool.h>

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
