/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Theron Tyler                                              */
/*    Created:      9/20/2024, 8:15:00 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "robot-config.h"
#include "PID.h"

//#include "turnHeading.h"

using namespace vex;

// A global instance of competition
void pre_auton(void) {

//Speed
motor_group(intakeupper, intakelower).setVelocity(95,pct);


//Stopping
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setStopping(coast);
motor_group(intakeupper, intakelower).setStopping(brake);

}

void autonomous(void) {
  drive(91.27); //prepare to pick up blocks
    intakeupper.setVelocity(10, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(fwd, 676767, deg, false); //begin intake spinning
  turn(150); //turn to face blocks
  drive(98.88); //drive to pick up blocks
  wait(50, msec);
  drive(45.64); //slower drive to ensure pickup
  turn(80); //turn to back facing upper center goal
  motor_group(intakeupper, intakelower).stop();
  drive(-91.27); //prepare to score in upper center
    intakeupper.setVelocity(100, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(reverse, 676767, deg, false); //score 2 blocks into goal
  wait(1.75, sec);
  motor_group(intakeupper, intakelower).stop();
  drive(170);
  wait(50, msec);
  drive(170); //drive in between long goal and loader
  turn(135); //turn to front face the loader
  scraper.set(true); //drop scraper mechanism
  wait(0.25, sec);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(50, pct);
  motor_group(fLDrive, bLDrive, uLDrive).spinFor(fwd, 7.5, rev, false);
  motor_group(fRDrive, bRDrive, uRDrive).spinFor(fwd, 7.5, rev, false);
  
  //drive(120);
    intakeupper.setVelocity(10, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(fwd, 676767, deg, false); 
  wait(2.5, sec);
  motor_group(intakelower, intakeupper).stop();
  drive(-207);
    intakeupper.setVelocity(100, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(reverse, 676767, deg, false);

  //drive to loader
  //back up to long goal
  //score all blocks

  //test

}
void usercontrol(void) {
while (1) {
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setStopping(coast);
  
  //Drive
  int rotational = Controller.Axis3.position(pct);
  int lateral = Controller.Axis1.position(pct);

  motor_group(fLDrive, bLDrive, uLDrive).spin(fwd,(lateral)*.5 + rotational,pct);
  motor_group(fRDrive, bRDrive, uRDrive).spin(reverse,(lateral)*.5 - rotational,pct);

  //Intake
  if (Controller.ButtonL1.pressing()) {
    intakelower.spin(fwd, 100, pct);
    intakeupper.spin(fwd, 10, pct);
  }
  else if (Controller.ButtonL2.pressing()) {
    intakeupper.spin(reverse, 80, pct);
    intakelower.spin(reverse, 80, pct);
  }
  else if (Controller.ButtonR2.pressing()) {
    intakeupper.spin(reverse, 80, pct);
    intakelower.spin(fwd, 80, pct);
  }
  else {
    intakeupper.stop();
    intakelower.stop();

  }

  //Wings
  if (Controller.ButtonRight.pressing()) {
    wings.set(true);
  }
  else if (Controller.ButtonY.pressing()) {
    wings.set(false);
  }

  //Scraper
  if (Controller.ButtonDown.pressing()) {
    scraper.set(true);
  }
  else if (Controller.ButtonB.pressing()) {
    scraper.set(false);
  }
  
  wait(30, msec);

}

}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
