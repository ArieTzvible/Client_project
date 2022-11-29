#pragma once
#ifndef HeaderMain
#define HeaderMain

#include "HeaderGeneral.h"
#include "HeaderPrintingManager.h"
#include "HeaderCreatingAClient.h"
#include "HeaderTest.h"

int testingFirstName(PClient cell, void* value);//First name check (specific)
int testingLastName(PClient cell, void* value);//Last name check (specific)
int testingID(PClient cell, void* value);//ID check (specific)
int testingPhone(PClient cell, void* value);//Phone check (specific)
int testingDebt(PClient cell, void* value);//Debt check (specific)
int testingDate(PClient cell, void* value);//Date check (specific)

#endif