#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "BatteryValidation.h"

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

TEST_CASE("InferBreach -Lower limit Temperature Check") {
  BatteryConfig_s BatteryInfo;
  BatteryInfo.lowerLimitTemp = 20;
  BatteryInfo.higherLimitTemp = 50;
  double value = 15;
  REQUIRE(InferBreach(value, BatteryInfo) == TOO_LOW);
}
