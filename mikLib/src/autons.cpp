#include "vex.h"

using namespace vex;
using namespace mik;

void default_constants(void) {
    chassis.set_control_constants(5, 10, 1.019, 5, 10, 1.019);

    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
    chassis.set_turn_constants(12, .437, .0215, 3.686, 15);
    chassis.set_drive_constants(10, 1.5, 0, 10, 0);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_swing_constants(12, .437, .0295, 3.486, 15);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_turn_exit_conditions(1.5, 75, 2000);
    chassis.set_drive_exit_conditions(1, 75, 3000);
    chassis.set_swing_exit_conditions(1.25, 75, 3000);
}

void odom_constants(void) {
    default_constants();
    chassis.heading_max_voltage = 10;
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
    chassis.boomerang_lead = .5;
    chassis.boomerang_setback = 2;    
}

std::string template_auto(bool calibrate, auto_variation var, bool get_name) {
    /* The first variation will be this auto */
    if (var == one) {}

    /* We declare and allow a second variation of this auto; 
    You may want this if you want a different movements in the same starting configuration */
    if (var == two) { return template_auto_other_variation(calibrate, get_name); }

    if (get_name) { /* Give a desciption of your auto */ return "template auto 1 (3 objs)"; }
    if (calibrate) {
        /* Initialize robots starting position "https://path.jerryio.com/" and/or add extra movements to line up robots 
        starting position **IF MOVING DURING CALIBRATION DO BEFORE FIELD CONTROLLER PLUG IN** */
        chassis.set_coordinates(55, 23.5, 90);
    
        /* Example of turning before auto is ran */
        chassis.turn_max_voltage = 6; 
        chassis.turn_to_angle(45);

        return "";
    }
    
    /* We now run the auto */ 
    chassis.drive_distance(10);
    chassis.drive_distance(-10);

    return "";
}
std::string template_auto_other_variation(bool calibrate, bool get_name) {
    if (get_name) { return "template auto 2 (4 objs)"; }
    
    // Mirror template_auto() from the x-axis
    chassis.mirror_all_auton_y_pos();
    
    if (calibrate) {
        // Coordinates will be set to (55, -23.5) as y_pos is mirrored
        template_auto(calibrate, one, get_name);
        return "";
    }
    
    // Run auto, make sure to pass in one as var.
    template_auto(calibrate, one, get_name);

    return "";
}


std::string blue_left_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "blue left winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(-38.5, 31, 90);

        return "";
    }
odom_constants();
assembly.intake_motor_lower.spin(fwd, 12, volt);
assembly.intake_motor_upper.spin(fwd, 1.2, volt);
chassis.turn_to_point(-27.83, 20.918);
chassis.drive_to_point(-27.83, 20.918, {.max_voltage = 3});
assembly.scraper.set(true); //pick up cluster
wait(0.35, sec);
chassis.turn_to_point(-1.866, 8.316, {.angle_offset = 180, .max_voltage = 6});
assembly.intake_motor_lower.spinFor(reverse, 0.3, rev, false);
chassis.drive_to_point(-1.866, 8.316, {.timeout = 1000});//mid goal
assembly.midGoal.set(true);
assembly.intake_motor_lower.spin(fwd, 12, volt);
assembly.intake_motor_upper.spin(fwd, 12, volt);
wait(1.25, sec);
assembly.midGoal.set(false);
assembly.intake_motor_lower.spin(fwd, 12, volt);
assembly.intake_motor_upper.spin(fwd, 1.2, volt);
chassis.drive_to_point(-39.156, 45);
chassis.turn_to_angle(270);
chassis.drive_distance(20, {.timeout = 750, .max_voltage = 6.5}); //loader
wait(0.5, sec);
chassis.drive_distance(-5, {.timeout = 500});
chassis.drive_to_point(-19.617, 48.826, {.timeout = 1000});
chassis.drive_distance(2);
assembly.intake_motor_lower.spin(fwd, 12, volt);
assembly.intake_motor_upper.spin(fwd, -12, volt);
assembly.scraper.set(false);
wait(1.5, sec); //score long goal
chassis.right_swing_to_angle(90, {.turn_direction = ccw});
chassis.turn_to_angle(52);
chassis.drive_distance(20);
chassis.turn_to_angle(90);
chassis.drive_distance(3.5);
chassis.turn_to_angle(135);
    return "";
}
std::string blue_left_sawp(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "blue left sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string blue_left_elim(bool calibrate, auto_variation var, bool get_name) {   
    if (get_name) { return "blue left elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string blue_right_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "blue right winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(-39.5, -24, 90);

        return "";
    }
   
    odom_constants();
//chassis.turn_to_point(-22.401, -15.7);
assembly.wing.set(true);
assembly.intake_motor_lower.spin(fwd, 12, volt);
assembly.intake_motor_upper.spin(fwd, 1.2, volt);

chassis.drive_to_point(-22.401, -15.7, { .max_voltage = 3}); //block pickup
assembly.scraper.set(true);
chassis.turn_to_point(-44.63, -41);
chassis.drive_to_point(-44.63, -41); //loader/long goal
wait(0.3, sec);

chassis.turn_to_point(-64.5, -40);
chassis.drive_to_point(-64.5, -40, {.max_voltage = 6.5});//loader pickup
wait(0.5, sec);
//chassis.turn_to_point(-32.087, -39, {.angle_offset = 180});
chassis.drive_to_point(-32.087, -40.5); //back up into long goal
assembly.intake_motor_lower.spin(fwd, 12, volt);
assembly.intake_motor_upper.spin(fwd, -12, volt);
wait(2, sec); //score into long goal
assembly.intake_motor_lower.stop();
assembly.intake_motor_upper.stop();
assembly.scraper.set(false);
chassis.drive_distance(10);
chassis.turn_to_point(-38.9, -30.2); 
//change
//was made when uncalbrated to auto
chassis.drive_to_point(-38.9, -30.2); //change
chassis.turn_to_angle(270);
assembly.wing.set(false);
chassis.drive_to_point(-8.7, -30.5, {.max_voltage = 6}); //change



    return "";
}
std::string blue_right_sawp(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "blue right sawp"; }
    if (calibrate) {
        chassis.set_coordinates(-39.5, -24, 90);

        return "";
    }
  odom_constants();

  chassis.turn_to_point (-36.95, -39.98);
  chassis.drive_to_point(-36.95, -39.98);
  chassis.turn_to_angle(270);
  assembly.scraper.set (true);
  assembly.intake_motor_lower.spin(fwd, 12, volt);
  assembly.intake_motor_upper.spin(fwd, 1.2, volt);
  chassis.drive_to_point(-61, -38.5, {.timeout = 850, .max_voltage = 7});
  wait(0.75, sec); //match loader wait
  chassis.drive_to_point(-27.2, -38);
  assembly.intake_motor_lower.spin(fwd, 12, volt);
  assembly.intake_motor_upper.spin(fwd, -12, volt);    //spin entire intake system to score
  assembly.scraper.set(false); //scraper up
  chassis.drive_distance(2);//off goal to ease scoring
  wait(1.25, sec);
  assembly.intake_motor_upper.spin(fwd, 1.2, volt); //slow upper int. so we can intake more blocks
  chassis.left_swing_to_angle(45); //swing into three stack left of long goal
  chassis.drive_to_point(-28.1, -19.7, { .max_voltage = 6});
  assembly.scraper.set(true);
  chassis.right_swing_to_point(-17.9, -7.2); //heading = 0 for drivetopose?
  assembly.scraper.set(false); //pull scraper up after intaking three stack 
  chassis.turn_to_point(-21, 23.5);
  chassis.drive_to_point(-21, 20.5);
  chassis.drive_to_point(-21, 23.5, {.max_voltage = 6}); //drive to opp three stack
  assembly.scraper.set(true); //drop scraper
  wait(0.15, sec);
  chassis.drive_distance(6);
  chassis.turn_to_point(-4.2, 13.6, {.max_voltage = 8, .angle_offset = 180}); //turn to mid goal
  
  assembly.intake_motor_lower.spinFor(reverse, 0.75, rev, false);
  chassis.drive_to_point(-4.2, 13.6, {.timeout = 750}); //drive to mid goal
  assembly.intake_motor_upper.spinFor(reverse, 3, rev, false);
  assembly.midGoal.set(true);
  assembly.intake_motor_lower.spin(fwd, 12, volt);
  assembly.intake_motor_upper.spin(fwd, 12, volt);
  wait(0.75, sec); //score into mid goal
  assembly.midGoal.set(false);
  assembly.intake_motor_lower.spin(fwd, 12, volt);
  assembly.intake_motor_upper.spin(fwd, 1.2, volt);
  chassis.drive_to_point(-30.2, 57.3);
  chassis.turn_to_angle(270);
  chassis.drive_distance(20, {.timeout = 500, .max_voltage = 7});
  wait(0.75, sec); //match loader wait
  chassis.drive_to_point(-27.7, 51.7);
  chassis.drive_distance(2);
  assembly.intake_motor_lower.spin(fwd, 12, volt);
  assembly.intake_motor_upper.spin(fwd, -12, volt);

    return "";
}
std::string blue_right_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "blue right elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}

std::string red_left_winpoint(bool calibrate, auto_variation var, bool get_name) { 
    
    if (get_name) { return "red left winpoint"; }
    chassis.mirror_all_auton_x_pos();
    chassis.mirror_all_auton_y_pos();
    if (calibrate) {
        blue_left_winpoint(calibrate, var, get_name);
        return "";
    }
        blue_left_winpoint(calibrate, var, get_name);
    return "";
}
std::string red_left_sawp(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red left sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string red_left_elim(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red left elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        
        return "";
    }
    
    return "";
}
std::string red_right_winpoint(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red right winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        
        return "";
    }

    return "";
}
std::string red_right_sawp(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "red right sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        
        return "";
    }
    odom_constants();
    //stuff

    return "";
}
std::string red_right_elim(bool calibrate, auto_variation var, bool get_name) {   
    if (get_name) { return "red right elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}

std::string skills(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "skills"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}