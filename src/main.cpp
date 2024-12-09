// Include headers for the inherited classes
#include "main.h"
#include "Brain_UI.h"
#include "Robot.h"
#include "Autonomous_Manager.h"
#include "Robot_Config.h"
#include "pros/optical.hpp"
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
	robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST); robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST); robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST); robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);

	robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	robotDevices.liftMotor.tare_position();

	// Calibrate sensors
    robotDevices.chassis.calibrate();
    while (robotDevices.imu.is_calibrating()) {
        pros::delay(10);
    }

	// Draws autonomous selector UI on the Brain using LVGL,
	// an industry standard micro-controller screen UI library.
	ui.DisplayAutonSelectorUI();
}



// Prep Arm Function
void prepArm() {
	c::motor_set_brake_mode(7, E_MOTOR_BRAKE_HOLD); c::motor_set_brake_mode(16, E_MOTOR_BRAKE_HOLD);
	while (robotDevices.liftRotation.get_position() > -2400) {
		c::motor_move(7, -90); c::motor_move(16, 90);
		pros::delay(10);
	}
	c::motor_move(7, 0); c::motor_move(16, 0);
}

// Score Arm Function
void scoreArm() {
	c::motor_set_brake_mode(7, E_MOTOR_BRAKE_HOLD); c::motor_set_brake_mode(16, E_MOTOR_BRAKE_HOLD);
	while (robotDevices.liftMotor.get_position() > -2300) {
		c::motor_move(17, 50);
		c::motor_move(7, -90); c::motor_move(16, 90);
		pros::delay(10);
	}
	c::motor_move(17, 0);
	c::motor_move(7, 0); c::motor_move(16, 0);
}

// Score Arm Function
void returnArm() {
	c::motor_set_brake_mode(7, E_MOTOR_BRAKE_HOLD); c::motor_set_brake_mode(16, E_MOTOR_BRAKE_HOLD);
	while (robotDevices.liftMotor.get_position() < -600) {
		c::motor_move(7, 90); c::motor_move(16, -90);
		pros::delay(10);
	}
	c::motor_move(7, 0); c::motor_move(16, 0);
}

// Score Arm Function
void restArm() {
	c::motor_set_brake_mode(7, E_MOTOR_BRAKE_HOLD); c::motor_set_brake_mode(16, E_MOTOR_BRAKE_HOLD);
	while (robotDevices.liftMotor.get_position() < -100) {
		c::motor_move(7, 90); c::motor_move(16, -90);
		pros::delay(10);
	}
	c::motor_move(7, 0); c::motor_move(16, 0);
}

void ejectRing() {
	c::motor_move(17, 0);
	delay(300);
}

// Wrapper functions to start tasks
void startPrepArmTask() { pros::Task prepArmTask(prepArm); }

void startScoreArmTask() { pros::Task scoreArmTask(scoreArm); }

void startReturnArmTask() { pros::Task returnArmTask(returnArm); }

void startrestArm() { pros::Task restArmTask(restArm); }

void startEjectTask() { pros::Task ejectTask(ejectRing); }

/*** @brief Load paths. */
ASSET(bluelefty_txt);
ASSET(blueleft2_txt);
ASSET(blueleft3_txt);
ASSET(blueleft4_txt);

ASSET(redrighty_txt);
ASSET(redright2_txt);
ASSET(redright3_txt);
ASSET(redright4_txt);

ASSET(skills1_txt);
ASSET(skills2_txt);
ASSET(skills3_txt);
ASSET(skills4_txt);
ASSET(skills5_txt);
ASSET(skills6_txt);
ASSET(skills7_txt);
ASSET(skills8_txt);

bool colorSortBlue = false;
/**
 * @brief Runs Autonomous period functions.
 */
void autonomous() {
	robotDevices.liftRotation.set_position(359);

// Retrieve the selected autonomous mode from the BrainUI.
	int selectedMode = ui.selectedAuton;
	
	selectedMode = 3;
	// Blue Right - 0
	// Blue Left - 1
	// Red left - 2
	// Red Right - 3

	// Determine which autonomous routine to execute based on the selected mode.
	switch(selectedMode) {
		case 0:
			colorSortBlue = true;
			// Executes the autonomous routine for the Blue Alliance, Right side.
			// Set initial position
			robotDevices.chassis.setPose(65, -7, 10);
			robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			
			break;
		case 1:
			colorSortBlue = true;
			// Executes the autonomous routine for the Blue Alliance, Left side.
			// Set initial position
			robotDevices.chassis.setPose(65, -7, 10);
			robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			c::motor_move(7, -127);
			c::motor_move(16, 127);
			delay(800);
			c::motor_move(7, 127);
			c::motor_move(16, -127);
			delay(1000);
			c::motor_move(7, 0);
			c::motor_move(16, 0);
			robotDevices.mogoClampPiston.set_value(true);
			robotDevices.chassis.follow(bluelefty_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();
			delay(100);
			robotDevices.mogoClampPiston.set_value(false);
						delay(250);

			c::motor_move(17, -127);
			robotDevices.chassis.turnToHeading(180, 2000);
			robotDevices.chassis.follow(blueleft2_txt, 15, 5000, true);
			robotDevices.chassis.waitUntilDone();
			delay(1250);
			c::motor_move(17, 0);
			robotDevices.chassis.turnToHeading(330, 2000);
			c::motor_move(17, -127);
			robotDevices.ringStopperPiston.set_value(true);
			delay(20);
            robotDevices.chassis.follow(blueleft3_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			delay(500);
			robotDevices.ringStopperPiston.set_value(false);
			delay(350);

            robotDevices.chassis.turnToHeading(270, 1000);
			delay(100);
            robotDevices.chassis.follow(blueleft4_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			c::motor_move(16, 127);
			c::motor_move(7, -127);
		    delay(700);
			c::motor_move(16, 0);
			c::motor_move(7, 0);
			break;
		case 2:
			colorSortBlue = false;
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
			break;
		case 3:
			// Executes the autonomous routine for the Blue Alliance, Left side.
			// Set initial position
			robotDevices.chassis.setPose(-65.88, -7.301, 350);
			robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			c::motor_move(7, -127);
			c::motor_move(16, 127);
			delay(800);
			c::motor_move(7, 127);
			c::motor_move(16, -127);
			delay(1000);
			c::motor_move(7, 0);
			c::motor_move(16, 0);
			robotDevices.mogoClampPiston.set_value(true);
			robotDevices.chassis.follow(redrighty_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();
			delay(100);
			robotDevices.mogoClampPiston.set_value(false);
						delay(200);

			c::motor_move(17, -127);
			robotDevices.chassis.turnToHeading(180, 2000);
			robotDevices.chassis.follow(redright2_txt, 15, 5000, true);
			robotDevices.chassis.waitUntilDone();
			delay(1250);
			c::motor_move(17, 0);
			robotDevices.chassis.turnToHeading(330, 2000);
			c::motor_move(17, -127);
			robotDevices.ringStopperPiston.set_value(true);
			delay(20);
            robotDevices.chassis.follow(redright3_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			delay(500);
			robotDevices.ringStopperPiston.set_value(false);
			delay(350);

            robotDevices.chassis.turnToHeading(90, 1000);
			delay(100);
						c::motor_move(16, 127);
			c::motor_move(7, -127);
		    delay(400);
			c::motor_move(16, 0);
			c::motor_move(7, 0);
            robotDevices.chassis.follow(redright4_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			break;
		case 4:
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.chassis.setPose(-62.605, -7.301, 320);
			robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

			robotDevices.mogoClampPiston.set_value(true);
			c::motor_move(16, 127);
			c::motor_move(7, -127);
			delay(700);
			c::motor_move(16, -127);
			c::motor_move(7, 127);
		    delay(700);
			robotDevices.chassis.follow(skills1_txt, 15, 5000, false);
			robotDevices.chassis.waitUntilDone();
			robotDevices.mogoClampPiston.set_value(false);
			delay(500);
			robotDevices.chassis.turnToHeading(100, 500);
			robotDevices.chassis.waitUntilDone();
			c::motor_move(17, -127);
			robotDevices.chassis.follow(skills2_txt, 15, 5000, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.turnToHeading(170, 900);
			robotDevices.chassis.waitUntilDone();

			robotDevices.chassis.follow(skills3_txt, 15, 5000, true);
			robotDevices.chassis.waitUntilDone();
			delay(1000);
			robotDevices.chassis.turnToHeading(250, 900);
			robotDevices.chassis.waitUntilDone();
			delay(1000);

			startPrepArmTask();
			robotDevices.chassis.follow(skills4_txt, 15, 5000, true);
			robotDevices.chassis.waitUntilDone();
			delay(3000);
			c::motor_move(17, 0);

			robotDevices.chassis.turnToHeading(215, 700);
			robotDevices.chassis.waitUntilDone();

			robotDevices.chassis.follow(skills5_txt, 10, 700, true);
			robotDevices.chassis.waitUntilDone();
			c::motor_move(17, 50);

			c::motor_move(16, 127);
			c::motor_move(7, -127);
			delay(500);
			c::motor_move(17, 0);

			c::motor_move(16, -127);
			c::motor_move(7, 127);
			delay(600);
			c::motor_move(16, 0);
			c::motor_move(7, 0);

			robotDevices.chassis.turnToHeading(310, 2000);
			robotDevices.chassis.waitUntilDone();
			c::motor_move(17, -127);

			robotDevices.chassis.follow(skills6_txt, 15, 5000, true);
			robotDevices.chassis.waitUntilDone();
			delay(1000);
			robotDevices.chassis.turnToHeading(170, 2000);
			robotDevices.chassis.waitUntilDone();

			robotDevices.chassis.turnToHeading(20, 2000);
			robotDevices.chassis.follow(skills7_txt, 15, 5000, false);
			robotDevices.mogoClampPiston.set_value(true);

			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.follow(skills8_txt, 15, 5000, true);
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
	if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) { robotDevices.mogoClampPiston.set_value(true);  } 
	else  											 { robotDevices.mogoClampPiston.set_value(false); }

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


int pressCount = 1;
bool lastButtonState = false;
bool isPressed = false;
bool wasPressed = false;

/**
 * @brief Manages the high stake lift controls during the Driver Control period.
 * 
 * This function adjusts the position of the high stake lift based on controller button inputs:
 * - Pressing the L2 button will raise the lift.
 * - Pressing the L1 button will lower the lift.
 * - When neither button is pressed, the lift will be held in its current position.
 */
void LiftDriverControl() {

	bool isPressed = master.get_digital(E_CONTROLLER_DIGITAL_L2);

	if (isPressed && !wasPressed) {
		pressCount = (pressCount + 1) % 4;
		switch(pressCount) {
			case 0: startPrepArmTask(); break;
			case 1: startScoreArmTask(); break;
			case 2: startReturnArmTask(); break;
			case 3: startrestArm(); break;
		}
	}

	wasPressed = isPressed;

	// Check if the L2 button is pressed.
	// If pressed, command the lift to rise.
	if (master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
		// Create threads to run prepArm and scoreArm asynchronously
		c::motor_move(7, -127);
		c::motor_move(16, 127);
	}
	// Check if the L1 button is pressed.
	// If pressed and L2 is not pressed, command the lift to lower.
	else if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
		// Create threads to run prepArm and scoreArm asynchronously
		c::motor_move(7, 127);
		c::motor_move(16, -127);
	}
	// If neither L2 nor L1 is pressed.
	// Stop the lift to hold it in its current position.
	else {
		robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);	
		c::motor_move(7, 0);
		c::motor_move(16, 0);
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
		 c::motor_move(3, -127);
		 c::motor_move(17, -127);

	} 
	// Check if the R2 button is pressed.
	// If pressed and R1 is not pressed, command the intake to spin backward with full power (100%).
	else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		c::motor_move(3, 127);
		c::motor_move(17, 127);

	} 
	// If neither R1 nor R2 is pressed.
	// Command the intake to stop and coast.
	else {
				c::motor_move(17, 0);

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
	ui.DisplayMatchImage();

/*		pros::lcd::initialize(); // initialize brain screen
    robotDevices.chassis.calibrate(); // calibrate sensors
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

			colorSortBlue = true;
robotDevices.liftRotation.set_position(359);

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
       	robotDevices.optical.set_led_pwm(100);

	// Infinite loop to continuously run operator control tasks.
	while (true) {
		/*
		double hue = robotDevices.optical.get_hue();
		if (robotDevices.optical.get_proximity() > 75) {
		if (colorSortBlue) 
		{
			if ((hue >=0 && hue <= 20) || (hue >=340 && hue <= 360)) {
					//delay(50);

				startEjectTask();
			}
		} else {
			if (hue >=120 && hue <= 200) {
					//delay(50);

				startEjectTask();
			}
		}
		}*/

	
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