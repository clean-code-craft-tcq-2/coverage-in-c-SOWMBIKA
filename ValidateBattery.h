#pragma once

BreachType InferBreach(double Value, BatteryParam_st BatteryLimits);
BatteryParam_st ClassifyTemp(CoolingType CoolingTypeInfo);
bool ValidateBattery(AlertTarget AlertTargetIndex, CoolingType CoolingTypeInfo, double TemperatureInC);
bool ValidateRange(size_t Var1, size_t Var2);
