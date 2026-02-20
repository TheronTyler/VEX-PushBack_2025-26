#pragma once

#include "vex.h"

using namespace vex;

enum lift_positions : int { IDLE = 229, LOADING = 206, SCORING = 99 };

class Assembly {
public:
    Assembly(
        mik::motor intake_motor_lower,
        mik::motor intake_motor_upper,
        mik::piston midGoal,
        mik::piston scraper,
        mik::piston wing
    );
    
    void control();

    void intake_motors_control();
    void scraper_control();
    void wing_control();

    int lift_arm_position = IDLE;
    vex::task lift_task;
    
    mik::motor intake_motor_lower;
    mik::motor intake_motor_upper;
    mik::piston midGoal;
    mik::piston scraper;
    mik::piston wing;
};