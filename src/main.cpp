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

ASSET(SkillsStep1_txt);
ASSET(SkillsStep3_txt);
ASSET(SkillsStep4_txt);
ASSET(SkillsStep5_txt);








/**
 * @brief Runs Autonomous period functions.
 */
void autonomous() {
	
// Retrieve the selected autonomous mode from the BrainUI.
	int selectedMode = ui.selectedAuton;
	selectedMode = 4;
	// Determine which autonomous routine to execute based on the selected mode.
	switch(selectedMode) {
		case 0:

			robotDevices.chassis.setPose(52, 23, 90);


			// Executes the autonomous routine for the Blue Alliance, left side.
			robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

			robotDevices.mogoClampPiston.set_value(true);

			robotDevices.chassis.follow(BlueRightStep1_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();
			robotDevices.mogoClampPiston.set_value(false);
			delay(250);
			robotDevices.chassis.turnToHeading(359, 750);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(24, 24, 359);

			c::motor_move(3, 127);
			robotDevices.chassis.follow(BlueRightStep2_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.turnToHeading(279, 750);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(24, 46, 279);
			robotDevices.chassis.follow(BlueRightStep3_txt, 15, 1500, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(8.5, 51, 279);

			robotDevices.chassis.follow(BlueRightStep4_txt, 15, 10000, false);
			robotDevices.chassis.setPose(24, 47, 279);
			robotDevices.chassis.turnToHeading(245, 750);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(31, 46, 245);
			robotDevices.chassis.follow(BlueRightStep5_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(18, 42, 245);

			robotDevices.chassis.follow(BlueRightStep6_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.turnToHeading(190, 750);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(29, 47, 190);
			robotDevices.chassis.follow(BlueRightStep7_txt, 15, 10000, true);

			c::motor_move(12, -127);
			delay(1500);
			c::motor_move(12, 0);

			break;
		case 1:

			robotDevices.chassis.setPose(59, -12, 180);

			// Executes the autonomous routine for the Blue Alliance, left side.
			robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

			robotDevices.chassis.follow(BlueLeftStep1_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.turnToHeading(270, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.setPose(59, -3.75, 270);
			robotDevices.chassis.follow(BlueLeftStep2_txt, 6, 1000, false);
			robotDevices.chassis.waitUntilDone();
			c::motor_move(3, 127);
			delay(500);
			c::motor_move(3, 0);

			robotDevices.chassis.setPose(69, -3.75, 270);
			robotDevices.chassis.follow(BlueLeftStep3_txt, 6, 1000, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.turnToHeading(43, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.mogoClampPiston.set_value(true);
			robotDevices.chassis.setPose(69, -3.75, 43);
			robotDevices.chassis.follow(BlueLeftStep4_txt, 15, 1000, false);
			robotDevices.chassis.waitUntilDone();
			delay(250);
			robotDevices.mogoClampPiston.set_value(false);
			delay(250);
			robotDevices.chassis.turnToHeading(160, 1000);
			robotDevices.chassis.waitUntilDone();

			robotDevices.chassis.setPose(45.491, -28, 160);
			c::motor_move(3, 127);
			robotDevices.chassis.follow(BlueLeftStep5_txt, 15, 1000, true);
			robotDevices.chassis.waitUntilDone();

			delay(500);
			robotDevices.chassis.setPose(49, -43, 160);

			robotDevices.chassis.follow(BlueLeftStep6_txt, 15, 1000, false);








			// Executes the autonomous routine for the Blue Alliance, right side.
			autonManager.BlueMatchRight();
			break;
		case 2:
			// Executes the autonomous routine for the Red Alliance, left side.
			autonManager.RedMatchLeft();
			break;
		case 3:
			
			break;
		case 4:
					robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

			// Executes the skills autonomous routine by default
			robotDevices.chassis.setPose(-62, 0, 90);
			c::motor_move(3, 127);
			delay(500);
			c::motor_move(3, 0);
			delay(150);

			robotDevices.chassis.turnToHeading(350, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.mogoClampPiston.set_value(true);
			robotDevices.chassis.follow(SkillsStep1_txt, 15, 10000, false);
			robotDevices.chassis.waitUntilDone();
			delay(200);
			robotDevices.mogoClampPiston.set_value(false);
			delay(100);
			robotDevices.chassis.turnToHeading(220, 1000);
			robotDevices.chassis.waitUntilDone();
			c::motor_move(3, 127);
			robotDevices.chassis.setPose(-49, -18, 220);

			robotDevices.chassis.follow(SkillsStep3_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();

			robotDevices.chassis.turnToHeading(140, 1000);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.follow(SkillsStep4_txt, 15, 10000, true);
			robotDevices.chassis.waitUntilDone();
			robotDevices.chassis.turnToHeading(93, 1000);
			robotDevices.chassis.waitUntilDone();
			delay(250);
						robotDevices.chassis.setPose(-49, -58, 93);

						robotDevices.chassis.follow(SkillsStep5_txt, 20, 10000, true);



			break;
	}



/*
	//robotDevices.drivetrain.autonDrive(24);

	robotDevices.mogoClampPiston.set_value(true);
	delay(250);
	master.print(0,0, "2");

	robotDevices.chassis.setPose(50, 42, 60);

	robotDevices.chassis.follow(match2_txt, 15, 1100, false);
	robotDevices.chassis.waitUntilDone();
	delay(100);

	master.print(0,0, "3");
	robotDevices.mogoClampPiston.set_value(false);
	delay(250);
	c::motor_move(3, 127);
	delay(100);
	robotDevices.chassis.turnToHeading(340, 1000);
	robotDevices.chassis.waitUntilDone();
	robotDevices.chassis.setPose(33, 31, 340);

	robotDevices.chassis.follow(match5_txt, 15, 3000, true);
	robotDevices.chassis.waitUntilDone();
	robotDevices.chassis.turnToHeading(259, 1000);
	robotDevices.chassis.waitUntilDone();

	robotDevices.chassis.setPose(23, 51, 259);
	robotDevices.chassis.follow(match6_txt, 15, 1500, true);
	robotDevices.chassis.waitUntilDone();

			//delay(500);
	robotDevices.chassis.setPose(4, 50, 262);

	robotDevices.chassis.follow(match7_txt, 15, 3000, false);
	robotDevices.chassis.waitUntilDone();

	robotDevices.chassis.turnToHeading(239, 1000);
	robotDevices.chassis.waitUntilDone();
    master.print(0,0, "buns");

	robotDevices.chassis.setPose(19, 50, 238);

	robotDevices.chassis.follow(match8_txt, 15, 3000, true);
	master.print(0,0, "buns222");
	delay(1500);
	c::motor_move(3, 0);		

	robotDevices.chassis.waitUntilDone();
	robotDevices.chassis.follow(match9_txt, 15, 3000, false);
	robotDevices.chassis.waitUntilDone();
		robotDevices.mogoClampPiston.set_value(true);
		robotDevices.chassis.turnToHeading(320, 100);

										robotDevices.chassis.waitUntilDone();
												robotDevices.chassis.setPose(34, 50, 0);

		robotDevices.chassis.follow(match10_txt, 22, 6000, false);
														robotDevices.chassis.waitUntilDone();






*/

	//robotDevices.drivetrain.autonDrive(24);

/*
	robotDevices.mogoClampPiston.set_value(true);
	delay(250);
	master.print(0,0, "2");

	robotDevices.chassis.setPose(-50, 42, 300);

	robotDevices.chassis.follow(lmatch2_txt, 15, 1100, false);
	robotDevices.chassis.waitUntilDone();
	delay(100);

	master.print(0,0, "3");
	robotDevices.mogoClampPiston.set_value(false);
	delay(250);
	c::motor_move(3, 127);
	delay(100);
	robotDevices.chassis.turnToHeading(20, 1000);
	robotDevices.chassis.waitUntilDone();
	robotDevices.chassis.setPose(-33, 31, 20);

	robotDevices.chassis.follow(lmatch5_txt, 15, 3000, true);
	robotDevices.chassis.waitUntilDone();
	robotDevices.chassis.turnToHeading(95, 1000);
	robotDevices.chassis.waitUntilDone();

	robotDevices.chassis.setPose(-23, 51, 95);
	robotDevices.chassis.follow(lmatch6_txt, 15, 1500, true);
	robotDevices.chassis.waitUntilDone();

			//delay(500);
	robotDevices.chassis.setPose(-4, 50, 95);

	robotDevices.chassis.follow(lmatch7_txt, 15, 3000, false);
	robotDevices.chassis.waitUntilDone();

	robotDevices.chassis.turnToHeading(125, 1000);
	robotDevices.chassis.waitUntilDone();
    master.print(0,0, "buns");

	robotDevices.chassis.setPose(-19, 50, 125);

	robotDevices.chassis.follow(lmatch8_txt, 15, 3000, true);
	master.print(0,0, "buns222");
	delay(1500);
	c::motor_move(3, 0);		

	robotDevices.chassis.waitUntilDone();
	
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
		c::motor_move(12, -127);
		pros::delay(10);
	}
	c::motor_move(12, 0);
	pros::delay(250);
	while (robotDevices.liftMotor.get_position() < 0) {
		c::motor_move(12, 127);
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
			c::motor_move(12, -80);


	// Detach threads so they run independently
	}
	// Check if the L1 button is pressed.
	// If pressed and L2 is not pressed, command the lift to lower.
	else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			// Create threads to run prepArm and scoreArm asynchronously
			c::motor_move(12, 127);


	// Detach threads so they run independently
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