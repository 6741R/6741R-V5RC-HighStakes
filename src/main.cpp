#include "main.h"
#include "BrainUI.h"
#include "Robot.h"
#include "Autonomous_Manager.h"
#include "Robot_Config.h"

using namespace pros;

// Initialize global devices object
Robot_Config robotDevices;

// Initialize global robot object
Robot robot;

// Initialize autonomous manager object
Autonomous_Manager autonManager(robot);

// Initialize UI object
BrainUI ui;

// Initialize Controller object
Controller master(pros::E_CONTROLLER_MASTER);

// Runs when robot is disabled by field controller
void disabled() {}

// Runs when initialized by field controller
void competition_initialize() {
	// Draws autonomous selector UI using LVGL
	ui.DisplayAutonSelectorUI();
}

// Runs autonomous period
void autonomous() {

	// Autonomous selector logic, grabs selected auton from BrainUI class
	switch(ui.selectedAuton) {
		case 0:
			autonManager.BlueMatchLeft();
			break;
		case 1:
			autonManager.BlueMatchRight();
			break;
		case 2:
			autonManager.RedMatchLeft();
			break;
		case 3:
			autonManager.RedMatchRight();
			break;
		case 4: // Runs skills auton by default
			autonManager.Skills();
			break;
	}
}

// Driver control handling drivetrain
void DrivetrainDriverControl() {
		// Tank Control
		int rightY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		int leftY = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		robotDevices.chassis.tank(-leftY, rightY); // Uses lemlibs tank control method
}

// Driver control handling mogo clamp
void MogoClampDriverControl() {

	// Clamps with Y button, unclamps with Right button

	if (master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
		robot.mogoClamp.Clamp();
	}

	if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
		robot.mogoClamp.Unclamp();
	}
}

// Driver control handling lift
void LiftDriverControl() {

	// Raises lift with L2, lowers lift with L1

	if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
		//robot.lift.RaiseLift();
		c::motor_move(12, 127);
	} else if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
		//robot.lift.LowerLift();
		c::motor_move(12, -127);
	} else {
		//robot.lift.StopLift();
		c::motor_move(12, 0);
	}
}

// Driver control handling intake
void IntakeDriverControl() {

	// Intakes with R1, outtakies with R2
	if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
		//robot.intake.Intake(100);
		c::motor_move(13, 127);
	} else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		robot.intake.Outtake(100);
		c::motor_move(13, -127);
	} else {
		//robot.intake.StopIntake();
		c::motor_set_brake_mode(12, E_MOTOR_BRAKE_HOLD);
		c::motor_brake(13);
	}
}

// User control
void opcontrol() {
	while (true) {
		DrivetrainDriverControl();
		MogoClampDriverControl();
		LiftDriverControl();
		IntakeDriverControl();
		master.print(0, 0, "opcontrol is running");
		delay(25);
	}
}

