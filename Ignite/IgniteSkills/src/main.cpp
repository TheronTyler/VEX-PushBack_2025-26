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
/*intakelower.setVelocity(100, pct);
intakeupper.setVelocity(100, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(reverse, 676767, rev, false);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, 0.1, sec);
scraper.set(true);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(fwd, 0.8, sec);
scraper.set(false); */
 
wings.set(true);
drive(300);
turn(267);
scraper.set(true);
wait(1, sec); //approach loader1 
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(10, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(fwd, 676767, rev, false);
drive(73);
wait(0.3, sec);
drive(-25);
wait(0.3, sec);
drive(25);
wait(0.3, sec);
drive(-25);
wait(0.3, sec);
drive(25);
wait(0.3, sec);

/*//vibe code
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(40, pct);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, 3, sec);
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(100, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(reverse, 676767, rev, false);
wait(5, sec);
scraper.set(false);
drive(150);
turn(225);
drive(160);
motor_group(fLDrive, bLDrive, uLDrive).spinFor(fwd, 0.25, sec); //park
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(20, pct);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(fwd, 1, sec);
drive(-20);
scraper.set(true);
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(10, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(fwd, 676767, rev, false);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(40, pct);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(fwd, 1.125, sec);
scraper.set(false);
*/

drive(-50);
scraper.set(false); //remove from loader 1
turn(93);
drive(90);
turn(95);
drive(365);
drive(360); //drive down corridor
turn(90);
drive(104);
turn(276);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(40, pct);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, 1, sec); //prepare to score loader 1
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(100, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(reverse, 676767, rev, false);
scraper.set(true); //prepare for loader 2
wait(4, sec); //finish scoring loader 1
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(10, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(fwd, 676767, rev, false); 
drive(175);
drive(68);
wait(0.3, sec);
drive(-20);
wait(0.3, sec);
drive(20);
wait(0.3, sec);
drive(-20);
wait(0.3, sec);
drive(20);
wait(0.3, sec);
drive(-20);
wait(0.3, sec);
drive(20);
wait(0.3, sec); //pickup loader 2
motor_group(intakelower, intakeupper).stop();
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(40, pct);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, 1.8, sec); //prepare to score loader 2
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(100, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(reverse, 676767, rev, false);
scraper.set(false);
wait(4, sec); //score loader 2
drive(75); //get off goal
turn(90); //turn towards center
motor_group(intakeupper, intakelower).stop();
drive(300);
drive(300);
drive(320);
drive(-130);
turn(273);
scraper.set(true);
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(10, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(fwd, 676767, rev, false); 
drive(162);
wait(0.3, sec);
drive(-20);
wait(0.3, sec);
drive(20);
wait(0.3, sec);
drive(-20);
wait(0.3, sec);
drive(20);
wait(0.3, sec);
drive(-20);
wait(0.3, sec);
drive(20);
drive(-50);
scraper.set(false); //remove from loader 3
turn(93);
drive(90);
turn(95);
drive(365);
drive(360); //drive down corridor
turn(90);
drive(104);
turn(276);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(40, pct);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, 1, sec); //prepare to score loader 1
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(100, pct);
intakelower.spinFor(fwd, 676767, rev, false);
intakeupper.spinFor(reverse, 676767, rev, false);
scraper.set(true); //prepare for loader 4
wait(4, sec); //finish scoring loader 3

}
void usercontrol(void) {
  
while (1) {
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setStopping(coast);
  
  //Drive
  int rotational = Controller.Axis3.position(pct);
  int lateral = Controller.Axis1.position(pct);

  motor_group(fLDrive, bLDrive, uLDrive).spin(fwd,((lateral)*0.5) + rotational,pct);
  motor_group(fRDrive, bRDrive, uRDrive).spin(reverse,((lateral)*0.5) - rotational,pct);

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
