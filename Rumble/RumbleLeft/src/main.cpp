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
  intakelower.setVelocity(100, pct);
  intakeupper.setVelocity(10, pct);
  intakelower.spinFor(fwd, 676767, rev, false);
  intakeupper.spinFor(fwd, 676767, rev, false);
  drive(180);
  drive(55); //intake cluster
  turn(58);
  intakelower.spinFor(reverse, 0.04, rev, false);
  //drive(-167);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(25, pct);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, 0.9, sec);
  midGoal.set(true);
  intakelower.setVelocity(100, pct);
  intakeupper.setVelocity(100, pct);
  intakeupper.spinFor(fwd, 676767, rev, false);
  intakelower.spinFor(fwd, 676767, rev, false);
wait(0.85, sec); //score midgoal
motor_group(intakeupper, intakelower).stop();
wait(0.05, sec);
midGoal.set(false);
drive(350); //loader and long goal 
turn(195);
drive(70); //realign
turn(121);
wait(0.25, sec);//drive to long
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(40, pct);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, 1.15, sec);
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(100, pct);
intakeupper.spinFor(reverse, 676767, rev, false);
intakelower.spinFor(fwd, 676767, rev, false); //score into long goal
scraper.set(true);
wait(0.75, sec);
motor_group(intakeupper, intakelower).stop();
intakelower.setVelocity(100, pct);
  intakeupper.setVelocity(10, pct);
  intakelower.spinFor(fwd, 676767, rev, false);
  intakeupper.spinFor(fwd, 676767, rev, false);
drive(125);
drive(110);
drive(-10);
drive(15);//take out loader
wait(0.1, sec);
drive(-15);
drive(15);
wait(0.1, sec);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setVelocity(60, pct);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spinFor(reverse, 1.2, sec);
intakelower.setVelocity(100, pct);
intakeupper.setVelocity(100, pct);
intakeupper.spinFor(reverse, 676767, rev, false);
intakelower.spinFor(fwd, 676767, rev, false);
scraper.set(false);//done

 

    /*wings.set(true);
  intakelower.setVelocity(100, pct);
  intakeupper.setVelocity(10, pct);
  intakelower.spinFor(fwd, 676767, rev, false);
  intakeupper.spinFor(fwd, 676767, rev, false); //intake
  drive(155); //hit 3 cluster
  scraper.set(true); 
  drive(80);
  turn(60); //turn to mid goal
  intakelower.spinFor(reverse, .2, rev, false);
  drive(-80);
  drive(-80);
  drive(10);
  midGoal.set(true);
  intakeupper.spinFor(reverse, 676767, rev, false);
  intakelower.spinFor(fwd, 676767, rev, false);
  wait(1, sec);
  midGoal.set(false);
  intakelower.setVelocity(100, pct);
  intakeupper.setVelocity(10, pct);
  intakelower.spinFor(fwd, 676767, rev, false);
  intakeupper.spinFor(fwd, 676767, rev, false);
  drive(248); //drive to loader/long goal
  wait(0.01, sec);
  drive(180);
  turn(137); //turn to loader
  drive(80);
  drive(32);
  wait(0.3, sec);
  drive(-15);
  drive(15); //retrieve from loader
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spin(reverse, 50, pct);
wait(1.3, sec);
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).stop();
  intakelower.setVelocity(100, pct);
  intakeupper.setVelocity(100, pct);
  intakeupper.spinFor(reverse, 676767, rev, false);
  intakelower.spinFor(fwd, 676767, rev, false);
  scraper.set(false);
  drive(25);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).spin(reverse, 100, pct);
  wait(0.2, sec);
  motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).stop(); */





}
void usercontrol(void) {
  
while (1) {
motor_group(fLDrive, bLDrive, uLDrive, fRDrive, bRDrive, uRDrive).setStopping(coast);

  //Drive
  int rotational = Controller.Axis3.position(pct);
  int lateral = Controller.Axis1.position(pct);

  motor_group(fLDrive, bLDrive, uLDrive).spin(fwd,(lateral) + rotational,pct);
  motor_group(fRDrive, bRDrive, uRDrive).spin(reverse,(lateral) - rotational,pct);

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
    intakeupper.spin(fwd, 100, pct);
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
