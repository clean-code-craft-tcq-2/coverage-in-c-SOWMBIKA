bool AlertBreach(AlertTarget AlertTarget, BreachType ProcessedBreachType);
void SendAlertToController(BreachType breachType);
void SendAlertToEmail(BreachType breachType);
void PrintToController (const unsigned short Header, BreachType BreachTypeInfo);
void PrintToEmail (const char* Recepient, char Message[]);
