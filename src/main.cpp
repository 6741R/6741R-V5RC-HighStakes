// Include headers for the inherited classes
#include "main.h"
#include "Brain_UI.h"
#include "Robot.h"
#include "Autonomous_Manager.h"
#include "Robot_Config.h"

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

/*** @brief Load paths. */
ASSET(testPath3_txt);


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

	// Draws autonomous selector UI on the Brain using LVGL,
	// an industry standard micro-controller screen UI library.
	//ui.DisplayAutonSelectorUI();
}

/**
 * @brief Runs Autonomous period functions.
 */
void autonomous() {
    // Calibrate sensors
    robotDevices.chassis.calibrate(); // calibrate sensors
    while (robotDevices.imu.is_calibrating()) {
        pros::delay(10);
    }

    // Set initial position to x:0, y:0, heading:0
    robotDevices.chassis.setPose(-12, -12, 90);

    robotDevices.chassis.follow(testPath3_txt, 7, 15000);

	/*
	// Retrieve the selected autonomous mode from the BrainUI.
	int selectedMode = ui.selectedAuton;
	// Determine which autonomous routine to execute based on the selected mode.
	switch(selectedMode) {
		case 0:
			// Executes the autonomous routine for the Blue Alliance, left side.
			autonManager.BlueMatchLeft();
			break;
		case 1:
			// Executes the autonomous routine for the Blue Alliance, right side.
			autonManager.BlueMatchRight();
			break;
		case 2:
			// Executes the autonomous routine for the Red Alliance, left side.
			autonManager.RedMatchLeft();
			break;
		case 3:
			// Executes the autonomous routine for the Red Alliance, right side.
			autonManager.RedMatchRight();
			break;
		case 4:
			// Executes the skills autonomous routine by default
			autonManager.Skills();
			break;
	}
	*/
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
	if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
		c::motor_move(12, 127);
		robot.ringStopper.Lower();
	}
	// Check if the L1 button is pressed.
	// If pressed and L2 is not pressed, command the lift to lower.
	else if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
		c::motor_move(12, -127);
			//robot.ringStopper.Raise();
	}
	// If neither L2 nor L1 is pressed.
	// Stop the lift to hold it in its current position.
	else {
		    robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

		c::motor_move(12, 0);
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
	} 
	// Check if the R2 button is pressed.
	// If pressed and R1 is not pressed, command the intake to spin backward with full power (100%).
	else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		c::motor_move(3, -127);
	} 
	// If neither R1 nor R2 is pressed.
	// Command the intake to stop and coast.
	else {
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
    });*/
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