#pragma once
#include "vex.h"

//Calling Function
void turn(float turnTarget);
void drive(float driveTarget);

//Turn Variables
float turnTarget;
float turnKp;
float turnKi;
float turnKd;
float turnError;
float previousTurnError;
float turnP;
float turnI;
float turnD;

//Drive Variables
float driveTarget;
float driveKp;
float driveKi;
float driveKd;
float driveError;
float previousDriveError;
float driveP;
float driveI;
float driveD;