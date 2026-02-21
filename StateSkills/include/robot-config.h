#pragma once
#include "vex.h"
using namespace vex;

// ========== GLOBAL INSTANCE OF COMPETITION ==========
competition Competition;

// ========== ROBOT CONFIGURATION ==========
brain Brain;
controller Controller;

// Drive motors (6-motor drive)

// Left side motors
motor fLDrive = motor(PORT9, ratio6_1, true);
motor bLDrive = motor(PORT18, ratio6_1, true);
motor uLDrive = motor(PORT16, ratio6_1);

// Right side motors
motor fRDrive = motor(PORT10, ratio6_1);
motor bRDrive = motor(PORT20, ratio6_1); 
motor uRDrive = motor(PORT17, ratio6_1, true);

// ========== INTAKE ==========
motor intakeLower = motor(PORT15, ratio6_1);
motor intakeUpper = motor(PORT19, ratio6_1, true);

// ========== PNEUMATICS =========
digital_out wing = digital_out(Brain.ThreeWirePort.G);
digital_out scraper = digital_out(Brain.ThreeWirePort.H);
digital_out midGoal = digital_out(Brain.ThreeWirePort.F);

// ========== SENSORS ==========
inertial IMU = inertial(PORT14);

rotation horizontalRotation = rotation(PORT11, false);

distance rightDistance = distance(PORT11);
distance backDistance = distance(PORT12);