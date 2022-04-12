#include <stdio.h>
#include <stdbool.h>
#include "BatteryConfig.h"
#include "BatteryValidation.h"


//Add here, so functionality can be extended for new parameters in future.
BatteryConfig_s BatteryParamValues[MAX_COOLING_TYPES] =
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

MailNotification_s MailNotificationInfo[MAX_BREACH_TYPES] =
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

AlertTarget_s AlertTargetInfo[MAX_ALERT_TARGET_POSSIBILITIES] =
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



char AlertMessageOverEmail[MAX_BREACH_TYPES][100] =
{"Not Applicable","Hi, the temperature is too low\n","Hi, the temperature is too high\n"};

//In case of production environment following print functionalities are used.
// Refer test-alerts.cpp file for the stub functions used in the unit test environment
#ifdef PRODUCTION_ENVIRONMENT
FnPtrPrintToController FuncPointerPrintToController = &PrintToController ;
FnPtrPrintToEmail FuncPointerPrintToEmail = &PrintToEmail ;
#endif
