/*
TUNE AUTOS AT COMP BY DRAGGING ROBOT TO WHERE IT NEEDS TO BE. 

OPTIMAL VOLTAGE FOR MATCH LOADER IS 6 / 7

PICK UP BLOCKS IS 3 V

LOADER AT 3/4 V

to add special parameters, do "function(x,y, {.parameter = z});"

EX: chassis.drive_to_point(12, 12, {.max_voltage = 8});

these can be voltages (out of 12), timeout (in 1000 = 1 second), or even modifying your PID constants

  LONG GOAL SCORING
  assembly.intake_motor_lower.spin(fwd, 12, volt);
  assembly.intake_motor_upper.spin(fwd, -12, volt); 

  INTAKING
  assembly.intake_motor_lower.spin(fwd, 12, volt);
  assembly.intake_motor_upper.spin(fwd, 1.2, volt);

  MIDGOAL SCORING
  assembly.midGoal.set(true);
  assembly.intake_motor_lower.spin(fwd, 12, volt);
  assembly.intake_motor_upper.spin(fwd, 12, volt); 
  
  Don't forget to include ---assembly.midGoal.set(false);--- once the midgoal scoring action is completed


  ******ORIENTATION******
  when working with coordinates, look at the field in a way that the side you are trying to change is positioned on your left hand side. 
  EX: changing red side auto, look at the field in a way that the red side is on your left hand side.

*/