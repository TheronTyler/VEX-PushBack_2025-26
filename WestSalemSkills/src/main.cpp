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
/*motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, 0.1, sec);

scraper.set(true);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(fwd, 0.8, sec);
scraper.set(false);*/
wings.set(true);
  drive(218);
  turn(259);
  scraper.set(true);
  wait(0.5, sec);
  intakeupper.setVelocity(10, pct);
  intakelower.setVelocity(100, pct);
  intakelower.spinFor(fwd, 676767, rev, false);
  intakeupper.spinFor(fwd, 676767, rev, false); //take out loader 1
  drive(79);
  wait(2, sec);
  drive(18);
  wait(2, sec);
  drive(-95); //move from loader 1
  drive(-120);
  intakeupper.setVelocity(100, pct);
  intakelower.setVelocity(100, pct);
  intakelower.spinFor(fwd, 676767, rev, false);
  intakeupper.spinFor(reverse, 676767, rev, false);
  scraper.set(false);
  wait(3, sec); //score in long goal 1
drive(50);
turn(215);
drive(210);
turn(215);
drive(50);
scraper.set(true);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(fwd, 0.8, sec);
scraper.set(false);

  /*turn(263);
  drive(-165.09);
  scraper.set(false);
  wait(0.1, sec);
  drive(35);
  turn(100); //position to corridor
  drive(-304.25);
  wait(0.1, sec);
  drive(-318.25); //drive down corridor
  turn(100);
  drive(-85);
  turn(86);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(50, pct);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, 0.25, sec);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).stop();

 //position to score in long goal 1
  intakeupper.setVelocity(100, pct);
  intakelower.setVelocity(100, pct);
  intakelower.spinFor(fwd, 676767, rev, false);
  intakeupper.spinFor(reverse, 676767, rev, false);
  wait(3, sec); //score in long goal 1
  scraper.set(true);
  intakeupper.setVelocity(10, pct);
  intakelower.setVelocity(100, pct);
  intakelower.spinFor(fwd, 676767, rev, false);
  intakeupper.spinFor(fwd, 676767, rev, false);
  drive(160);
  drive(65);
  wait(1.5, sec);
  drive(15);
  wait(1, sec); //remove from loader 2
  drive(-110);
  turn(183);
  drive(-110);
  intakeupper.setVelocity(100, pct);
  intakelower.setVelocity(100, pct);
  intakelower.spinFor(fwd, 676767, rev, false);
  intakeupper.spinFor(reverse, 676767, rev, false); //score loader 2
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setStopping(coast);
  wait(1.5, sec);
  drive(40);
  scraper.set(false);
  turn(90);
  drive(120);
  turn(110);
  wait(0.25, sec);
  drive(350);
  drive(350);
  turn(270);
  drive(20);
scraper.set(true);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(fwd, 0.8, sec);
scraper.set(false);
  
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
