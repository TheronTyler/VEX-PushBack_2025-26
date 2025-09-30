#pragma once
#include "vex.h"
using namespace vex;

//A global instance of Competition
competition Competition;

brain Brain;
controller Controller;

motor fLDrive = motor(PORT8, ratio36_1, true);
motor bLDrive = motor(PORT9, ratio36_1, true);
motor uLDrive = motor(PORT10, ratio36_1);
motor fRDrive = motor(PORT2, ratio36_1);
motor bRDrive = motor(PORT5, ratio36_1);
motor uRDrive = motor(PORT4, ratio36_1, false);

motor Lintake = motor(PORT10);
motor Mintake = motor(PORT15, true);
motor Uintake = motor(PORT16, true);

digital_out wings = digital_out(Brain.ThreeWirePort.H);
digital_out scraper = digital_out(Brain.ThreeWirePort.A);