// Include headers for the inherited classes and VEX Functionality
#include "main.h"
#include "Brain_UI.h"
#include "Robot.h"
#include "Autonomous_Manager.h"
#include "Robot_Config.h"
#include "pros/optical.hpp"
#include <thread>

using namespace pros;

/*** @brief Global instances representing core robot components ***/
Robot_Config robotDevices;
Robot robot;
Brain_UI ui;
Autonomous_Manager autonManager(robot);
Controller master(pros::E_CONTROLLER_MASTER);

/*** @brief Runs when robot is disabled by VEX Field Controller */
void disabled() {   
    // Display Autonomous Selector UI and calibrate sensors
    ui.DisplayAutonSelectorUI();
    robotDevices.chassis.calibrate(); 
}

/*** @brief Initialize function. Runs on program startup */
void initialize() {}

/*** @brief Runs Autonomous period functions */
void autonomous() {
    // Coordinates
    /*
    pros::lcd::initialize(); // initialize brain screen
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

    // Retrieve the selected autonomous mode from the BrainUI.
    int selectedMode = ui.selectedAuton;
    // Autonomous override
    // selectedMode = 0;

    // Red SOLO AWP   1
    // Blue SOLO AWP  2
    // Red GOAL RUSH  3
    // Blue GOAL RUSH 4
    // Skills         5

    // Determine which autonomous routine to execute based on the selected mode.
    switch (selectedMode)
    {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 5:
            break;
    }
}

/*** @brief Runs when initialized by VEX Field Controller */
void competition_initialize() {
    // Hold Arm motor and calibrate its position, and calibrate drivetrain sensors
    robotDevices.armMotor1.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    robotDevices.armMotor2.set_brake_mode(E_MOTOR_BRAKE_HOLD);

    robotDevices.chassis.calibrate();
    // initialize brain screen
    pros::lcd::initialize();         
    // Draws autonomous selector UI on the Brain using LVGL
    ui.DisplayAutonSelectorUI();
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
    robotDevices.leftMotors.move(leftY); // Negative power for counter rotation
    robotDevices.rightMotors.move(rightY);
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
    if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
        robot.mogoClamp.Clamp();
    }
    else {
        robot.mogoClamp.Unclamp();
    }
}

/**
 * @brief Controls the mobile goal clamp during the Driver Control period.
 *
 * This function manages the mobile goal clamp based on controller button inputs:
 * - Pressing the Y button will activate the clamp.
 * - Pressing the Right button will deactivate the clamp (release it).
 */
void DoinkerDriverControl() {
    // Check if the Y button is pressed on the controller.
    // If pressed, raise the doinker
    if (master.get_digital(E_CONTROLLER_DIGITAL_B)) {
        robot.doinker.Raise();
    }

    // Check if the Right button is pressed on the controller.
    // If pressed, lower the doinker
    if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
        robot.doinker.Lower();
    }
}

/**
 * @brief Manages the high stake arm controls during the Driver Control period.
 *
 * This function adjusts the position of the high stake arm based on controller button inputs:
 * - Pressing the L2 button will raise the arm.
 * - Pressing the L1 button will lower the arm.
 * - When neither button is pressed, the arm will be held in its current position.
 */
void ArmDriverControl() {

    // Check if the Y button is pressed.
    // If pressed, raise arm
    if (master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
        robot.lift.Raise();
    }
    // Check if the Right button is pressed.
    // If pressed, lower arm
    else if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
        robot.lift.Lower();
    }
    // If neither L2 nor L1 is pressed.
    // Stop the arm to hold it in its current position.
    else {
        robot.lift.StopArm();
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
    // If pressed, spin intake forward with full power (100%)
    if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
        robot.intake.Intake(127);
    }
    // Check if the R2 button is pressed.
    // If pressed, spin intake backward with full power (100%)
    else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
        robot.intake.Intake(127);

    }
    // If neither R1 nor R2 is pressed.
    // Stop intake and coast.
    else {
        robot.intake.StopIntake();
    }
}

/**
 * @brief Executes the Driver Control (opcontrol) tasks while the robot is enabled.
 *
 * This function runs in an infinite loop while the robot is under operator control.
 * It handles the control of the drivetrain, mobile goal clamp, arm, and intake systems.
 */
void opcontrol() {

    // Let Drivetrain motors coast when stopped
    robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);

    //ui.DisplayMatchImage();

    while (true) {
        DrivetrainDriverControl();
        MogoClampDriverControl();
        ArmDriverControl();
        IntakeDriverControl();
        DoinkerDriverControl();

        // Small delay
        delay(25);
    }
}