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

//#include "turnHeading.h"

using namespace vex;

// A global instance of competition
void pre_auton(void) {
sense.calibrate();
Brain.Screen.drawImageFromFile("Theron.png", 0, 0);
Brain.Screen.drawImageFromFile("happyTheron.png", 101, 0);
Brain.Screen.drawImageFromFile("TheronSplits.png", 222, 0);

//Speed
motor_group(intakeupper, intakelower).setVelocity(95,pct);


//Stopping
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setStopping(coast);
motor_group(intakeupper, intakelower).setStopping(brake);

}

void autonomous(void) {
  //turn(170); //Turn to 3 block
  intakelower.setVelocity(100,pct);
  intakeupper.setVelocity(10,pct);
  intakelower.spinFor(fwd, 676767, deg, false); //pickup 3 block
  intakeupper.spinFor(fwd, 676767, deg, false); 
  
  drive(162.4); //drive to 3 block
  drive(100); //Cut in half to slow it down

  turn(133); //turn to under long goal

  drive(157.12); //drive to under long goal and pickup block
  wait(150, msec);

  drive(-150.93); //backup and align with middle goal
  turn(107);
  wait(10, msec);

  intakelower.stop();
  intakeupper.stop();

  drive(-105.29); //reverse to middle goal
  wait(10, msec);

  intakeupper.setVelocity(100,pct);
  intakelower.spinFor(fwd, 676767, deg, false); //score 3 block into upper middle goal
  intakeupper.spinFor(reverse, 676767, deg, false); 
  wait(750, msec);

  intakelower.stop();
  intakeupper.stop();

  drive(349.89); //drive in-line with match loader

  turn(127); //turn to match loader

  scraper.set(true); //drop scraper mechanism
  wait(250, msec);

  intakeupper.setVelocity(10,pct);
  intakelower.spinFor(fwd, 676767, deg, false); //pickup matchload blocks
  intakeupper.spinFor(fwd, 676767, deg, false);

  drive(85); //ram matchloader
  drive(65); 


  wait(750, msec); //collect matchloader blocks

  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(55, pct);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, .6, sec);
  //drive(-235); //back up to long goal
  
  intakeupper.setVelocity(100,pct);
  intakelower.spinFor(fwd, 676767, deg, false); //score matchloader blocks into long goal
  intakeupper.spinFor(reverse, 676767, deg, false); 


  /*drive(91.27); //prepare to pick up blocks
    intakeupper.setVelocity(10, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(fwd, 676767, deg, false); //begin intake spinning
  turn(150); //turn to face blocks
  drive(95.88); //drive to pick up blocks
  wait(50, msec);
  drive(50.64); //slower drive to ensure pickup
  turn(80); //turn to back facing upper center goal
  motor_group(intakeupper, intakelower).stop();
  drive(-106.27); //prepare to score in upper center
    intakeupper.setVelocity(100, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(reverse, 676767, deg, false); //score 2 blocks into goal
  wait(1.25, sec);
  motor_group(intakeupper, intakelower).stop();
  drive(182);
  wait(50, msec);
  drive(179); //drive in between long goal and loader
  turn(135); //turn to front face the loader
  scraper.set(true); //drop scraper mechanism
  wait(0.25, sec);
    intakeupper.setVelocity(10, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(fwd, 676767, deg, false); 
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(30, pct);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(fwd, .65, sec);
  wait(.05, sec);
    motor_group(fLDrive, bLDrive, uLDrive).spinFor(reverse, .025, rev, false);
    motor_group(fRDrive, bRDrive, uRDrive).spinFor(reverse, .025, rev);
    motor_group(fLDrive, bLDrive, uLDrive).spinFor(fwd, .025, rev, false);
    motor_group(fRDrive, bRDrive, uRDrive).spinFor(fwd, .025, rev);
  //drive(120);

  wait(.575, sec);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).stop();
  wait(1, sec);
  motor_group(intakelower, intakeupper).stop();
  drive(-207);
    intakeupper.setVelocity(100, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(reverse, 676767, deg, false);
  thread threadRunning(sort);
  //drive to loader
  //back up to long goal
  //score all blocks

  //test
*/
}
void usercontrol(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.drawImageFromFile("WeMisshunter.png", 0, 0);
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
