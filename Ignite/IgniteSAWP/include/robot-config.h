#pragma once
#include "vex.h"
using namespace vex;

//A global instance of Competition
static competition Competition;

static brain Brain;
static controller Controller;

static motor fLDrive = motor(PORT9, ratio36_1, true); //
static motor bLDrive = motor(PORT18, ratio36_1, true); //
static motor uLDrive = motor(PORT16, ratio36_1); //
static motor fRDrive = motor(PORT10, ratio36_1); //
static motor bRDrive = motor(PORT20, ratio36_1); //
static motor uRDrive = motor(PORT17, ratio36_1, true); //

static motor intakelower = motor(PORT15); //
static motor intakeupper = motor(PORT19); //

static digital_out wings = digital_out(Brain.ThreeWirePort.G);
static digital_out scraper = digital_out(Brain.ThreeWirePort.H);
static digital_out midGoal = digital_out(Brain.ThreeWirePort.F);


static inertial sense = inertial(PORT14);

static optical color_sort = optical(PORT12);