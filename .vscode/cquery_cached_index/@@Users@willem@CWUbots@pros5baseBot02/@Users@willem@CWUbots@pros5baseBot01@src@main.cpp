#include "main.h"
#include "portdef.hpp"		// portdef.hpp defines all the ports by name we use on the V5 brain
													// using a portdef.hpp file, and using the definitions set in their
													// as the parameters when we need to specify a port in our code,
													// allows us very quickly to move things around and gives us one
													// place to look for all the ports and their assigned functions

#include "globals.hpp"		// ensure access to all global functions and variables
													// this goes hand in hand with globals.cpp

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// While technicaly not needed it is a good practice to intialize the motors
	// and sensors during the intialization face of the program
	// We are using the green cartridge here - if they are changed the MOTOR_GEARSET
	// needs to be subsequently adjusted
	//             red    - 100RPM max  (MOTOR_GEARSET_36)
	//             green  - 200RPM      (MOTOR_GEARSET_18)
	//             blue   - 600RPM      (MOTOR_GEARSET_6)
	// Also notice the right_whell motor has the direction reversed, so in this case
	// if we give a command to move forward, the left motor runs clockwise and the
	// right motor counter clockwise - moving the robot forward.

	// gearset is set to the RED cartridge - you may need to change back to default of green
	// by changing MOTOR_GEARSET_36 to MOTOR_GEARSET_18
	pros::Motor left_wheel (LEFT_MOTOR_PORT, MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor right_wheel (RIGHT_MOTOR_PORT, MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  motorMaxSpeed = 25;			// Lets set the max speed of movement, remember it is
													// a global variable see globals.cpp/globals.hpp


	// Now lets move the robot forward for a bit.  We use relative movement here, so we
	// move encoder unit increments no matter what are current encoder count is, as
	// we specified E_MOTOR_ENCODER_DEGREES in motor setup we will rotate the motor 1000 degrees
	// See here for more detail: https://pros.cs.purdue.edu/v5/api/cpp/motors.html#move-relative

  // We should ensure that the eoncoders start at 0, this makes it easier to visualize and ensure
	// motors move for the given requested distance
	left_wheel.tare_position();       // ensure encoders are reset before
	right_wheel.tare_position();      // movement.

	right_wheel.move_relative(1000, motorMaxSpeed);		// Move forward for 1000 encoder units
  left_wheel.move_relative(1000, motorMaxSpeed);
	// Important to understnad - we need to let the motor run it's course and ensure that it gets within
	// +-5  if we do not do that it would randomly either directly move on to the next movement or
	// never execute what comes next, as it will NEVER precisely reach the requested encoder units
	while (!((left_wheel.get_position() < 1005) && (left_wheel.get_position() > 995))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
	// Lets print out the encoder values after the movement is completed, notice that it will have a
	// value whihc is within +-5 units of request, likely slight below the requested vaule
	// To view this output ensure hte V5 is connected via USB cable to your computer
	// and open the Consoel Terminal (menu PROS -> Open Terminal)
  std::cout << "After forward: Encoder left: " << left_wheel.get_position() << "\n";

	// lets make a turn to the left, meaning we are only going to spin the left motor
	left_wheel.tare_position();       // ensure encoders are reset before
	right_wheel.tare_position();      // movement.

  // let set a new motorMaxSpeed and lets check if it is allowed, if not we set it to the
	// maximum allowable speed.
	motorMaxSpeed = 300;
	if(motorMaxSpeed > maxAllowedSpeed) {
		// Oops we are exceeding maximum value.....
		motorMaxSpeed = maxAllowedSpeed;							// setting to the max maxAllowedSpeed
	}
	// for fun lets print what the speed is
	std::cout << "Motospeed is set to: " << motorMaxSpeed << "\n";

	left_wheel.move_relative(1000, motorMaxSpeed);
	while (!((left_wheel.get_position() < 1005) && (left_wheel.get_position() > 995))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  std::cout << "After turn: Encoder left: " << left_wheel.get_position() << "\n";

	// Lest drive backwards for a movement, we are going to give it negative encoder counts
	// This also means our while wait loop needs to change to reflect in thsi case -1005 and -995
	// and the > and < signs flip!

  // Lets set out speed to the default
	motorMaxSpeed = motorDefaultSpeed;									// comes from gloabls.cpp

	// for fun lets print what the speed is
	std::cout << "Motospeed is set to: " << motorMaxSpeed << "\n";

	left_wheel.tare_position();       // ensure encoders are reset before
	right_wheel.tare_position();      // movement.

	right_wheel.move_relative(-1000, motorMaxSpeed);		// Move forward for 1000 encoder units
  left_wheel.move_relative(-1000, motorMaxSpeed);

	while (!((left_wheel.get_position() > -1005) && (left_wheel.get_position() < -995))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  std::cout << "After drive Backwards: Encoder left: " << left_wheel.get_position() << "\n";

	// We could ensure that robot is completely stopped by issuing the following commands to the motors:
	left_wheel.move_velocity(0);
	right_wheel.move_velocity(0);
}
