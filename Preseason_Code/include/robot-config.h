#pragma once
#include "vex.h"
using namespace vex;

//A global instance of Competition
static competition Competition;

static brain Brain;
static controller Controller;

static motor fLDrive = motor(PORT8, ratio36_1, true);
static motor bLDrive = motor(PORT9, ratio36_1, true);
static motor uLDrive = motor(PORT10, ratio36_1);
static motor fRDrive = motor(PORT2, ratio36_1);
static motor bRDrive = motor(PORT5, ratio36_1);
static motor uRDrive = motor(PORT4, ratio36_1, false);

static motor Lintake = motor(PORT10);
static motor Mintake = motor(PORT15, true);
static motor Uintake = motor(PORT16, true);

static digital_out wings = digital_out(Brain.ThreeWirePort.H);
static digital_out scraper = digital_out(Brain.ThreeWirePort.A);

static inertial sense = inertial(PORT11);