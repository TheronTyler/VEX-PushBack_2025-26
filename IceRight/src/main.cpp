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
  intakeupper.setVelocity(10, pct);
  intakelower.setVelocity(100, pct);
  intakelower.spinFor(fwd, 676767, deg, false); //pickup 3 block
  intakeupper.setVelocity(10, pct);
  intakeupper.spinFor(fwd, 676767, deg, false); 
  
  drive(162.4); //drive to 3 block
  drive(80); //Cut in half to slow it down

turn(225); //turn to under long goal

  drive(170.12); //drive to under long goal and pickup block
  wait(150, msec);

  drive(-170.12); //return to 3 stack

  turn(260); //face long and loader area

drive(297.21); //drive to long and loader area

turn(228); //face front to loader

scraper.set(true);
wait(0.125, sec);
drive(85);
drive(35);
wait(0.75, sec);
intakeupper.setVelocity(10, pct);
  intakelower.spinFor(fwd, 676767, deg, false); //take out loader
  intakeupper.spinFor(fwd, 676767, deg, false); 
  //scraper.set(true);
  //drive(150);
  //drive(80.55); //drive to loader
  drive(-120);
  drive(-120);
  intakeupper.setVelocity(100, pct);
  intakelower.spinFor(fwd, 676767, deg, false);
  intakeupper.spinFor(reverse, 676767, deg, false); //score into goal


}
void usercontrol(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.drawImageFromFile("WeMisshunter.png", 0, 0);
while (1) {
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setStopping(coast);
  
  //Drive
  int lateral = Controller.Axis3.position(pct);
  int rotational = exp(Controller.Axis1.position(pct));

  motor_group(fLDrive, bLDrive, uLDrive).spin(fwd,(rotational)*.5 + lateral,pct);
  motor_group(fRDrive, bRDrive, uRDrive).spin(reverse,(rotational)*.5 - lateral,pct);

  //Intake
  if (Controller.ButtonL1.pressing()) {
    intakelower.spin(fwd, 100, pct);
    intakeupper.spin(fwd, 10, pct);
  }
  else if (Controller.ButtonL2.pressing()) {
    \
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
