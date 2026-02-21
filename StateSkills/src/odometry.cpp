#include "vex.h"
#include <cmath>

using namespace vex;

// ========== ODOMETRY CONSTANTS ==========
// Drive wheel diameter in inches
const double DRIVE_WHEEL_DIAMETER = 3.25; // inches

// Horizontal tracking wheel diameter in inches
const double HORIZONTAL_WHEEL_DIAMETER = 2.0; // inches

// Distance from tracking center to horizontal wheel (inches)
// Positive if wheel is to the right of center, negative if left
const double HORIZONTAL_OFFSET = 3; // inches

// Drive motor gear ratio (adjust based on your cartridge)
// Blue cartridge = 6:1 (0.167), then external gearing 36:48 = 0.75
// Combined ratio = 6:1 × 36:48 = 6:1 × 0.75 = 4.5:1 total
// Ratio value = 1 / (6 × 0.75) = 1 / 4.5 = 0.222
const double DRIVE_GEAR_RATIO = 0.222; // Blue cartridge with 36:48 external gearing

// Rotation sensor degrees per revolution
const double ROTATION_DEGREES_PER_REV = 360.0;

// Motor encoder degrees per revolution
const double MOTOR_DEGREES_PER_REV = 360.0;

// Convert drive motor degrees to inches
const double DRIVE_INCH_PER_DEGREE = (M_PI * DRIVE_WHEEL_DIAMETER * DRIVE_GEAR_RATIO) / MOTOR_DEGREES_PER_REV;

// Convert horizontal rotation sensor degrees to inches
const double HORIZONTAL_INCH_PER_DEGREE = (M_PI * HORIZONTAL_WHEEL_DIAMETER) / ROTATION_DEGREES_PER_REV;

// ========== DISTANCE SENSOR CALIBRATION ==========
// Distance from right distance sensor to right edge of robot (inches)
const double RIGHT_SENSOR_OFFSET = 3.0; // inches

// Distance from back distance sensor to back edge of robot (inches)
const double BACK_SENSOR_OFFSET = 3.0; // inches

// Field dimensions (inches) - standard VEX field is 144" x 144"
const double FIELD_WIDTH = 144.0; // inches
const double FIELD_LENGTH = 144.0; // inches

// Distance sensor position reset thresholds
const double DISTANCE_RESET_THRESHOLD = 18.0; // Only reset if within 18
const double 