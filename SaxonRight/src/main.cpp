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
#include "sort.h"
#include "vex.h"

//#include "turnHeading.h"

using namespace vex;

// A global instance of competition
void pre_auton(void) {
sense.calibrate();
Brain.Screen.drawImageFromFile("aleiaWeiner.png", 0, 0);





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
  turn(210); //turn to face blocks
  drive(90.88); //drive to pick up blocks
  wait(50, msec);
  drive(40.64); 
  turn(193);
  drive(132.55);
  drive(70);
  wait(0.5, sec);
  drive(-202.55);
  turn(240);
  drive(240.63);
  wait(0.25, sec);
  turn(240);
  drive(-120);
  intakeupper.setVelocity(100, pct);
  intakelower.setVelocity(100, pct);
  intakelower.spinFor(fwd, 676767, deg, false);
  intakeupper.spinFor(reverse, 676767, deg, false);
  wait(1.25, sec);
  motor_group(intakeupper, intakelower).stop();
  scraper.set(true);
  drive(167.76);
    intakeupper.setVelocity(10, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(fwd, 676767, deg, false); 
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(30, pct);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(fwd, .6, sec);
  wait(.05, sec);
    motor_group(fLDrive, bLDrive, uLDrive).spinFor(reverse, .025, rev, false);
    motor_group(fRDrive, bRDrive, uRDrive).spinFor(reverse, .025, rev);
    motor_group(fLDrive, bLDrive, uLDrive).spinFor(fwd, .025, rev, false);
    motor_group(fRDrive, bRDrive, uRDrive).spinFor(fwd, .025, rev);
    wait(0.1, sec);
    turn(182);
    drive(-210.76);
  intakeupper.setVelocity(100, pct);
  intakelower.setVelocity(100, pct);
  intakelower.spinFor(fwd, 676767, deg, false);
  intakeupper.spinFor(reverse, 676767, deg, false);


  //slower drive to ensure pickup
   //turn to face under goal blocks
   //drive into blocks and pick up
   //drive back
   //turn towards long goal and loader
   //drive to between long goal and loader
   //turn to face loader
   //drop scraper
   //drive into loader
   //back into goal
   //score goal
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
    intakeupper.spin(fwd, 100, pct);
    intakelower.spin(reverse, 100, pct);
  }
  else if (Controller.ButtonR2.pressing()) {
    intakeupper.spin(reverse, 100, pct);
    intakelower.spin(fwd, 100, pct);
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
