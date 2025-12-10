#include "robot-config.h"
#include "vex.h"

void turn(float turnTarget) {

  // --- PID CONSTANTS ---
  float turnKp = 0.4;
  float turnKi = 0;
  float turnKd = 0;

  // --- PID VARIABLES ---
  float turnError = 0;
  float previousTurnError = 0;
  float turnIntegral = 0;
  float turnDerivative = 0;
  float turnOutput = 0;

  // Normalize heading so 180 is the "zero" point
  sense.setHeading(180, degrees);

  // Main PID Loop
  while (true) {

    // Error (Target – Current Heading)
    turnError = turnTarget - sense.heading();

    // Exit condition
    if (fabs(turnError) < 3) {
      break;
    }

    // Integral
    turnIntegral += turnError * 0.02;       // 20ms loop time
    if (turnIntegral > 50) turnIntegral = 50;

if (turnIntegral < -50) turnIntegral = -50;
 // Prevent runaway integral

    // Derivative
    turnDerivative = (turnError - previousTurnError) / 0.02;

    // PID Output
    turnOutput = 
          turnKp * turnError +
          turnKi * turnIntegral +
          turnKd * turnDerivative;

    // Apply to motors (left is +, right is -)
    motor_group(fLDrive, bLDrive, uLDrive).spin(fwd, turnOutput, pct);
    motor_group(fRDrive, bRDrive, uRDrive).spin(fwd, -turnOutput, pct);

    // Save error for next loop
    previousTurnError = turnError;

    wait(20, msec);
  }

  // Stop motors cleanly
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setStopping(brake);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).stop();
}


void drive(float driveTarget) {   // driveTarget is in degrees ( (DISTANCE / 47.33) * 360 )

  
  float driveKp = 0.4; //tune?
  float driveKi = 0; //tune?
  float driveKd = 0; //tune?

  float driveError = 0;
  float previousDriveError = 0;
  float driveIntegral = 0;
  float driveDerivative = 0;
  float driveOutput = 0;

  fLDrive.setPosition(0, deg);
  fRDrive.setPosition(0, deg);

  while (true) {
    float currentPos = (fLDrive.position(deg) + fRDrive.position(deg)) / 2.0;
    driveError = driveTarget - currentPos;

    if (fabs(driveError) < 10) {
      break;
    }

    driveIntegral += driveError * 0.02;
    if (driveIntegral > 50) driveIntegral = 50;
    if (driveIntegral < -50) driveIntegral = -50;

    driveDerivative = (driveError - previousDriveError) / 0.02;

    driveOutput =
          driveKp * driveError +
          driveKi * driveIntegral +
          driveKd * driveDerivative;

    // Apply to all motors
    motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spin(fwd, driveOutput, pct);

    // Save previous error
    previousDriveError = driveError;

    wait(20, msec);
  }

  // Stop motors cleanly
  motor_group(fLDrive, bLDrive, uLDrive, 
              fRDrive, bRDrive, uRDrive).setStopping(brake);
  motor_group(fLDrive, bLDrive, uLDrive, 
              fRDrive, bRDrive, uRDrive).stop();
}

/*void drive(float driveTarget){  //(DISTANCE / 47.33)*360
  fLDrive.setPosition(0, deg);
  fRDrive.setPosition(0, deg);

  float driveKp = .15; //needs tuned
  float driveKi = .255; //needs tuned
  float driveKd = .25; //needs tuned
  float driveError = driveTarget - ((fLDrive.position(deg) + fRDrive.position(deg)) / 2); 
  
  while (fabs(driveError) > 10){
  driveError = driveTarget - (fLDrive.position(deg));
  float previousDriveError = driveError;
  float driveP = driveKp * driveError;
  float driveI = driveI + (.02 * driveError * driveKi);
  float driveD = driveKd * (driveError - previousDriveError)/1;

    motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spin(fwd, (driveP + driveI + driveD)*1.3, pct);
    wait (20, msec);
  }
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setStopping(brake);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spin(fwd, 0, pct);
}*/