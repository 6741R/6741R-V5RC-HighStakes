// Include headers for the inherited classes
#include "main.h"
#include "Brain_UI.h"
#include "Robot.h"
#include "Autonomous_Manager.h"
#include "Robot_Config.h"
#include <thread>


using namespace pros;

// Global objects

/*** @brief Global configuration object for the robot's devices. */
Robot_Config robotDevices;

/*** @brief Global robot object, contains input and output 
 * functionality for all of the robot's subcomponents.*/
Robot robot;

/*** @brief Manages autonomous routines, initialized with
 * the global robot object.*/
Autonomous_Manager autonManager(robot);

/*** @brief Manages the robot's UI display and user interactions. */
Brain_UI ui;

/*** @brief Represents the master controller used to operate the robot. */
Controller master(pros::E_CONTROLLER_MASTER);




/**
 * @brief Runs when robot is disabled by VEX Field Controller.
 */
void disabled() {
	// Placeholder
}

/**
 * @brief Runs when initialized by VEX Field Controller.
 */
void competition_initialize() {

	robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	robotDevices.liftMotor.tare_position();

	    // Calibrate sensors
    robotDevices.chassis.calibrate(); // calibrate sensors
    while (robotDevices.imu.is_calibrating()) {
        pros::delay(10);
    }
	//master.print(0,0, "1");
    // Calibrate sensors
   /* robotDevices.chassis.calibrate(); // calibrate sensors
    while (robotDevices.imu.is_calibrating()) {
        pros::delay(10);
    }*/
	// Draws autonomous selector UI on the Brain using LVGL,
	// an industry standard micro-controller screen UI library.
	ui.DisplayAutonSelectorUI();
}

/*** @brief Load paths. */
ASSET(BlueRightStep1_txt);
ASSET(BlueRightStep2_txt);
ASSET(BlueRightStep3_txt);
ASSET(BlueRightStep4_txt);
ASSET(BlueRightStep5_txt);
ASSET(BlueRightStep6_txt);
ASSET(BlueRightStep7_txt);

ASSET(BlueLeftStep1_txt);
ASSET(BlueLeftStep2_txt);
ASSET(BlueLeftStep3_txt);
ASSET(BlueLeftStep4_txt);
ASSET(BlueLeftStep5_txt);
ASSET(BlueLeftStep6_txt);

ASSET(RedRightStep1_txt);
ASSET(RedRightStep2_txt);
ASSET(RedRightStep3_txt);
ASSET(RedRightStep4_txt);
ASSET(RedRightStep5_txt);
ASSET(RedRightStep6_txt);

ASSET(RedLeftStep1_txt);
ASSET(RedLeftStep2_txt);
ASSET(RedLeftStep3_txt);
ASSET(RedLeftStep4_txt);
ASSET(RedLeftStep5_txt);
ASSET(RedLeftStep6_txt);
ASSET(RedLeftStep7_txt);



ASSET(SkillsStep1_txt);
ASSET(SkillsStep2_txt);

ASSET(SkillsStep3_txt);
ASSET(SkillsStep4_txt);
ASSET(SkillsStep5_txt);
ASSET(SkillsStep6_txt);
ASSET(SkillsStep7_txt);
ASSET(SkillsStep8_txt);

ASSET(SkillsStep9_txt);
ASSET(SkillsStep10_txt);
ASSET(SkillsStep11_txt);
ASSET(SkillsStep12_txt);
ASSET(SkillsStep13_txt);
ASSET(SkillsStep14_txt);
ASSET(SkillsStep15_txt);
ASSET(SkillsStep16_txt);
ASSET(SkillsStep17_txt);



















/**
 * @brief Runs Autonomous period functions.
 */
void autonomous() {
	
// Retrieve the selected autonomous mode from the BrainUI.
	int selectedMode = ui.selectedAuton;
	//selectedMode = 3;
	// Blue Right - 0
	// Blue Left - 1
	// Red left - 2
	// Red Right - 3

	// Determine which autonomous routine to execute based on the selected mode.
	switch(selectedMode) {
		case 0:
			// Executes the autonomous routine for the Blue Alliance, Right side.
			// Set initial position
			robotDevices.chassis.setPose(52, 23, 90);
			robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

			// Move arm back 
			c::motor_move(12, 127);
			delay(50);
			c::motor_move(12, 0);

			// Ready clamp
			robotDevices.mogoClampPiston.set_value(true);

			// Approach goal
			robotDevices.chassis.follow(BlueRightStep1_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();

			// Clamp goal
			robotDevices.mogoClampPiston.set_value(false);
			delay(250);

			// Face stack of rings
			robotDevices.chassis.turnToHeading(359, 750);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(24, 24, 359);

			// Turn on intake
			c::motor_move(3, 127);
			c::motor_move(13, 127);

			// Intake stack of rings
			robotDevices.chassis.follow(BlueRightStep2_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();

			// Face group of 4 rings
			robotDevices.chassis.turnToHeading(289, 750);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(24, 46, 289);

			// Intake first ring from group of 4
			robotDevices.chassis.follow(BlueRightStep3_txt, 15, 1500, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(8.5, 51, 279);

			// Back up
			robotDevices.chassis.follow(BlueRightStep4_txt, 15, 10000, false);
			robotDevices.chassis.setPose(24, 47, 279);

			// Face second ring from group of 4
			robotDevices.chassis.turnToHeading(260, 750);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(31, 46, 260);

			// Intake second ring from group of 4
			robotDevices.chassis.follow(BlueRightStep5_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			delay(500);
			robotDevices.chassis.setPose(18, 42, 245);

			// Face ladder
			//robotDevices.chassis.turnToHeading(160, 1000);
			//robotDevices.chassis.waitUntilDone();
			//delay(500);
			//robotDevices.chassis.setPose(6.9, 42.8, 160);

			// Touch ladder for WP
			//robotDevices.chassis.follow(BlueRightStep7_txt, 15, 10000, true);
			//robotDevices.chassis.waitUntilDone();
			//delay(500);
			//c::motor_move(3, 0);
			//c::motor_move(13, 0);
			break;

		case 1:
			// Executes the autonomous routine for the Blue Alliance, Left side.
			// Set initial position
			robotDevices.chassis.setPose(59, -12, 180);
			robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

			// Move arm back 
			c::motor_move(12, 127);
			delay(50);
			c::motor_move(12, 0);

			// Align with alliance stake
			robotDevices.chassis.follow(BlueLeftStep1_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();

			// Point torwards alliance stake
			robotDevices.chassis.turnToHeading(265, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(59, -3.75, 280);

			// Approach alliance stake and score
			robotDevices.chassis.follow(BlueLeftStep2_txt, 6, 1000, false);
			robotDevices.chassis.waitUntilDone();
			c::motor_move(3, 127);
			c::motor_move(13, 127);
			delay(500);
			c::motor_move(3, 0);
			c::motor_move(13, 0);
			robotDevices.chassis.setPose(69, -3.75, 270);

			// Back away from alliance stake
			robotDevices.chassis.follow(BlueLeftStep3_txt, 6, 1000, true);
			robotDevices.chassis.waitUntilDone();

			// Face mobile goal
			robotDevices.chassis.turnToHeading(43, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.mogoClampPiston.set_value(true);
			robotDevices.chassis.setPose(69, -3.75, 43);

			// Approach mobile goal and clamp
			robotDevices.chassis.follow(BlueLeftStep4_txt, 15, 2000, false);
			robotDevices.chassis.waitUntilDone();
			delay(250);
			robotDevices.mogoClampPiston.set_value(false);
			delay(400);

			// Face stack of rings
			robotDevices.chassis.turnToHeading(160, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(45.491, -28, 160);

			// Intake stack of rings
			c::motor_move(3, 127);
			c::motor_move(13, 127);
			robotDevices.chassis.follow(BlueLeftStep5_txt, 15, 1000, true);
			robotDevices.chassis.waitUntilDone();
			delay(500);
			robotDevices.chassis.setPose(49, -43, 160);

			// Touch ladder for WP
			robotDevices.chassis.follow(BlueLeftStep6_txt, 15, 1750, false);

			break;
		case 2:
			// Executes the autonomous routine for the Red Alliance, Left side.
			// Set initial position
			robotDevices.chassis.setPose(-52, 23, -90);
			robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

			// Move arm back 
			c::motor_move(12, 127);
			delay(50);
			c::motor_move(12, 0);

			// Approach goal and clamp
			robotDevices.mogoClampPiston.set_value(true);
			robotDevices.chassis.follow(RedLeftStep1_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();
			robotDevices.mogoClampPiston.set_value(false);
			delay(250);

			// Face stack of rings
			robotDevices.chassis.turnToHeading(-359, 750);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(-24, 24, -359);

			// Intake stack of rings
			c::motor_move(3, 127);
			c::motor_move(13, 127);
			robotDevices.chassis.follow(RedLeftStep2_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();

			// Face group of 4 rings
			robotDevices.chassis.turnToHeading(70, 750);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(-24, 46, 70);

			// Intake first ring of group of 4
			robotDevices.chassis.follow(RedLeftStep3_txt, 15, 1500, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(-8.5, 51, -279);
			
			// Back up
			robotDevices.chassis.follow(RedLeftStep4_txt, 15, 10000, false);
			robotDevices.chassis.setPose(-24, 47, -279);

			// Face second ring of group of 4 and intake it
			robotDevices.chassis.turnToHeading(-245, 750);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(-31, 46, -245);
			robotDevices.chassis.follow(RedLeftStep5_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			delay(500);
			robotDevices.chassis.setPose(-18, 42, -245);

			// Face ladder for WP
			robotDevices.chassis.turnToHeading(200, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(-7.5, 40.5, 200);

			// Touch ladder for WP
			robotDevices.chassis.follow(RedLeftStep7_txt, 15, 10000, true);
			break;
		case 3:
			// Executes the autonomous routine for the Red Alliance, Right side.

			// Set initial position
			robotDevices.chassis.setPose(-59, -12, -180);
			robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

			// Move arm back
			c::motor_move(12, 127);
			delay(50);
			c::motor_move(12, 0);

			// Align with alliance stake
			robotDevices.chassis.follow(RedRightStep1_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();

			// Face alliance stake
			robotDevices.chassis.turnToHeading(90, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(-59, -3.75, 90);

			// Approach alliance stake and score
			robotDevices.chassis.follow(RedRightStep2_txt, 6, 1000, false);
			robotDevices.chassis.waitUntilDone();
			c::motor_move(3, 127);
			c::motor_move(13, 127);
			delay(500);
			c::motor_move(3, 0);
			c::motor_move(13, 0);
			robotDevices.chassis.setPose(-69, -3.75, -270);

			// Back away from alliance stake
			robotDevices.chassis.follow(RedRightStep3_txt, 6, 1000, true);
			robotDevices.chassis.waitUntilDone();

			// Face mobile goal
			robotDevices.chassis.turnToHeading(-43, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.mogoClampPiston.set_value(true);
			robotDevices.chassis.setPose(-69, -3.75, -43);

			// Approach mobile goal and clamp
			robotDevices.chassis.follow(RedRightStep4_txt, 15, 1000, false);
			robotDevices.chassis.waitUntilDone();
			delay(400);
			robotDevices.mogoClampPiston.set_value(false);
			delay(400);

			// Face stack of rings
			robotDevices.chassis.turnToHeading(175, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(-45.491, -28, 175);

			// Intake stack of rings
			c::motor_move(3, 127);
			c::motor_move(13, 127);
			robotDevices.chassis.follow(RedRightStep5_txt, 15, 1000, true);
			robotDevices.chassis.waitUntilDone();
			delay(500);
			robotDevices.chassis.setPose(-49, -43, -160);

			// Touch ladder for WP
			robotDevices.chassis.follow(RedRightStep6_txt, 15, 2000, false);

			c::motor_move(12, -127);
			break;
		case 4:
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			c::motor_move(12, 127);
			delay(50);
			c::motor_move(12, 0);
			// Executes the skills autonomous routine by default
			robotDevices.chassis.setPose(-62, 0, 90);
			c::motor_move(3, 127);
			c::motor_move(13, 127);

			delay(300);
			c::motor_move(3, 0);
			c::motor_move(13, 0);

			delay(150);
			robotDevices.chassis.turnToHeading(350, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.mogoClampPiston.set_value(true);
			robotDevices.chassis.follow(SkillsStep1_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();

			delay(200);
			robotDevices.mogoClampPiston.set_value(false);
			delay(250);

			robotDevices.chassis.turnToHeading(120, 1000);
			robotDevices.chassis.waitUntilDone();
  			c::motor_move(3, 127);
			c::motor_move(13, 127);
			robotDevices.chassis.setPose(-50, -18, 120);

			robotDevices.chassis.follow(SkillsStep2_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.turnToHeading(260, 1000);
			robotDevices.chassis.waitUntilDone();
						// Move arm back
			c::motor_move(12, 127);
			delay(50);
			c::motor_move(12, 0);

			robotDevices.chassis.follow(SkillsStep3_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.turnToHeading(145, 1000);
			robotDevices.chassis.waitUntilDone();

			robotDevices.chassis.follow(SkillsStep4_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.turnToHeading(75, 1000);

			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.follow(SkillsStep5_txt, 20, 10000, true);
			robotDevices.chassis.waitUntilDone();

			robotDevices.chassis.turnToHeading(45, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.follow(SkillsStep6_txt, 20, 10000, true);
			robotDevices.chassis.waitUntilDone();

			robotDevices.chassis.follow(SkillsStep7_txt, 20, 6000, false);
			robotDevices.chassis.waitUntilDone();
												robotDevices.mogoClampPiston.set_value(true);

			  			c::motor_move(3, -127);
			c::motor_move(13, -127);
delay(500);
  			c::motor_move(3, 127);
			c::motor_move(13, 127);
			robotDevices.chassis.follow(SkillsStep8_txt, 20, 8000, true);
			robotDevices.chassis.waitUntilDone();

			c::motor_move(3, 0);
			c::motor_move(13, 0);
			// Move arm back
			c::motor_move(12, 127);
			delay(50);
			c::motor_move(12, 0);
			robotDevices.chassis.turnToHeading(100, 1000);






			robotDevices.chassis.waitUntilDone();

									robotDevices.chassis.setPose(-25.71, -21.541, 100);

			robotDevices.chassis.follow(SkillsStep9_txt, 20, 8000, false);//bruh
						robotDevices.chassis.waitUntilDone();
						delay(500);

									robotDevices.mogoClampPiston.set_value(false);
									delay(250);
												robotDevices.chassis.turnToHeading(90, 1000);
												  			c::motor_move(3, 127);
			c::motor_move(13, 127);

									robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.follow(SkillsStep10_txt, 20, 8000, true);//bruh
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.turnToHeading(350, 1000);
				robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.follow(SkillsStep11_txt, 20, 8000, true);//bruh
			robotDevices.chassis.waitUntilDone();
												robotDevices.chassis.turnToHeading(260, 1000);
																robotDevices.chassis.waitUntilDone();

									robotDevices.chassis.setPose(-23.768, 43.834, 260);

			robotDevices.chassis.follow(SkillsStep12_txt, 20, 8000, true);//bruh
				robotDevices.chassis.waitUntilDone();
												robotDevices.chassis.turnToHeading(25, 1000);
							robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.follow(SkillsStep13_txt, 20, 2000, true);//bruh

							robotDevices.chassis.waitUntilDone();
												robotDevices.chassis.turnToHeading(100, 1000);
							robotDevices.chassis.waitUntilDone();
										robotDevices.chassis.follow(SkillsStep14_txt, 20, 1000, false);//bruh
							robotDevices.chassis.waitUntilDone();
										  			c::motor_move(3, -127);
			c::motor_move(13, -127);
												robotDevices.mogoClampPiston.set_value(true);
									robotDevices.chassis.setPose(-58.074, 61.958, 100);
										robotDevices.chassis.follow(SkillsStep15_txt, 20, 5000, true);//bruh
																	robotDevices.chassis.waitUntilDone();
												robotDevices.mogoClampPiston.set_value(false);

												robotDevices.chassis.turnToHeading(180, 1000);
																													robotDevices.chassis.waitUntilDone();

																						robotDevices.chassis.follow(SkillsStep16_txt, 20, 2000, false);//bruh
																													robotDevices.chassis.waitUntilDone();
																						robotDevices.chassis.follow(SkillsStep17_txt, 20, 5000, true);//bruh









			break;
	}
}

/**
 * @brief Manages the drivetrain controls during the Driver Control period.
 * 
 * This function reads the analog inputs from the controller to control the robot's drivetrain
 * using a "tank drive" configuration. The tank drive configuration separates control of the left 
 * and right wheels, where each joystick controls one side of the drivetrain.
 */
void DrivetrainDriverControl() {

	// Read the Y-axis values from the controller's analog sticks.
	// rightY controls the right side of the drivetrain.
	// leftY controls the left side of the drivetrain.
	int rightY = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
	int leftY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);

	// Apply tank drive control to the drivetrain.
	// The tank method from lemlibs takes two arguments:
	// The first argument is the power for the left side (negative of leftY to match joystick direction).
	// The second argument is the power for the right side (rightY directly from joystick).
	robotDevices.chassis.tank(leftY, rightY);
}

/**
 * @brief Controls the mobile goal clamp during the Driver Control period.
 * 
 * This function manages the mobile goal clamp based on controller button inputs:
 * - Pressing the Y button will activate the clamp.
 * - Pressing the Right button will deactivate the clamp (release it).
 */
void MogoClampDriverControl() {

	// Check if the Y button is pressed on the controller.
	// If pressed, activate the clamp to secure the mobile goal.
	if (master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
    	robotDevices.mogoClampPiston.set_value(true);
	}

	// Check if the Right button is pressed on the controller.
	// If pressed, deactivate the clamp to release the mobile goal.
	if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
    	robotDevices.mogoClampPiston.set_value(false);

	}
}

/**
 * @brief Controls the mobile goal clamp during the Driver Control period.
 * 
 * This function manages the mobile goal clamp based on controller button inputs:
 * - Pressing the Y button will activate the clamp.
 * - Pressing the Right button will deactivate the clamp (release it).
 */
void RingStopperDriverControl() {

	// Check if the Y button is pressed on the controller.
	// If pressed, activate the clamp to secure the mobile goal.
	if (master.get_digital(E_CONTROLLER_DIGITAL_B)) {
		robot.ringStopper.Lower();
	}

	// Check if the Right button is pressed on the controller.
	// If pressed, deactivate the clamp to release the mobile goal.
	if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
		robot.ringStopper.Raise();
	}
}



// Prep Arm Function
void prepArm() {
	while (robotDevices.liftMotor.get_position() > -295) {
		c::motor_move(12, -127);
		pros::delay(10);
	}
	c::motor_move(12, 0);
}

// Score Arm Function
void scoreArm() {
	while (robotDevices.liftMotor.get_position() > -1450) {
		c::motor_move(7, -127);
		pros::delay(10);
	}
	c::motor_move(7, 0);
	pros::delay(250);
	while (robotDevices.liftMotor.get_position() < 0) {
		c::motor_move(7, 127);
		pros::delay(10);
	}
	c::motor_move(12, 0);
}

// Wrapper functions to start tasks
void startPrepArmTask() {
	pros::Task prepArmTask(prepArm);
}

void startScoreArmTask() {
	pros::Task scoreArmTask(scoreArm);
}


/**
 * @brief Manages the high stake lift controls during the Driver Control period.
 * 
 * This function adjusts the position of the high stake lift based on controller button inputs:
 * - Pressing the L2 button will raise the lift.
 * - Pressing the L1 button will lower the lift.
 * - When neither button is pressed, the lift will be held in its current position.
 */
void LiftDriverControl() {



	// Check if the L2 button is pressed.
	// If pressed, command the lift to rise.
	if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
			// Create threads to run prepArm and scoreArm asynchronously
			c::motor_move(7, -127);


	// Detach threads so they run independently
	}
	// Check if the L1 button is pressed.
	// If pressed and L2 is not pressed, command the lift to lower.
	else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			// Create threads to run prepArm and scoreArm asynchronously
			c::motor_move(7, 127);


	// Detach threads so they run independently
	}
	// If neither L2 nor L1 is pressed.
	// Stop the lift to hold it in its current position.
	else {
		    robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

		c::motor_move(7, 0);
	}
}

/**
 * @brief Controls the ring intake system during the Driver Control period.
 * 
 * This function manages the intake system based on the following controller button inputs:
 * - Pressing the R1 button will spin the intake forward.
 * - Pressing the R2 button will spin the intake backward.
 * - When neither R1 nor R2 is pressed, the intake will coast to a stop.
 */
void IntakeDriverControl() {

	// Check if the R1 button is pressed.
	// If pressed, command the intake to spin forward with full power (100%).
	if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
		 c::motor_move(3, 127);
		 c::motor_move(17, 127);

	} 
	// Check if the R2 button is pressed.
	// If pressed and R1 is not pressed, command the intake to spin backward with full power (100%).
	else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		c::motor_move(3, -127);
		c::motor_move(17, -127);

	} 
	// If neither R1 nor R2 is pressed.
	// Command the intake to stop and coast.
	else {
				c::motor_move(13, 0);

		robot.intake.StopIntake();
	}
}

/**
 * @brief Executes the Driver Control (opcontrol) tasks while the robot is enabled.
 * 
 * This function runs in an infinite loop while the robot is under operator control.
 * It handles the control of the drivetrain, mobile goal clamp, lift, and intake systems.
 */
void opcontrol() {

	robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);

	/*
    pros::lcd::initialize(); // initialize brain screen
    robotDevices.chassis.calibrate(); // calibrate sensors
	while (robotDevices.imu.is_calibrating()) {
		pros::delay(10);
	}

    // print position to brain screen
      pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", robotDevices.chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", robotDevices.chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", robotDevices.chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
	*/
   // c::motor_move(3, 100);

	// Infinite loop to continuously run operator control tasks.
	while (true) {
       
		// Call function to handle drivetrain controls based on joystick input.
		DrivetrainDriverControl();
		
		// Call function to manage mobile goal clamp based on button input.
		MogoClampDriverControl();
		
		// Call function to control the lift based on button input.
		LiftDriverControl();
	
		// Call function to manage the intake system based on button input.
		IntakeDriverControl();

		RingStopperDriverControl();

		// Small delay to prevent the loop from running too fast
		// This helps to balance processing load and maintain responsiveness.
		delay(25);
	}
	
}