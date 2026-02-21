#include "vex.h"

using namespace vex;

// Pass in the devices we want to use
Assembly::Assembly(
    mik::motor intake_motor_lower,
    mik::motor intake_motor_upper,
    mik::piston midGoal,
    mik::piston scraper,
    mik::piston wing
) :
    // Assign the ports to the devices
    intake_motor_lower(intake_motor_lower),
    intake_motor_upper(intake_motor_upper),
    midGoal(midGoal),
    scraper(scraper),
    wing(wing)
    //long_piston(long_piston) // Make sure when using a 3 wire device that isnt mik::piston you convert the port. `to_triport(PORT_A)`.
{};

// You want to put this function inside the user control loop in main.
void Assembly::control() {
  Assembly::intake_motors_control();
  Assembly::scraper_control();
  Assembly::wing_control();


}


void Assembly::intake_motors_control() {
    if (Controller.ButtonL1.pressing()) {
    intake_motor_lower.spin(fwd, 100, pct);
    intake_motor_upper.spin(fwd, 10, pct);
  }
  else if (Controller.ButtonL2.pressing()) {
    intake_motor_upper.spin(fwd, 100, pct);
    intake_motor_lower.spin(reverse, 100, pct);
  }
  else if (Controller.ButtonR2.pressing()) {
    intake_motor_upper.spin(reverse, 100, pct);
    intake_motor_lower.spin(fwd, 100, pct);
  }
  else if (Controller.ButtonR1.pressing()) {
    midGoal.set(true);
    intake_motor_upper.spin(fwd, 100, pct);
    intake_motor_lower.spin(fwd, 100, pct);
  }
  else {
    intake_motor_upper.stop();
    intake_motor_lower.stop();
    midGoal.set(false);
}
}


    void Assembly::scraper_control() {
if (btnRight_new_press(Controller.ButtonRight.pressing())) {
  scraper.toggle();
    }
  }

    void Assembly::wing_control() {
  if (btnDown_new_press(Controller.ButtonDown.pressing())) {
     wing.toggle();
      }
    }


// Extends or retracts piston when button A is pressed, can only extend or retract again until button A is released and pressed again
