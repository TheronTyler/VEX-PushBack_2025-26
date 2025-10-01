#pragma once
#include "vex.h"
using namespace vex;

//A global instance of Competition
competition Competition;

brain Brain;
controller Controller;

motor fLDrive = motor(PORT9, ratio36_1, true);
motor bLDrive = motor(PORT7, ratio36_1, true);
motor uLDrive = motor(PORT8, ratio36_1);
motor fRDrive = motor(PORT19, ratio36_1);
motor bRDrive = motor(PORT17, ratio36_1);
motor uRDrive = motor(PORT18, ratio36_1, true);

motor Lintake = motor(PORT10);
motor Mintake = motor(PORT15, true);
motor Uintake = motor(PORT16, true);

digital_out wings = digital_out(Brain.ThreeWirePort.H);
digital_out scraper = digital_out(Brain.ThreeWirePort.A);