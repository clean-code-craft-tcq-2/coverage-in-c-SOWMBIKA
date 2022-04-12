#include <stdio.h>
#include <stdbool.h>
#include "Config.h"
#include "ValidateBattery.h"
#include "SendAlertInfo.h"

// Note : In future if more number of cooling types with varying temperatures are introduced, this configuration alone can be extended to meet the need.
BatteryParam_st BatteryParamValues[MAX_COOLING_TYPES] =
{
  {
  .coolingType =  PASSIVE_COOLING,
  .lowerLimitTemp = 0,
  .higherLimitTemp = 35,
  .status = FAILURE
  },
  {
  .coolingType =  HI_ACTIVE_COOLING,
  .lowerLimitTemp = 0,
  .higherLimitTemp = 45,
  .status = FAILURE
  },
  {
  .coolingType = MED_ACTIVE_COOLING,
  .lowerLimitTemp = 0,
  .higherLimitTemp = 40,
  .status = FAILURE
  }
};
AlertTarget_st AlertTargetInfo[MAX_ALERT_TARGET_POSSIBILITIES] =
{
  {
    .alertTarget = TO_CONTROLLER,
    .alertTargetFunction = &SendAlertToController
  },
  {
     .alertTarget = TO_EMAIL,
    .alertTargetFunction = &SendAlertToEmail
  }
};


// Note : In future if mail notification needs to be configured exclusively for a particular breach pattern, this can be configured here.
MailNotification_st MailNotificationInfo[MAX_BREACH_TYPES] =
{
  {
    .breachType  = NORMAL,
    .mailNotification = NOT_REQUIRED
  },
  {
    .breachType = TOO_LOW,
    .mailNotification = REQUIRED
  },
  {
    .breachType = TOO_HIGH,
    .mailNotification = REQUIRED
  }
};
char AlertMessageOverEmail[MAX_BREACH_TYPES][100] =
{"Not Applicable","Hi, the temperature is too low\n","Hi, the temperature is too high\n"};

//In case of production environment following print functionalities are used.
// Refer test-alerts.cpp file for the stub functions used in the unit test environment
#ifdef PRODUCTION_ENVIRONMENT
FnPtrPrintToController FuncPointerPrintToController = &PrintToController ;
FnPtrPrintToEmail FuncPointerPrintToEmail = &PrintToEmail ;
#endif
