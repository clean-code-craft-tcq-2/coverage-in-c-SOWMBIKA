#include <stddef.h>
#pragma once
#define TEST_ENVIRONMENT
#define INVALID_TEMPERATURE 0xff
#define SUCCESS true
#define FAILURE false

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  MAX_COOLING_TYPES,
  INVALID_COOLING_TYPE = 0xff
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
  MAX_BREACH_TYPES
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  MAX_ALERT_TARGET_POSSIBILITIES,
  INVALID_ALERT_TARGET = 0xff
} AlertTarget;

typedef enum{
  REQUIRED,
  NOT_REQUIRED
}MailNotification;

typedef struct {
  CoolingType coolingType;
  double lowerLimitTemp;
  double higherLimitTemp;
  bool status;
} BatteryParam_st;

typedef void (*FnPtrAlertTarget)(BreachType);
typedef void (*FnPtrPrintToController)(const unsigned short , BreachType);
typedef void (*FnPtrPrintToEmail)(const char* , char[]);

typedef struct 
{
  AlertTarget alertTarget;
  FnPtrAlertTarget alertTargetFunction;
}AlertTarget_st;

typedef struct 
{
  BreachType breachType;
  MailNotification mailNotification;
}MailNotification_st;

extern MailNotification_st MailNotificationInfo[MAX_BREACH_TYPES];
extern AlertTarget_st AlertTargetInfo[MAX_ALERT_TARGET_POSSIBILITIES];
extern BatteryParam_st BatteryParamValues[MAX_COOLING_TYPES];
extern char AlertMessageOverEmail[MAX_BREACH_TYPES][50];
extern FnPtrPrintToController FuncPointerPrintToController;
extern FnPtrPrintToEmail FuncPointerPrintToEmail;
bool AlertBreach(AlertTarget AlertTarget, BreachType ProcessedBreachType);
void SendAlertToController(BreachType breachType);
void SendAlertToEmail(BreachType breachType);
void PrintToController (const unsigned short Header, BreachType BreachTypeInfo);
void PrintToEmail (const char* Recepient, char Message[]);
BreachType InferBreach(double Value, BatteryParam_st BatteryLimits);
BatteryParam_st ClassifyTemp(CoolingType CoolingTypeInfo);
bool ValidateBattery(AlertTarget AlertTargetIndex, CoolingType CoolingTypeInfo, double TemperatureInC);
bool ValidateRange(size_t Var1, size_t Var2);