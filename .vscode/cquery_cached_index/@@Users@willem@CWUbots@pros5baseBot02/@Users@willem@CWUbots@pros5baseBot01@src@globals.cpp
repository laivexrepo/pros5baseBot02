// ------- globals.cpp ---------------------------------------------------------
//
// Use globals.cpp together with globals.hpp to define all motor and other objects
// which should be available/accessible in autonomous and opcontrol code.
//
// for example setup a motor definition and then add a extern pros::motor to
// globals.hpp to ensure all other modules have access -- of course by including
// #include "globals.hpp" in the relevant source (.cpp) files

#include "globals.hpp"
#include "portdef.hpp"
#include "main.h"

// declare the motor objects we are using - see initialize section for more
// details see the initialize() function in main.cpp
// gearset is set to the RED cartridge - you may need to change back to default of green
// by changing MOTOR_GEARSET_36 to MOTOR_GEARSET_18
pros::Motor left_wheel (LEFT_MOTOR_PORT, MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor right_wheel (RIGHT_MOTOR_PORT, MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);

int motorMaxSpeed = 50;            // Maximum movement speed
const int motorDefaultSpeed = 75;  // our default movement speed
const int maxAllowedSpeed = 100;   // a constant maximum allowed speed
