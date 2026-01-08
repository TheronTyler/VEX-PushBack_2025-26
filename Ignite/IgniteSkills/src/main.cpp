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
wings.set(true);
drive(290);
turn(270);
scraper.set(true);
wait(0.5, sec); //approach loader1 
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(10, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(fwd, 676767, rev, false);
drive(60);
wait(0.3, sec);
drive(-20);
wait(0.3, sec);
drive(20);
wait(0.3, sec);
drive(-20);
wait(0.3, sec);
drive(20);
wait(0.3, sec);
drive(-50);
scraper.set(false); //remove from loader 1
turn(93);
drive(90);
turn(90);
drive(370);
drive(370); //drive down corridor
turn(90);
drive(110);
turn(276);
drive(-80); //prepare to score
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(100, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(reverse, 676767, rev, false);
scraper.set(true); //prepare for loader 2
wait(1.5, sec); //finish scoring 
drive(150);
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(10, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(fwd, 676767, rev, false); //pickup loader 2
drive(60);
wait(0.3, sec);
drive(-20);
wait(0.3, sec);
drive(20);
wait(0.3, sec);
drive(-20);
wait(0.3, sec);
drive(20);
wait(0.3, sec);
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
  else if (Controller.ButtonR1.pressing()) {
    midGoal.set(true);
    intakeupper.spin(reverse, 100, pct);
    intakelower.spin(fwd, 100, pct);
  }
  else {
    intakeupper.stop();
    intakelower.stop();
    midGoal.set(false);


  }

  //Wings
  if (Controller.ButtonDown.pressing()) {
    wings.set(true);
  }
  else if (Controller.ButtonB.pressing()) {
    wings.set(false);
  }

  //Scraper
  if (Controller.ButtonRight.pressing()) {
    scraper.set(true);
  }
  else if (Controller.ButtonY.pressing()) {
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
