#pragma once
#include "vex.h"
using namespace vex;

//A global instance of Competition
static competition Competition;

static brain Brain;
static controller Controller;

static motor fLDrive = motor(PORT14, ratio36_1, true);
static motor bLDrive = motor(PORT16, ratio36_1, true);
static motor uLDrive = motor(PORT15, ratio36_1);
static motor fRDrive = motor(PORT18, ratio36_1);
static motor bRDrive = motor(PORT19, ratio36_1);
static motor uRDrive = motor(PORT20, ratio36_1, true);

static motor intakelower = motor(PORT13, true);
static motor intakeupper = motor(PORT17);

static digital_out wings = digital_out(Brain.ThreeWirePort.G);
static digital_out scraper = digital_out(Brain.ThreeWirePort.H);

static inertial sense = inertial(PORT10);

static rotation perpPod = rotation(PORT11);
static rotation paraPod = rotation(PORT7);

static distance backDist = distance(PORT8);
static distance leftDist = distance(PORT9);

static optical color_sort = optical(PORT12);