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
void disabled()
{
    ui.DisplayAutonSelectorUI();
        robotDevices.chassis.calibrate(); // calibrate sensors
}

// initialize function. Runs on program startup
void initialize() {
    /*

delay(4000);*/
}


pros::Task *prepArmTask = nullptr;

// Constants for PID
const double tolerance = 400.0;
const double kP = 0.01; // Proportional constant
const double kI = 0;     // Integral constant
const double kD = 0;     // Derivative constant

// Target position in ticks
const double targetPosition = 33800.0;

// Maximum and minimum motor power limits
const double maxPower = 100.0;
const double minPower = -100.0;
void prepArm(void *param)
{

    // Set brake modes
    c::motor_set_brake_mode(17, E_MOTOR_BRAKE_HOLD);

    // PID variables
    double error = 0.0;      // Difference between target and current position
    double lastError = 0.0;  // Error from the previous loop
    double integral = 0.0;   // Sum of all previous errors (I term)
    double derivative = 0.0; // Rate of change of error (D term)
    double motorPower = 0.0; // Motor power output

    while (true)
    {

        // Current position of the arm
        double currentPosition = robotDevices.liftRotation.get_position();
        if (currentPosition < 10000.0)
        {
            robotDevices.liftRotation.set_position(35800.0);
        }
        master.print(0, 0, "Pos: %.2f", currentPosition); // Calculate PID components
        error = targetPosition - currentPosition;         // Proportional term
        integral += error;                                // Integral term
        derivative = error - lastError;                   // Derivative term

        // Compute motor power using PID formula
        motorPower = (kP * error) + (kI * integral) + (kD * derivative);

        // Constrain motor power to max/min limits
        motorPower = std::clamp(motorPower, minPower, maxPower);

        // Move motors with calculated power
        c::motor_move(17, motorPower); // Adjust motor 17 (opposite direction)

        // Break if the arm is within the tolerance range
        if (fabs(error) <= tolerance)
        {
            // break;
        }

        // Update last error
        lastError = error;

        // Delay to prevent overloading the CPU
        pros::delay(10);
    }

    // Print "bruh" to indicate end of function
    master.rumble(".-");

    // Stop the motors
    c::motor_move(17, 0);
}

// Wrapper functions to start tasks
void startPrepArmTask()
{
    // Ensure the task is not already running
    if (prepArmTask == nullptr)
    {
        prepArmTask = new pros::Task(prepArm, nullptr, "Prep Arm Task");
    }
}

// Function to stop the task
void stopPrepArmTask()
{
    if (prepArmTask != nullptr)
    {
        prepArmTask->remove(); // Forcefully terminate the task
        delete prepArmTask;    // Clean up the task object
        prepArmTask = nullptr; // Reset the pointer
    }
}

/*** @brief Load paths. */
ASSET(skills1_txt);
ASSET(skills2_txt);
ASSET(skills3_txt);
ASSET(skills4_txt);
ASSET(skills5_txt);
ASSET(skills6_txt);
ASSET(skills7_txt);
ASSET(skills8_txt);
ASSET(skills9_txt);
ASSET(skills10_txt);
ASSET(skills11_txt);
ASSET(skills12_txt);
ASSET(skills13_txt);
ASSET(skills14_txt);
ASSET(skills15_txt);
ASSET(skills16_txt);
ASSET(skills17_txt);
ASSET(skills18_txt);
ASSET(skills19_txt);
ASSET(skills20_txt);
ASSET(skills21_txt);
ASSET(skills22_txt);
ASSET(skills23_txt);
ASSET(skills24_txt);
ASSET(skills25_txt);
ASSET(skills26_txt);


ASSET(soloblue1_txt);
ASSET(soloblue2_txt);
ASSET(soloblue22_txt);
ASSET(soloblue3_txt);
ASSET(soloblue33_txt);

ASSET(soloblue4_txt);
ASSET(soloblue6_txt);
ASSET(soloblue5_txt);
ASSET(soloblue55_txt);

ASSET(soloblue66_txt);
ASSET(soloblue7_txt);
ASSET(soloblue8_txt);
ASSET(soloblue9_txt);
ASSET(soloblue10_txt);
ASSET(soloblue11_txt);

ASSET(solored1_txt);
ASSET(solored2_txt);
ASSET(solored3_txt);
ASSET(solored5_txt);
ASSET(solored22_txt);
ASSET(solored4_txt);
ASSET(solored55_txt);
ASSET(solored555_txt);

ASSET(solored66_txt);
ASSET(solored77_txt);
ASSET(solored8_txt);
ASSET(solored9_txt);
ASSET(solored10_txt);
ASSET(solored11_txt);
ASSET(solored33_txt);



ASSET(redrush1_txt);
ASSET(redrush2_txt);
ASSET(redrush3_txt);
ASSET(redrush4_txt);
ASSET(redrush44_txt);
ASSET(redrush5_txt);
ASSET(redrush555_txt);
ASSET(redrush66_txt);
ASSET(redrush77_txt);
ASSET(redrush8_txt);
ASSET(redrush6_txt);
ASSET(redrush7_txt);

ASSET(bluerush1_txt);
ASSET(bluerush2_txt);
ASSET(bluerush3_txt);
ASSET(bluerush44_txt);
ASSET(bluerush66_txt);
ASSET(bluerush77_txt);
ASSET(bluerush4_txt);
ASSET(bluerush5_txt);
ASSET(bluerush6_txt);
ASSET(bluerush7_txt);
ASSET(bluerush8_txt);

/**
 * @brief Runs Autonomous period functions.
 */
void autonomous()
{
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
    });


    robotDevices.liftRotation.set_position(359);

    // Retrieve the selected autonomous mode from the BrainUI.
    int selectedMode = ui.selectedAuton;

    selectedMode = 2;
    // Blue Right - 0 BLUE SOLO
    // Blue Left - 1 RED GOAL RUSH
    // Red left - 2 RED SOLO ///////////////////////
    // Red Right - 3 BLUE GOAL RUSH

    // Determine which autonomous routine to execute based on the selected mode.
    switch (selectedMode)
    {
    case 0:

        // delay(1500);
        robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.chassis.setPose(60.491, 11.661, 150);
        c::motor_move(17, -127);
        delay(650);
        c::motor_move(17, 0);

        
        robotDevices.mogoClampPiston.set_value(true);
        robotDevices.chassis.follow(soloblue1_txt, 15, 1000, false);
        robotDevices.chassis.waitUntilDone();
         c::motor_move(17, 127);

                robotDevices.chassis.turnToHeading(104, 600);
        robotDevices.chassis.waitUntilDone();

                        c::motor_move(17, 0);

        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(soloblue2_txt, 15, 1000, false);
        robotDevices.chassis.waitUntilDone();
        delay(100);
        robotDevices.mogoClampPiston.set_value(false);
        delay(200);

        
        robotDevices.chassis.turnToHeading(330, 800);
        robotDevices.chassis.waitUntilDone();

        
        c::motor_move(5, -127);
        c::motor_move(18, -127);

        
        robotDevices.chassis.follow(soloblue3_txt, 20, 3000, true);
        robotDevices.chassis.waitUntilDone();
        delay(250);

                robotDevices.chassis.follow(soloblue33_txt, 20, 3000, false);
                        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.turnToHeading(7, 700);

                        robotDevices.chassis.waitUntilDone();

        robotDevices.chassis.follow(soloblue4_txt, 20, 3000, true);
        robotDevices.chassis.waitUntilDone();
delay(100);
                robotDevices.chassis.turnToHeading(160, 900);
        robotDevices.chassis.waitUntilDone();
        robotDevices.ringStopperPiston.set_value(true);

                        robotDevices.chassis.follow(soloblue5_txt, 20, 3000, true);
        robotDevices.chassis.waitUntilDone();
        delay(500);

                        robotDevices.chassis.turnToHeading(270, 900);

                                                robotDevices.chassis.follow(soloblue55_txt, 20, 3000, true);


        //HERE 
        /*
        robotDevices.mogoClampPiston.set_value(true);
        delay(600);
        c::motor_move(5, 0);
        c::motor_move(18, 0);

                        robotDevices.chassis.turnToHeading(60, 900);
        robotDevices.chassis.waitUntilDone();*/








        /*
                c::motor_move(5, 0);
        c::motor_move(18, 0);
                robotDevices.chassis.turnToHeading(262, 900);
                        robotDevices.chassis.waitUntilDone();

        robotDevices.doinker.set_value(true);
        delay(500);
                robotDevices.chassis.follow(soloblue5_txt, 30, 3000, false);
                        robotDevices.chassis.waitUntilDone();
                robotDevices.chassis.turnToHeading(200, 600);
                                        robotDevices.chassis.waitUntilDone();

                        robotDevices.doinker.set_value(false);
delay(200);
                robotDevices.chassis.turnToHeading(175, 600);
                                        robotDevices.chassis.waitUntilDone();
                c::motor_move(5, -127);
        c::motor_move(18, -127);
                robotDevices.chassis.follow(soloblue6_txt, 30, 3000, true);
                                        robotDevices.chassis.waitUntilDone();
        delay(100);
                                robotDevices.ringStopperPiston.set_value(true);
delay(100);
                        robotDevices.chassis.follow(soloblue7_txt, 30, 3000, true);
                                        robotDevices.chassis.waitUntilDone();
                                                robotDevices.chassis.swingToHeading(290, DriveSide::RIGHT, 1000);
                                                                                        robotDevices.chassis.waitUntilDone();

        c::motor_move(17, -127);
        delay(600);
*/
/*
        robotDevices.chassis.swingToHeading(20, DriveSide::RIGHT, 1000);
        delay(100);
        robotDevices.chassis.swingToHeading(270, DriveSide::RIGHT, 1000);

        delay(50);
        
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.turnToHeading(45, 600);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(soloblue3_txt, 15, 3000, true);
        robotDevices.chassis.waitUntilDone();
        delay(500);
        c::motor_move(5, 0);
        c::motor_move(18, -127);
        robotDevices.chassis.turnToHeading(160, 600);
        robotDevices.chassis.waitUntilDone();
        robotDevices.ringStopperPiston.set_value(true);
        c::motor_move(5, -127);

        robotDevices.chassis.follow(soloblue4_txt, 15, 3000, true);
        robotDevices.chassis.waitUntilDone();

        robotDevices.ringStopperPiston.set_value(false);
        delay(350);
        robotDevices.ringStopperPiston.set_value(true);
        robotDevices.chassis.turnToHeading(350, 800);
        robotDevices.chassis.waitUntilDone();
        robotDevices.ringStopperPiston.set_value(false);
*/
        // LADDER TOUCH 
        /*
        robotDevices.chassis.follow(soloblue5_txt, 20, 600, true);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, -127);*/

        break;
    case 1:

        robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.chassis.setPose(0, 0, 0);
        c::motor_move(5, -127);
        c::motor_move(18, -127);
        robotDevices.chassis.moveToPoint(-0.289, 30.38, 4000, {.forwards = true, .maxSpeed = 90, .minSpeed = 70});
        robotDevices.chassis.waitUntilDone();
        robotDevices.doinker.set_value(true);
        //delay

        robotDevices.chassis.moveToPoint(-0.289, 25.00, 4000, {.forwards = false, .maxSpeed = 90, .minSpeed = 40});
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.turnToHeading(75, 800);

        delay(3000);
        robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);

/*
        c::motor_move(5, -127);
        delay(100);
        robotDevices.chassis.follow(redrush77_txt, 10, 2000, false);
        robotDevices.chassis.waitUntilDone();

        robotDevices.chassis.follow(redrush8_txt, 10, 2000, true);
*/
        /* robotDevices.chassis.turnToHeading(180, 700);
         robotDevices.chassis.waitUntilDone();

         robotDevices.chassis.follow(redrush5_txt, 20, 2000, false);
         robotDevices.chassis.waitUntilDone();
         robotDevices.mogoClampPiston.set_value(false);
         delay(200);
         robotDevices.chassis.turnToHeading(320, 1000);
         robotDevices.chassis.waitUntilDone();
                     c::motor_move(5, -127);
         c::motor_move(18, -127);
         robotDevices.ringStopperPiston.set_value(true);
         robotDevices.chassis.follow(redrush6_txt, 20, 2000, true);
         robotDevices.chassis.waitUntilDone();
         robotDevices.ringStopperPiston.set_value(false);
         delay(300);
         robotDevices.chassis.follow(redrush7_txt, 20, 2000, false);
                     robotDevices.chassis.waitUntilDone();

                     robotDevices.chassis.turnToHeading(45, 700);
                     robotDevices.chassis.waitUntilDone();
         c::motor_move(17, -127);*/

        break;

    case 2:
 
        // delay(1500);
        robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.chassis.setPose(-60.491, 11.661, 210);
        c::motor_move(17, -127);
        delay(650);
        c::motor_move(17, 0);

        
        robotDevices.mogoClampPiston.set_value(true);
        robotDevices.chassis.follow(solored1_txt, 15, 1000, false);
        robotDevices.chassis.waitUntilDone();
         c::motor_move(17, 127);

                robotDevices.chassis.turnToHeading(256, 600);
        robotDevices.chassis.waitUntilDone();

                        c::motor_move(17, 0);

        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(solored2_txt, 15, 1000, false);
        robotDevices.chassis.waitUntilDone();
        delay(100);
        robotDevices.mogoClampPiston.set_value(false);
        delay(200);

        
        robotDevices.chassis.turnToHeading(30, 800);
        robotDevices.chassis.waitUntilDone();

        
        c::motor_move(5, -127);
        c::motor_move(18, -127);

        
        robotDevices.chassis.follow(solored3_txt, 20, 3000, true);
        robotDevices.chassis.waitUntilDone();
        delay(250);

                robotDevices.chassis.follow(solored33_txt, 20, 3000, false);
                        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.turnToHeading(353, 700);

                        robotDevices.chassis.waitUntilDone();

        robotDevices.chassis.follow(solored4_txt, 20, 3000, true);
        robotDevices.chassis.waitUntilDone();
delay(100);
                robotDevices.chassis.turnToHeading(200, 900);
        robotDevices.chassis.waitUntilDone();
        robotDevices.ringStopperPiston.set_value(true);

                        robotDevices.chassis.follow(solored5_txt, 20, 3000, true);
        robotDevices.chassis.waitUntilDone();
        delay(500);

                        robotDevices.chassis.turnToHeading(90, 900);

                                                robotDevices.chassis.follow(solored55_txt, 20, 3000, true);

//HERE



        /*
        robotDevices.chassis.follow(solored6_txt, 20, 4000, true);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.swingToHeading(160, DriveSide::LEFT, 600);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.swingToHeading(200, DriveSide::LEFT, 1000);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(solored7_txt, 20, 4000, true);

        // SPLIT IN HALF

        /*
        robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(true);
        delay(400);
        robotDevices.chassis.follow(solored8_txt, 20, 4000, true);
        robotDevices.chassis.waitUntilDone();
        delay(275);
        c::motor_move(5, -5);
        c::motor_move(18, -5);
        delay(100);
        robotDevices.chassis.turnToHeading(280, 700);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(solored9_txt, 20, 1500, false);
        robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(false);
        delay(100);
        robotDevices.chassis.turnToHeading(180, 600);
        c::motor_move(5, -127);
        c::motor_move(18, -127);
        robotDevices.chassis.follow(solored10_txt, 20, 1500, true);
        robotDevices.chassis.waitUntilDone();
        robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST); robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST); robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST); robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.chassis.follow(solored11_txt, 20, 1500, false);
        */

        break;
    case 3:

        robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.chassis.setPose(61.949, -10.689, 35);

        c::motor_move(17, -127);
        delay(600);

        robotDevices.mogoClampPiston.set_value(true);
        robotDevices.chassis.follow(bluerush1_txt, 25, 4000, false);
                c::motor_move(17, 45);

        robotDevices.chassis.waitUntilDone();
                c::motor_move(17, 0);

        robotDevices.mogoClampPiston.set_value(false);
        delay(300);
        robotDevices.chassis.turnToHeading(310, 800);

        robotDevices.chassis.follow(bluerush2_txt, 20, 3000, true);
        robotDevices.chassis.waitUntilDone();
                robotDevices.chassis.turnToHeading(338, 800);
                        robotDevices.chassis.waitUntilDone();


        robotDevices.doinker.set_value(true);
delay(300);
        robotDevices.chassis.turnToHeading(270, 800);

        robotDevices.chassis.waitUntilDone();
                robotDevices.chassis.follow(bluerush3_txt, 30, 3000, false);
        robotDevices.chassis.waitUntilDone();

        robotDevices.doinker.set_value(false);

        c::motor_move(5, -127);
        c::motor_move(18, -127);
        robotDevices.chassis.turnToHeading(261, 1000);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(bluerush44_txt, 15, 3000, true);
        robotDevices.chassis.waitUntilDone();
                robotDevices.chassis.turnToHeading(180, 1000);
        robotDevices.chassis.waitUntilDone();


        robotDevices.chassis.follow(bluerush66_txt, 15, 1000, true);
        robotDevices.chassis.waitUntilDone();
                        robotDevices.chassis.turnToHeading(25, 1000);
        robotDevices.chassis.waitUntilDone();
                robotDevices.ringStopperPiston.set_value(true);
        robotDevices.chassis.follow(bluerush77_txt, 15, 3000, true);
                robotDevices.chassis.waitUntilDone();

                        robotDevices.ringStopperPiston.set_value(false);
                        delay(300);
                                                robotDevices.ringStopperPiston.set_value(true);





        /*
        robotDevices.chassis.waitUntilDone();
        robotDevices.ringStopperPiston.set_value(false);
        delay(200);

        robotDevices.chassis.turnToHeading(270, 700);
        robotDevices.chassis.waitUntilDone();

        //robotDevices.chassis.turnToHeading(150, 1000);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(bluerush77_txt, 15, 800, true);
        robotDevices.chassis.waitUntilDone();



*/
        /*
        robotDevices.chassis.follow(bluerush4_txt, 15, 1000, true);
        robotDevices.chassis.waitUntilDone();
        delay(1500);
        c::motor_move(5, 0);
        c::motor_move(18, 0);
        robotDevices.mogoClampPiston.set_value(true);
        delay(250);
        robotDevices.chassis.turnToHeading(180, 700);
        robotDevices.chassis.waitUntilDone();

        robotDevices.chassis.follow(bluerush5_txt, 15, 1000, false);
        robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(false);
        delay(250);
        robotDevices.chassis.turnToHeading(40, 700);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(5, -127);
        c::motor_move(18, -127);
        robotDevices.ringStopperPiston.set_value(true);
        robotDevices.chassis.follow(bluerush6_txt, 20, 2000, true);
robotDevices.chassis.waitUntilDone();
        robotDevices.ringStopperPiston.set_value(false);
        delay(500);
        robotDevices.chassis.follow(bluerush7_txt, 20, 2000, false);
                    robotDevices.chassis.waitUntilDone();

                    robotDevices.chassis.turnToHeading(-45, 700);
                    robotDevices.chassis.waitUntilDone();
        c::motor_move(17, -127);
/*
        robotDevices.ringStopperPiston.set_value(false);
        delay(1);
        robotDevices.chassis.turnToHeading(180, 1000);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(bluerush8_txt, 20, 2000, true);
        robotDevices.chassis.waitUntilDone();*/
        break;

    case 4:

        robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.chassis.setPose(-61, 0, 270);

        // SCORE ALLIANCE STAKE
        c::motor_move(17, -127);
        delay(500);
        c::motor_move(17, 127);
        delay(400);
        c::motor_move(17, 0);

        // ALIGN WITH FIRST GOAL
        robotDevices.chassis.follow(skills1_txt, 20, 2000, false);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.turnToHeading(356, 700);
        robotDevices.chassis.waitUntilDone();

        

        // Approach first goal and clamp, then align with and face ring
        robotDevices.mogoClampPiston.set_value(true);
        robotDevices.chassis.follow(skills2_txt, 20, 2000, false);
        robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(false);
        delay(300);

        
        robotDevices.chassis.turnToHeading(86.25, 700);

        // Approach ring and intake
        c::motor_move(5, -127);
        c::motor_move(18, -127);
        robotDevices.chassis.follow(skills3_txt, 20, 2000, true);
        robotDevices.chassis.waitUntilDone();
        delay(100);
        
        robotDevices.chassis.turnToHeading(135, 700);
        robotDevices.chassis.waitUntilDone();

        robotDevices.chassis.follow(skills4_txt, 20, 2000, true);
        robotDevices.chassis.waitUntilDone();
        delay(200);

        // Back up, align with stake, prep lady brown, intake, score on stake
        robotDevices.chassis.turnToHeading(120, 700);
        robotDevices.chassis.waitUntilDone();
        
        robotDevices.chassis.follow(skills5_txt, 20, 2000, false);
        robotDevices.chassis.waitUntilDone();
        
        startPrepArmTask();
        robotDevices.chassis.turnToHeading(178, 700);
        robotDevices.chassis.waitUntilDone();
        
        robotDevices.chassis.follow(skills6_txt, 20, 2300, true);
        delay(1500);
        
        c::motor_move(5, 30);
        c::motor_move(18, 30);
        stopPrepArmTask();
        c::motor_move(17, -127);
        delay(900);
        c::motor_move(17, 0);
        
        // Back up from wall stake, align with 3 rings
        robotDevices.chassis.follow(skills7_txt, 20, 8000, false);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 127);
        delay(500);
        c::motor_move(17, 0);

        // Face 3 rings, intake
        robotDevices.chassis.turnToHeading(265, 700);
        robotDevices.chassis.waitUntilDone();

        c::motor_move(5, -127);
        c::motor_move(18, -127);
        robotDevices.chassis.follow(skills8_txt, 20, 4000, true);
        robotDevices.chassis.waitUntilDone();
        delay(250);

        // Face fourth ring, intake
        robotDevices.chassis.turnToHeading(153, 700);
        robotDevices.chassis.waitUntilDone();

        robotDevices.chassis.follow(skills9_txt, 20, 4000, true);
        robotDevices.chassis.waitUntilDone();

        // Maneuver to corner and drop goal
        robotDevices.chassis.swingToHeading(355, DriveSide::RIGHT, 1000);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(5, 127);
        c::motor_move(18, 127);
        robotDevices.mogoClampPiston.set_value(true);
        delay(400);
        robotDevices.chassis.swingToHeading(170, DriveSide::RIGHT, 500);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.swingToHeading(185, DriveSide::RIGHT, 400);

        // Align with next goal
        c::motor_move(5, 0);
        c::motor_move(18, 0);
        robotDevices.chassis.turnToHeading(177, 700);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(skills12_txt, 45, 6000, false);
        robotDevices.chassis.waitUntilDone();
        
        // delay(300);
        robotDevices.mogoClampPiston.set_value(false);
        delay(300);

        // FACE OTHER RING
        robotDevices.chassis.turnToHeading(93, 700);
        robotDevices.chassis.waitUntilDone();

        c::motor_move(5, -127);
        c::motor_move(18, -127);
        robotDevices.chassis.follow(skills13_txt, 20, 6000, true);
        robotDevices.chassis.waitUntilDone();
        
        robotDevices.chassis.turnToHeading(40, 700);
        robotDevices.chassis.waitUntilDone();
        
        robotDevices.chassis.follow(skills14_txt, 25, 6000, true);
        robotDevices.chassis.waitUntilDone();
        
        delay(250);

        robotDevices.chassis.turnToHeading(60, 700);

        robotDevices.chassis.follow(skills15_txt, 20, 6000, false);
        robotDevices.chassis.waitUntilDone();
        
        robotDevices.chassis.turnToHeading(5, 700);

        robotDevices.chassis.waitUntilDone();
        
        startPrepArmTask();
        delay(100);
        robotDevices.chassis.follow(skills16_txt, 20, 1600, true);
        robotDevices.chassis.waitUntilDone();
        delay(400);
        c::motor_move(5, 15);
        c::motor_move(18, 15);
        stopPrepArmTask();
        c::motor_move(17, -127);
        delay(600);
        c::motor_move(17, 0);
        //delay(100);

        robotDevices.chassis.follow(skills17_txt, 20, 3000, false);
        robotDevices.chassis.waitUntilDone();

        c::motor_move(17, 127);
        delay(600);
        c::motor_move(17, 0);
        robotDevices.chassis.turnToHeading(270, 700);
        robotDevices.chassis.waitUntilDone();

        // HERE 

        
        c::motor_move(5, -127);
        c::motor_move(18, -127);
        robotDevices.chassis.follow(skills18_txt, 20, 3000, true);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.turnToHeading(25, 700);
        robotDevices.chassis.follow(skills19_txt, 20, 3000, true);
        robotDevices.chassis.waitUntilDone();
        delay(500);

        robotDevices.chassis.swingToHeading(160, DriveSide::LEFT, 1000);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(5, 127);
        c::motor_move(18, 127);
        robotDevices.chassis.waitUntilDone();
                robotDevices.mogoClampPiston.set_value(true);

        delay(250);
        
        robotDevices.chassis.follow(skills21_txt, 20, 3000, true);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.turnToHeading(90, 700);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(skills22_txt, 35, 3000, true);
        
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.turnToHeading(0, 700);
                robotDevices.chassis.waitUntilDone();


                
        robotDevices.chassis.waitUntilDone();

        robotDevices.chassis.follow(skills23_txt, 20, 3000, false);
        robotDevices.chassis.waitUntilDone();
                        robotDevices.mogoClampPiston.set_value(false);
delay(200);
                robotDevices.chassis.turnToHeading(190, 700);
                        robotDevices.chassis.waitUntilDone();
delay(200);
        c::motor_move(5, -127);
        c::motor_move(18, -127);
                robotDevices.chassis.follow(skills24_txt, 55, 3000, true);
                                        robotDevices.chassis.waitUntilDone();

                robotDevices.chassis.turnToHeading(310, 700);
                                        robotDevices.chassis.waitUntilDone();
                robotDevices.chassis.follow(skills25_txt, 60, 3000, true);
                                                        robotDevices.chassis.waitUntilDone();
                robotDevices.chassis.turnToHeading(45, 700);
                                                                        robotDevices.chassis.waitUntilDone();
                robotDevices.chassis.follow(skills26_txt, 60, 3000, true);



        /*

        
        robotDevices.chassis.turnToHeading(180, 700);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.follow(skills24_txt, 20, 3000, false);
        robotDevices.chassis.waitUntilDone();

        robotDevices.chassis.follow(skills25_txt, 20, 3000, true);
*/
        break;
    }
}

/**
 * @brief Runs when initialized by VEX Field Controller.
 */
void competition_initialize()
{
    robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);

    robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    robotDevices.liftMotor.tare_position();
    // Start calibration for both inertial sensors
    robotDevices.imu.reset();
    robotDevices.imu2.reset();

    pros::lcd::initialize();          // initialize brain screen
    robotDevices.chassis.calibrate(); // calibrate sensors

    // Draws autonomous selector UI on the Brain using LVGL,
    // an industry standard micro-controller screen UI library.
    //ui.DisplayAutonSelectorUI();
}

/**
 * @brief Manages the drivetrain controls during the Driver Control period.
 *
 * This function reads the analog inputs from the controller to control the robot's drivetrain
 * using a "tank drive" configuration. The tank drive configuration separates control of the left
 * and right wheels, where each joystick controls one side of the drivetrain.
 */
void DrivetrainDriverControl()
{

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
void MogoClampDriverControl()
{

    // Check if the Y button is pressed on the controller.
    // If pressed, activate the clamp to secure the mobile goal.
    if (master.get_digital(E_CONTROLLER_DIGITAL_L1))
    {
        robotDevices.mogoClampPiston.set_value(true);
    }
    else
    {
        robotDevices.mogoClampPiston.set_value(false);
    }

    if (master.get_digital(E_CONTROLLER_DIGITAL_X))
    {
        robotDevices.ringStopperPiston.set_value(false);
    }


}

/**
 * @brief Controls the mobile goal clamp during the Driver Control period.
 *
 * This function manages the mobile goal clamp based on controller button inputs:
 * - Pressing the Y button will activate the clamp.
 * - Pressing the Right button will deactivate the clamp (release it).
 */
void RingStopperDriverControl()
{

    // Check if the Y button is pressed on the controller.
    // If pressed, activate the clamp to secure the mobile goal.
    if (master.get_digital(E_CONTROLLER_DIGITAL_B))
    {
        robotDevices.doinker.set_value(true);
    }

    // Check if the Right button is pressed on the controller.
    // If pressed, deactivate the clamp to release the mobile goal.
    if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN))
    {
        robotDevices.doinker.set_value(false);
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
void LiftDriverControl()
{

    if (master.get_digital(E_CONTROLLER_DIGITAL_L2))
    {
        startPrepArmTask();
    }

    // Check if the L2 button is pressed.
    // If pressed, command the lift to rise.
    if (master.get_digital(E_CONTROLLER_DIGITAL_Y))
    {
        stopPrepArmTask();
        c::motor_move(17, -127);
        c::motor_move(18, -127);
    }
    // Check if the L1 button is pressed.
    // If pressed and L2 is not pressed, command the lift to lower.
    else if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT))
    {
        stopPrepArmTask();
        c::motor_move(17, 127);
    }
    // If neither L2 nor L1 is pressed.
    // Stop the lift to hold it in its current position.
    else
    {
        robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        c::motor_move(17, 0);
        c::motor_move(19, 0);
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
void IntakeDriverControl()
{

    // Check if the R1 button is pressed.
    // If pressed, command the intake to spin forward with full power (100%).
    if (master.get_digital(E_CONTROLLER_DIGITAL_R1))
    {
        c::motor_move(18, -127);
        c::motor_move(5, -127);
    }
    // Check if the R2 button is pressed.
    // If pressed and R1 is not pressed, command the intake to spin backward with full power (100%).
    else if (master.get_digital(E_CONTROLLER_DIGITAL_R2))
    {
        c::motor_move(5, 127);
        c::motor_move(18, 127);
    }
    // If neither R1 nor R2 is pressed.
    // Command the intake to stop and coast.
    else
    {
        c::motor_move(18, 0);
        c::motor_move(5, 0);
        robot.intake.StopIntake();
    }
}
/**
 * @brief Executes the Driver Control (opcontrol) tasks while the robot is enabled.
 *
 * This function runs in an infinite loop while the robot is under operator control.
 * It handles the control of the drivetrain, mobile goal clamp, lift, and intake systems.
 */
void opcontrol()
{

    // ui.DisplayMatchImage();
                robotDevices.ringStopperPiston.set_value(false);

    while (true)
    {

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