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
  drive(91.27);
    intakeupper.setVelocity(10, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(fwd, 676767, deg, false);
  turn(150);
  drive(98.88);
  wait(50, msec);
  drive(45.64);
  turn(75);
  motor_group(intakeupper, intakelower).stop();
  drive(-91.27);
    intakeupper.setVelocity(100, pct);
    intakelower.setVelocity(100, pct);
    intakelower.spinFor(fwd, 676767, deg, false);
    intakeupper.spinFor(reverse, 676767, deg, false);
  wait(1.75, sec);
  motor_group(intakeupper, intakelower).stop();
  drive(357.49);
  turn(135);
  //test


  /*intakeupper.setVelocity(15, pct);
  intakelower.setVelocity(100, pct);
  intakelower.spinTo(25000, degrees, false);
  intakeupper.spinTo(250, degrees, false);

 motor_group(fRDrive, bRDrive, uRDrive).spinFor(300, degrees, false);
 motor_group(fLDrive, bLDrive, uLDrive).spinFor(300, degrees, false);
 wait(2, sec);
 motor_group(fRDrive, bRDrive, uRDrive).spinFor(-40, degrees, false);
 motor_group(fLDrive, bLDrive, uLDrive).spinFor(40, degrees, false);
 wait(0.75, sec);
 motor_group(fRDrive, bRDrive, uRDrive).spinFor(80, degrees, false);
 motor_group(fLDrive, bLDrive, uLDrive).spinFor(80, degrees, false);
 wait(0.85, sec);
 motor_group(fRDrive, bRDrive, uRDrive).spinFor(-180, degrees, false);
 motor_group(fLDrive, bLDrive, uLDrive).spinFor(-180, degrees, false);
 wait(0.75, sec);
 motor_group(fRDrive, bRDrive, uRDrive).spinFor(-65, degrees, false);
 motor_group(fLDrive, bLDrive, uLDrive).spinFor(65, degrees, false);
 wait(0.5, sec);
 motor_group(fRDrive, bRDrive, uRDrive).spinFor(270, degrees, false);
 motor_group(fLDrive, bLDrive, uLDrive).spinFor(270, degrees, false);
 wait(1.3, sec);
 motor_group(fRDrive, bRDrive, uRDrive).spinFor(-45, degrees, false);
 motor_group(fLDrive, bLDrive, uLDrive).spinFor(45, degrees, false);
 wait(1, sec);
 motor_group(fRDrive, bRDrive, uRDrive).spinFor(-160, degrees, false);
 motor_group(fLDrive, bLDrive, uLDrive).spinFor(-160, degrees, false);
 wait(0.2, sec);
 intakeupper.setVelocity(100, pct);
 intakelower.spinTo(250000, degrees, false);
intakeupper.spinTo(-250000, degrees, false);
*/
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
