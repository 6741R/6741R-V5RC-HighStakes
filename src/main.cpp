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
 //   ui.DisplayAutonSelectorUI();
        robotDevices.chassis.calibrate(); // calibrate sensors
}

// initialize function. Runs on program startup
void initialize() {
    /*

delay(4000);*/
}


pros::Task *prepArmTask = nullptr;

// Constants for PID
const double tolerance = 200.0;
const double kP = 0.018; // Proportional constant
const double kI = 0;     // Integral constant
const double kD = 0.01;     // Derivative constant

// Target position in ticks
const double targetPosition = 33600.0;


// Maximum and minimum motor power limits
const double maxPower = 100.0;
const double minPower = -100.0;
void prepArm(void *param)
{
            double currentPosition = robotDevices.liftRotation.get_position();


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
         currentPosition = robotDevices.liftRotation.get_position();
        if (currentPosition < 10000.0)
        {
            robotDevices.liftRotation.set_position(35200.0);
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
    c::motor_set_brake_mode(17, E_MOTOR_BRAKE_HOLD);

    // Stop the motors
    c::motor_move(17, 0);
}


const double atargetPosition = 29000.0;

pros::Task *aprepArmTask = nullptr;

// Constants for PID
const double atolerance = 400.0;
const double akP = 0.018; // Proportional constant
const double akI = 0;     // Integral constant
const double akD = 0.01;     // Derivative constant

// Maximum and minimum motor power limits
const double amaxPower = 100.0;
const double aminPower = -100.0;
void aprepArm(void *param)
{
            double currentPosition = robotDevices.liftRotation.get_position();


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
         currentPosition = robotDevices.liftRotation.get_position();
        if (currentPosition < 10000.0)
        {
            robotDevices.liftRotation.set_position(35200.0);
        }
        master.print(0, 0, "Pos: %.2f", currentPosition); // Calculate PID components
        error = atargetPosition - currentPosition;         // Proportional term
        integral += error;                                // Integral term
        derivative = error - lastError;                   // Derivative term

        // Compute motor power using PID formula
        motorPower = (akP * error) + (akI * integral) + (akD * derivative);

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
    c::motor_set_brake_mode(17, E_MOTOR_BRAKE_HOLD);

    // Stop the motors
    c::motor_move(17, 0);
}

// Wrapper functions to start tasks
void astartPrepArmTask()
{
    // Ensure the task is not already running
    if (aprepArmTask == nullptr)
    {
        aprepArmTask = new pros::Task(aprepArm, nullptr, "APrep Arm Task");
    }
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
void astopPrepArmTask()
{
    if (aprepArmTask != nullptr)
    {
        aprepArmTask->remove(); // Forcefully terminate the task
        delete aprepArmTask;    // Clean up the task object
        aprepArmTask = nullptr; // Reset the pointer
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


    //robotDevices.liftRotation.set_position(33200.0);

    // Retrieve the selected autonomous mode from the BrainUI.
    int selectedMode = ui.selectedAuton;

    selectedMode = 5;
    // Blue Right - 0 Blue SOLO AWP done
    // Blue Left - 1 Red GOAL RUSH 
    // Red left - 2 Red SOLO AWP done
    // Red Right - 3 Blue GOAL RUSH

    // Determine which autonomous routine to execute based on the selected mode.
    switch (selectedMode)
    {
    case 0:

        robotDevices.liftRotation.set_position(33400.0);

        // Face Alliance Stake and score
        robotDevices.chassis.turnToHeading(50.75, 800);
        c::motor_move(17, -55);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 0);
        robotDevices.mogoClampPiston.set_value(true);

        // Grab goal
        robotDevices.chassis.moveToPoint(-10, -28, 1500, {.forwards = false, .maxSpeed = 90, .minSpeed = 30});
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 45);
        robotDevices.mogoClampPiston.set_value(false);

        // Face 4 rings
        robotDevices.chassis.turnToHeading(-135, 1000);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 0);
        c::motor_move(18, -127);
        c::motor_move(5, -127);

        // Align with 4 rings
        robotDevices.chassis.moveToPoint(-21, -45, 1500, {.forwards = true, .maxSpeed = 90, .minSpeed = 30});
        robotDevices.chassis.waitUntilDone();

        // Face 4 rings
        robotDevices.chassis.turnToHeading(-90, 700);
        robotDevices.chassis.waitUntilDone();

        // Intake 2 rings
        robotDevices.chassis.moveToPoint(-29.75, -45.4, 1500, {.forwards = true, .maxSpeed = 90, .minSpeed = 55});
        robotDevices.chassis.waitUntilDone();

        // Face other ring
        robotDevices.chassis.turnToHeading(1, 700);
        robotDevices.chassis.waitUntilDone();

        // Intake other ring
        robotDevices.chassis.moveToPoint(-30, -37.25, 1500, {.forwards = true, .maxSpeed = 90, .minSpeed = 55});
        robotDevices.chassis.waitUntilDone();
        //delay(80);
        c::motor_move(5, 127);

        // Face goal towards wall
        robotDevices.chassis.turnToHeading(-130, 700);
        robotDevices.chassis.waitUntilDone();

        // Back up to align with stacked ring
        robotDevices.chassis.moveToPoint(-20, -23, 1500, {.forwards = false, .maxSpeed = 90, .minSpeed = 55});
        robotDevices.chassis.waitUntilDone();

        // Face stacked ring
        robotDevices.chassis.turnToHeading(95, 700);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(5, -127);
        c::motor_move(18, -110);
        robotDevices.mogoClampPiston.set_value(true);

        // Intakee stacked ring
        robotDevices.chassis.moveToPoint(23, -22.75, 3000, {.forwards = true, .maxSpeed = 65, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();
        c::motor_move(18, 0);
        c::motor_move(5, -127);

        // face second goal
        robotDevices.chassis.turnToHeading(-5, 700);
        robotDevices.chassis.waitUntilDone();

        // grab second goal
        robotDevices.chassis.moveToPoint(23, -36, 3000, {.forwards = false, .maxSpeed = 65, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(false);
        delay(100);

        // Face other ring
        robotDevices.chassis.turnToHeading(90, 700);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(18, -127);
        c::motor_move(5, -127);

        // Intake other ring
        robotDevices.chassis.moveToPoint(38, -34, 3000, {.forwards = true, .maxSpeed = 65, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();
        delay(500);
        c::motor_move(17, -25);

        // Touch ladder
        robotDevices.chassis.moveToPoint(10, -40, 1500, {.forwards = false, .maxSpeed = 65, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 0);

                        astopPrepArmTask();


        break;
    case 1:
        robotDevices.liftRotation.set_position(33400.0);

        robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    c::motor_set_brake_mode(17, E_MOTOR_BRAKE_HOLD);



        //c::motor_move(18, -30);
        c::motor_move(5, -127);
        astartPrepArmTask();

        robotDevices.doinker.set_value(true);
        robotDevices.chassis.moveToPoint(4, 26.5, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110});
        robotDevices.chassis.waitUntilDone();
        robotDevices.doinker.set_value(false);

        robotDevices.chassis.moveToPoint(4, 16, 8000, {.forwards = false, .maxSpeed = 80, .minSpeed = 40});
                robotDevices.chassis.waitUntilDone();

        robotDevices.doinker.set_value(true);
        delay(300);
        robotDevices.chassis.moveToPoint(4, 10, 8000, {.forwards = false, .maxSpeed = 80, .minSpeed = 40});
                        robotDevices.chassis.waitUntilDone();
        robotDevices.doinker.set_value(false);

        robotDevices.chassis.turnToHeading(167, 800);
                robotDevices.mogoClampPiston.set_value(true);

        robotDevices.chassis.moveToPoint(-0.5, 24.25, 8000, {.forwards = false, .maxSpeed = 80, .minSpeed = 40});
                                robotDevices.chassis.waitUntilDone();

        robotDevices.mogoClampPiston.set_value(false);
        delay(150);
        c::motor_move(18, -127);
        delay(150);
        robotDevices.chassis.turnToHeading(0, 800);
                                robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.moveToPoint(-2, 16, 8000, {.forwards = false, .maxSpeed = 80, .minSpeed = 40});
                                robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(true);
delay(100);
        robotDevices.chassis.turnToHeading(100, 800);
                                        robotDevices.chassis.waitUntilDone();
               c::motor_move(18, 0);
                c::motor_move(5, 0);
        robotDevices.chassis.moveToPoint(-12, 16, 8000, {.forwards = false, .maxSpeed = 80, .minSpeed = 40});
                                robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(false);

 
                delay(100);
        robotDevices.chassis.turnToHeading(215, 800);
        robotDevices.chassis.waitUntilDone();
        robotDevices.ringStopperPiston.set_value(true);
                c::motor_move(18, -127);
                c::motor_move(5, -127);


                        robotDevices.chassis.moveToPoint(-32, -10, 8000, {.forwards = true, .maxSpeed = 80, .minSpeed = 40});
        robotDevices.chassis.waitUntilDone();
        robotDevices.ringStopperPiston.set_value(false);
        delay(250);
        c::motor_move(5, 0);

        robotDevices.chassis.turnToHeading(148, 800);
                robotDevices.chassis.waitUntilDone();

                        robotDevices.chassis.moveToPoint(-30.85, -14.85, 8000, {.forwards = true, .maxSpeed = 60, .minSpeed = 20});

                       // robotDevices.chassis.moveToPoint(-25, -15, 8000, {.forwards = true, .maxSpeed = 80, .minSpeed = 40});
        
                robotDevices.chassis.waitUntilDone();
                astopPrepArmTask();
        c::motor_move(17, -127);
        delay(500);
        c::motor_move(17, 0);
                        robotDevices.chassis.moveToPoint(-38, 5, 8000, {.forwards = false, .maxSpeed = 60, .minSpeed = 20});


        delay(3000);
                robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);

                        astopPrepArmTask();

        break;

    case 2:
        
        robotDevices.liftRotation.set_position(33400.0);

        // Face Alliance Stake and score
        robotDevices.chassis.turnToHeading(-50.75, 800);
        c::motor_move(17, -55);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 0);
        robotDevices.mogoClampPiston.set_value(true);

        // Grab goal
        robotDevices.chassis.moveToPoint(10, -27, 1500, {.forwards = false, .maxSpeed = 90, .minSpeed = 30});
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 45);
        robotDevices.mogoClampPiston.set_value(false);

        // Face 4 rings
        robotDevices.chassis.turnToHeading(135, 1000);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 0);
        c::motor_move(18, -127);
        c::motor_move(5, -127);

        // Align with 4 rings
        robotDevices.chassis.moveToPoint(22, -42, 1500, {.forwards = true, .maxSpeed = 90, .minSpeed = 30});
        robotDevices.chassis.waitUntilDone();

        // Face 4 rings
        robotDevices.chassis.turnToHeading(90, 700);
        robotDevices.chassis.waitUntilDone();

        // Intake 2 rings
        robotDevices.chassis.moveToPoint(31.25, -41, 1500, {.forwards = true, .maxSpeed = 90, .minSpeed = 55});
        robotDevices.chassis.waitUntilDone();

        // Face other ring
        robotDevices.chassis.turnToHeading(-1, 700);
        robotDevices.chassis.waitUntilDone();

        // Intake other ring
        robotDevices.chassis.moveToPoint(30, -37, 1500, {.forwards = true, .maxSpeed = 90, .minSpeed = 55});
        robotDevices.chassis.waitUntilDone();
        delay(100);
        c::motor_move(5, 127);

        // Face goal towards wall
        robotDevices.chassis.turnToHeading(130, 700);
        robotDevices.chassis.waitUntilDone();

        // Back up to align with stacked ring
        robotDevices.chassis.moveToPoint(20, -18, 1500, {.forwards = false, .maxSpeed = 90, .minSpeed = 55});
        robotDevices.chassis.waitUntilDone();

        // Face stacked ring
        robotDevices.chassis.turnToHeading(-80, 700);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(5, -127);
        robotDevices.mogoClampPiston.set_value(true);
        c::motor_move(18, -90);

        // Intakee stacked ring
        robotDevices.chassis.moveToPoint(-27, -18, 3000, {.forwards = true, .maxSpeed = 65, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();
        c::motor_move(18, 0);
        c::motor_move(5, -127);

        // face second goal
        robotDevices.chassis.turnToHeading(5, 700);
        robotDevices.chassis.waitUntilDone();

        // grab second goal
        robotDevices.chassis.moveToPoint(-27, -30, 3000, {.forwards = false, .maxSpeed = 65, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(false);
        delay(100);

        // Face other ring
        robotDevices.chassis.turnToHeading(-90, 700);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(18, -127);
        c::motor_move(5, -127);

        // Intake other ring
        robotDevices.chassis.moveToPoint(-39.9, -31, 3000, {.forwards = true, .maxSpeed = 65, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();
        delay(500);
        c::motor_move(17, -25);

        // Touch ladder
        robotDevices.chassis.moveToPoint(-15, -40, 1500, {.forwards = false, .maxSpeed = 65, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 0);
                astopPrepArmTask();

        break;
    case 3:

        robotDevices.liftRotation.set_position(33400.0);

robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    c::motor_set_brake_mode(17, E_MOTOR_BRAKE_HOLD);



        //c::motor_move(18, -30);
        c::motor_move(5, -127);
        astartPrepArmTask();

        robotDevices.doinker.set_value(true);

        
        robotDevices.chassis.moveToPoint(3, 29, 3000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110});
        robotDevices.chassis.waitUntilDone();
        robotDevices.doinker.set_value(false);


        robotDevices.chassis.moveToPoint(3, 16, 8000, {.forwards = false, .maxSpeed = 80, .minSpeed = 40});
                robotDevices.chassis.waitUntilDone();

        robotDevices.doinker.set_value(true);
        delay(300);
        robotDevices.chassis.moveToPoint(3, 10, 8000, {.forwards = false, .maxSpeed = 80, .minSpeed = 40});
                        robotDevices.chassis.waitUntilDone();
        robotDevices.doinker.set_value(false);

        robotDevices.chassis.turnToHeading(167, 800);
                robotDevices.mogoClampPiston.set_value(true);

        robotDevices.chassis.moveToPoint(0, 28, 8000, {.forwards = false, .maxSpeed = 80, .minSpeed = 40});
                                robotDevices.chassis.waitUntilDone();

        robotDevices.mogoClampPiston.set_value(false);
        delay(150);
        c::motor_move(18, -127);
        delay(150);
        robotDevices.chassis.turnToHeading(0, 800);
                                robotDevices.chassis.waitUntilDone();
        
        robotDevices.chassis.moveToPoint(3, 17, 8000, {.forwards = false, .maxSpeed = 80, .minSpeed = 40});
                                robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(true);
delay(100);
        robotDevices.chassis.turnToHeading(-120, 800);
                                        robotDevices.chassis.waitUntilDone();
               c::motor_move(18, 0);
                c::motor_move(5, 0);
        robotDevices.chassis.moveToPoint(27, 30, 8000, {.forwards = false, .maxSpeed = 80, .minSpeed = 40});

                
                                robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(false);

 
                delay(100);
        robotDevices.chassis.turnToHeading(-230, 800);
        robotDevices.chassis.waitUntilDone();

        
        robotDevices.ringStopperPiston.set_value(true);
                c::motor_move(18, -127);
                c::motor_move(5, -127);


                        robotDevices.chassis.moveToPoint(54, 19, 8000, {.forwards = true, .maxSpeed = 80, .minSpeed = 40});
        robotDevices.chassis.waitUntilDone();

        
        robotDevices.ringStopperPiston.set_value(false);
        delay(250);
        c::motor_move(5, 0);

        robotDevices.chassis.turnToHeading(-189, 800);
                robotDevices.chassis.waitUntilDone();

                        robotDevices.chassis.moveToPoint(56.25, 14.1, 8000, {.forwards = true, .maxSpeed = 60, .minSpeed = 20});

                       // robotDevices.chassis.moveToPoint(-25, -15, 8000, {.forwards = true, .maxSpeed = 80, .minSpeed = 40});
        
                robotDevices.chassis.waitUntilDone();
                astopPrepArmTask();
        c::motor_move(17, -127);
        delay(500);
        c::motor_move(17, 0);

        
                        robotDevices.chassis.moveToPoint(50, 32, 8000, {.forwards = false, .maxSpeed = 60, .minSpeed = 20});


        delay(3000);
                robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
                       astopPrepArmTask();


        break;

    case 5:
        robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        robotDevices.chassis.setPose(0, 0, 0);
        robotDevices.mogoClampPiston.set_value(true);

        c::motor_move(18, -127);
        delay(250);
        c::motor_move(18, 0);
        // Align with goal
        robotDevices.chassis.moveToPoint(0, 4.1, 800, {.forwards = true, .maxSpeed = 127, .minSpeed = 110});
        robotDevices.chassis.waitUntilDone();
        // Face goal
        robotDevices.chassis.turnToHeading(-88, 600);
        robotDevices.chassis.waitUntilDone();

        // Grab goal
        robotDevices.chassis.moveToPoint(8.35, 5.55, 4000, {.forwards = false, .maxSpeed = 110, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(false);

        //Face ring
        robotDevices.chassis.turnToHeading(-2, 700);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(5, -127);
        c::motor_move(18, -127);
        // Intake first ring
        robotDevices.chassis.moveToPoint(10, 20, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();
        delay(150);

        
        // FAce second ring
        robotDevices.chassis.turnToHeading(86, 700);
        robotDevices.chassis.waitUntilDone();
        //Intake second ring
        robotDevices.chassis.moveToPoint(26.25, 27, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();
        delay(100);
        // Face far ring
        robotDevices.chassis.turnToHeading(2, 700);
        robotDevices.chassis.waitUntilDone();
        
        // Intake far ring
        robotDevices.chassis.moveToPoint(34.5, 68, 4000, {.forwards = true, .maxSpeed = 100, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();
        delay(650);

        startPrepArmTask();

        // Back up
        robotDevices.chassis.moveToPoint(28, 54.75, 4000, {.forwards = false, .maxSpeed = 80, .minSpeed = 15}); // TUNE THIS FOR WALL STAKE 1
        robotDevices.chassis.waitUntilDone();
        
        // Face wall stake
        robotDevices.chassis.turnToHeading(88, 700);
        robotDevices.chassis.waitUntilDone();
        
        // Intake ring, score on wall stake
        robotDevices.chassis.moveToPoint(48.9, 54.75, 900, {.forwards = true, .maxSpeed = 60, .minSpeed = 30});
        robotDevices.chassis.waitUntilDone();
        delay(700);
        
        // FIRST WALL STAKE
        c::motor_move(5, 15);
        c::motor_move(18, 15);
        stopPrepArmTask();
        c::motor_move(17, -127);
        delay(500);
        c::motor_move(17, 0);
        
        // Reverse from wall stake
        robotDevices.chassis.moveToPoint(32, 53, 4000, {.forwards = false, .maxSpeed = 60, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();

        // Face 3 rings
        robotDevices.chassis.turnToHeading(176, 700);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 60);

        // Drive to 3 rings at high speed
        robotDevices.chassis.moveToPoint(32.25, 40, 4000, {.forwards = true, .maxSpeed = 110, .minSpeed = 80});
        robotDevices.chassis.waitUntilDone();
        
        c::motor_move(17, 0);
        c::motor_move(5, -127);
        c::motor_move(18, -127);

        // Slow down and intake 2 rings
        robotDevices.chassis.moveToPoint(32.25, 1, 4000, {.forwards = true, .maxSpeed = 80, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();
        delay(50);
        // Face 3rd ring
        robotDevices.chassis.turnToHeading(70, 700);
        robotDevices.chassis.waitUntilDone();

        // Intake 3rd ring
        robotDevices.chassis.moveToPoint(41, 7, 4000, {.forwards = true, .maxSpeed = 70, .minSpeed = 25});
        robotDevices.chassis.waitUntilDone();
        delay(100);

        // Angle goal towards corner
        robotDevices.chassis.turnToHeading(-15, 700);
        robotDevices.chassis.waitUntilDone();
        c::motor_move(5, 25);
        c::motor_move(18, 25);

        // Place goal in corner and let go
        robotDevices.chassis.moveToPoint(48, 0.25, 600, {.forwards = false, .maxSpeed = 60, .minSpeed = 50});
        robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(true);
        
        // Drive away from corner
        robotDevices.chassis.moveToPoint(44, 0.9, 700, {.forwards = true, .maxSpeed = 75, .minSpeed = 50});
        robotDevices.chassis.waitUntilDone();

        // Face second goal
        robotDevices.chassis.turnToHeading(87, 550);
        robotDevices.chassis.waitUntilDone();

        // Approach second goal and clamp
        robotDevices.chassis.moveToPoint(-16, 1.75, 4000, {.forwards = false, .maxSpeed = 100, .minSpeed = 40});
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.moveToPoint(-32.75, 0.75, 4000, {.forwards = false, .maxSpeed = 70, .minSpeed = 15});
        robotDevices.chassis.waitUntilDone();
        robotDevices.mogoClampPiston.set_value(false);
        //delay(100);

        // Face first ring
        robotDevices.chassis.turnToHeading(0, 700);
        robotDevices.chassis.waitUntilDone();

        c::motor_move(5, -127);
        c::motor_move(18, -127);

        // Intake first ring
        robotDevices.chassis.moveToPoint(-32.5, 21.5, 1000, {.forwards = true, .maxSpeed = 75, .minSpeed = 15});
        robotDevices.chassis.waitUntilDone();
        
        // Face ring under ladder
        robotDevices.chassis.turnToHeading(48, 500);                       
        robotDevices.chassis.waitUntilDone();
        c::motor_move(18, -30);

        // Intake ladder ring
        robotDevices.chassis.moveToPoint(-11.75, 44, 4000, {.forwards = true, .maxSpeed = 110, .minSpeed = 15});
        robotDevices.chassis.waitUntilDone();
        c::motor_move(18, -127);

        delay(600);
        c::motor_move(5, 30);
        c::motor_move(18, 30);
        // Back out of ladder
        robotDevices.chassis.moveToPoint(-37, 28, 4000, {.forwards = false, .maxSpeed = 75, .minSpeed = 15});
        robotDevices.chassis.waitUntilDone();
        c::motor_move(5,  -127);
        c::motor_move(18, -127);

        
        // Face wall stake ring and approach
        robotDevices.chassis.turnToHeading(-45, 700);                        
        robotDevices.chassis.waitUntilDone();

        startPrepArmTask();

        robotDevices.chassis.moveToPoint(-44, 47.5, 4000, {.forwards = true, .maxSpeed = 75, .minSpeed = 15});
        robotDevices.chassis.waitUntilDone();

        // Face wall stake, intake ring and score
        robotDevices.chassis.turnToHeading(-93, 700);  
        robotDevices.chassis.waitUntilDone();
        delay(200);

        // Drive into wall stake and score
        robotDevices.chassis.moveToPoint(-73, 49.6, 1300, {.forwards = true, .maxSpeed = 60, .minSpeed = 30});
        robotDevices.chassis.waitUntilDone();
        delay(500);

        // SECOND WALL STAKE
        c::motor_move(5, 15);
        c::motor_move(18, 15);
        stopPrepArmTask();
        c::motor_move(17, -127);
        delay(500);
        c::motor_move(17, 0);

        // Back away from wall stake
        robotDevices.chassis.moveToPoint(-51, 48, 2800, {.forwards = false, .maxSpeed = 40, .minSpeed = 15});
        robotDevices.chassis.waitUntilDone();

        // Turn into row of 3
        robotDevices.chassis.turnToHeading(-177, 700);  
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 45);

        // Approach row of 3 rings and intake
        c::motor_move(5, -127);
        c::motor_move(18, -127);
        robotDevices.chassis.moveToPoint(-52, -4, 4000, {.forwards = true, .maxSpeed = 90, .minSpeed = 35});
        robotDevices.chassis.waitUntilDone();
        delay(150);
        c::motor_move(17, 0);
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.turnToHeading(-55, 700);  
        robotDevices.chassis.moveToPoint(-63, 1, 4000, {.forwards = true, .maxSpeed = 60, .minSpeed = 15});
        robotDevices.chassis.waitUntilDone();

        // Turn to third ring
        robotDevices.chassis.turnToHeading(15, 700);  
        robotDevices.chassis.waitUntilDone();

        // Intake third ring
        robotDevices.chassis.moveToPoint(-65, -10.75, 4000, {.forwards = false, .maxSpeed = 60, .minSpeed = 15});
        robotDevices.chassis.waitUntilDone();
        c::motor_move(5, 127);

        c::motor_move(18, 127);
        robotDevices.mogoClampPiston.set_value(true);
        
        // 
        robotDevices.chassis.turnToHeading(65.75, 1000);  
        robotDevices.chassis.waitUntilDone();
        c::motor_move(5, -127);
        c::motor_move(18, -50);
        
        // Travel past ladder
        robotDevices.chassis.moveToPoint(19.25, 70, 2400, {.forwards = true, .maxSpeed = 110, .minSpeed = 15});
        robotDevices.chassis.waitUntilDone();

        c::motor_move(5, 0);
        c::motor_move(18, 0);
        startPrepArmTask();

        // Face third goal
        robotDevices.chassis.turnToHeading(130, 1000);  
        robotDevices.chassis.waitUntilDone();

        // Grab goal        
        robotDevices.chassis.moveToPoint(-11, 90.25, 2500, {.forwards = false, .maxSpeed = 60, .minSpeed = 15});
        c::motor_move(5, -127);
        c::motor_move(18, -127);
        robotDevices.chassis.waitUntilDone();
        delay(100);
        robotDevices.mogoClampPiston.set_value(false);
        
        // Face alliance stake
        robotDevices.chassis.turnToHeading(12.5, 1000);  
                
        robotDevices.chassis.waitUntilDone();  
        // Score on alliance stake                                    
        //robotDevices.chassis.moveToPoint(-9, 90, 2500, {.forwards = true, .maxSpeed = 60, .minSpeed = 30});
        robotDevices.chassis.waitUntilDone();                                      

        // ALLIANCE STKAE
        c::motor_move(5, 15);
        c::motor_move(18, 15);
        stopPrepArmTask();
        c::motor_move(17, -127);
        delay(550);
        c::motor_move(17, 0);
        
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.moveToPoint(-13.8, 85, 5000, {.forwards = false, .maxSpeed = 100, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();

        robotDevices.chassis.turnToHeading(-135, 1000);  
        robotDevices.chassis.waitUntilDone();
        c::motor_move(17, 60);

        c::motor_move(5, -127);
        c::motor_move(18, -127);
                        
        robotDevices.chassis.moveToPoint(-28, 70, 5000, {.forwards = true, .maxSpeed = 127, .minSpeed = 80});

        robotDevices.chassis.waitUntilDone();

        c::motor_move(17, 0);

        robotDevices.chassis.turnToHeading(-88, 1000);  
        robotDevices.chassis.waitUntilDone();
        robotDevices.chassis.moveToPoint(-62.9, 71, 5000, {.forwards = true, .maxSpeed = 127, .minSpeed = 80});
        robotDevices.chassis.waitUntilDone();
        delay(200);
        robotDevices.chassis.turnToHeading(-3, 1000);  
        robotDevices.chassis.waitUntilDone();

        robotDevices.chassis.moveToPoint(-72.5, 83.5, 5000, {.forwards = true, .maxSpeed = 100, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();   

                                            
        robotDevices.chassis.moveToPoint(-72.5, 75, 5000, {.forwards = false, .maxSpeed = 100, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();   
        robotDevices.chassis.turnToHeading(43, 1000);                                                 robotDevices.chassis.waitUntilDone();   
        robotDevices.chassis.waitUntilDone();  
                                               
        robotDevices.chassis.moveToPoint(-66, 86.5, 5000, {.forwards = true, .maxSpeed = 100, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();   
        delay(100);

        robotDevices.chassis.turnToHeading(125, 1000);  
        robotDevices.chassis.waitUntilDone();   
        robotDevices.mogoClampPiston.set_value(true);

        robotDevices.chassis.moveToPoint(-78, 102, 1000, {.forwards = false, .maxSpeed = 100, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();   
        robotDevices.chassis.moveToPoint(-50, 91, 2000, {.forwards = true, .maxSpeed = 100, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();   
        robotDevices.chassis.turnToHeading(60, 600);  
                astartPrepArmTask();

        robotDevices.chassis.moveToPoint(57, 127, 2700, {.forwards = true, .maxSpeed = 100, .minSpeed = 60});
        robotDevices.chassis.waitUntilDone();   
        //c::motor_move(17, 0);
                c::motor_move(5, 25);
        c::motor_move(18, 25);
                c::motor_move(18, 0);
       // robotDevices.chassis.turnToHeading(55, 400);  
        robotDevices.chassis.waitUntilDone();   

                        
        robotDevices.chassis.moveToPoint(0, 39, 3000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127});

        delay(3000);
                robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
        robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);


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