#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include <stdbool.h>
#include "Config.h"
#include "ValidateBattery.h"
#include "SendAlertInfo.h"

// Note : For the test environment stub for all the print interfaces used
#ifdef TEST_ENVIRONMENT
int Test_PrintToControllerStubCount;
int Test_PrintToEmailStubCount;
void PrintToControllerStub (const unsigned short Header, BreachType BreachTypeInfo)
{
      Test_PrintToControllerStubCount++;
}
void PrintToEmailStub (const char* Recepient, char Message[])
{
      Test_PrintToEmailStubCount++;
}
FnPtrPrintToController FuncPointerPrintToController = &PrintToControllerStub;
FnPtrPrintToEmail FuncPointerPrintToEmail = &PrintToEmailStub;
#endif 


TEST_CASE("InferBreach -Temperature value passed is less than lower limit") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 15;
  REQUIRE(InferBreach(value, BatteryLimits) == TOO_LOW);
}

TEST_CASE("InferBreach - Temperature value passed is more than higher limit") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 60;
  REQUIRE(InferBreach(value, BatteryLimits) == TOO_HIGH);
}

TEST_CASE("InferBreach - Temperature value passed is in the normal range") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 30;
  REQUIRE(InferBreach(value, BatteryLimits) == NORMAL);
}

TEST_CASE("InferBreach - Temperature value passed is in the lower boundary") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 20;
  REQUIRE(InferBreach(value, BatteryLimits) == NORMAL);
}

TEST_CASE("InferBreach -Temperature value passed is in the higher boundary") {
  BatteryParam_st BatteryLimits;
  BatteryLimits.lowerLimitTemp = 20;
  BatteryLimits.higherLimitTemp = 50;
  double value = 50;
  REQUIRE(InferBreach(value, BatteryLimits) == NORMAL);
}

TEST_CASE("ClassifyTemp -Positive scenario- PASSIVE_COOLING Cooling Type based lower and upper temperature limit derivation ") {
  BatteryParam_st BatteryLimits;
  BatteryLimits = ClassifyTemp(PASSIVE_COOLING);
  REQUIRE(BatteryLimits.status  == SUCCESS);
  REQUIRE(BatteryLimits.coolingType  == PASSIVE_COOLING);
  REQUIRE(BatteryLimits.lowerLimitTemp  == 0);
  REQUIRE(BatteryLimits.higherLimitTemp == 35);
}

TEST_CASE("ClassifyTemp -Positive scenario- HI_ACTIVE_COOLING Cooling Type based lower and upper temperature limit derivation ") {
  BatteryParam_st BatteryLimits;
  BatteryLimits = ClassifyTemp(HI_ACTIVE_COOLING);
  REQUIRE(BatteryLimits.status  == SUCCESS);
  REQUIRE(BatteryLimits.coolingType  == HI_ACTIVE_COOLING);
  REQUIRE(BatteryLimits.lowerLimitTemp  == 0);
  REQUIRE(BatteryLimits.higherLimitTemp == 45);
}

TEST_CASE("ClassifyTemp -Positive scenario- MED_ACTIVE_COOLING Cooling Type based lower and upper temperature limit derivation ") {
  BatteryParam_st BatteryLimits;
  BatteryLimits = ClassifyTemp(MED_ACTIVE_COOLING);
  REQUIRE(BatteryLimits.status  == SUCCESS);
  REQUIRE(BatteryLimits.coolingType  == MED_ACTIVE_COOLING);
  REQUIRE(BatteryLimits.lowerLimitTemp  == 0);
  REQUIRE(BatteryLimits.higherLimitTemp == 40);
}

TEST_CASE("ClassifyTemp -Negative scenario- INVALID_COOLING_TYPE  Test cooling type which is not under the configured list ") {
  BatteryParam_st BatteryLimits;
  BatteryLimits = ClassifyTemp(INVALID_COOLING_TYPE);
  REQUIRE(BatteryLimits.status  == FAILURE);
}
