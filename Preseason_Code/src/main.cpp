/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Theron Tyler                                                     */
/*    Created:      9/29/2025, 1:51:49 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "robot-config.h"
#include "vex.h"

using namespace vex;

void pre_auton(void) {

  //Speed
  motor_group(Uintake, Mintake, Lintake).setVelocity(95, pct);

  //Stopping
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setStopping(coast);
  motor_group(Uintake, Mintake, Lintake).setStopping(coast);
}

void autonomous(void) {
  motor_group(fLDrive, bLDrive, uLDrive).spinFor(.58, rev, false);
  motor_group(fRDrive, bRDrive, uRDrive).spinFor(.58, rev, false);
  wait(1.67,sec);
  
  //motor_group(Uintake, Mintake, Lintake).spinFor(1.98, rev, false);

  motor_group(fLDrive, bLDrive, uLDrive).spinFor(-.18, rev, false);
  motor_group(fRDrive, bRDrive, uRDrive).spinFor(.18, rev);
wait(.67, sec);
  motor_group(fLDrive, bLDrive, uLDrive).spinFor(.4, rev, false);
  motor_group(fRDrive, bRDrive, uRDrive).spinFor(.4, rev, false);

  wait(.4, sec);

  motor_group(Uintake, Mintake, Lintake).spinFor(-2.5, rev, false);

  //intake

}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
  
  //Drivetrain
  int rotational = Controller.Axis3.position(pct);
  int lateral = Controller.Axis1.position(pct);

  motor_group(fLDrive, bLDrive, uLDrive).spin(fwd, (lateral)*.5 + rotational, pct);
  motor_group(fRDrive, bRDrive, uRDrive).spin(reverse, (lateral)*.5 - rotational, pct);

  //Intake
  if (Controller.ButtonL1.pressing()) {
    motor_group(Uintake, Mintake, Lintake).spin(fwd, 80, pct);
  }
  else if (Controller.ButtonL2.pressing()) {
    motor_group(Uintake, Mintake, Lintake).spin(reverse, 80, pct);
  }
  else if (Controller.ButtonR2.pressing()) {
    Uintake.spin(reverse, 80, pct);
    motor_group(Mintake, Lintake).spin(fwd, 80, pct);
  }
  else {
    motor_group(Uintake, Mintake, Lintake).stop();
  }

  //Wings
  if (Controller.ButtonB.pressing()) {
    wings.set(true);
  }
  else if (Controller.ButtonDown.pressing()) {
    wings.set(false);
  }

  //Scraper
  if (Controller.ButtonLeft.pressing()) {
    scraper.set(true);
  }
  else if (Controller.ButtonUp.pressing()) {
    scraper.set(false);
  }
  
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
