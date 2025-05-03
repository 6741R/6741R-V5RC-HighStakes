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
   // ui.DisplayAutonSelectorUI();
    robotDevices.chassis.calibrate(); 
}

/*** @brief Initialize function. Runs on program startup */
void initialize() {
  robotDevices.chassis.calibrate();
}

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
    selectedMode = 9;

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
    // Red SOLO AWP   1 TUNED
    // Blue SOLO AWP  2 TUNED
    // Red GOAL RUSH  3 UNFINISHED
    // Blue GOAL RUSH 4 UNFINISHED
    // Red RING RUSH  5 TUNED
    // Blue RING RUSH 6 TUNED
    // Goal side BLUE 7 TUNED
    // GOAL SIDE MATCH RED 8 TUNED
    // Skills         9

    // Determine which autonomous routine to execute based on the selected mode.
    switch (selectedMode)
    {
        case 1:

            robot.intake.redAlliance = true;
            robot.intake.startTask();

            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            pros::lcd::initialize(); 


            robotDevices.chassis.turnToHeading(300, 700);  
            robotDevices.armMotor1.move(40);
            robotDevices.armMotor2.move(-40);
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            robot.mogoClamp.Unclamp();
            robotDevices.chassis.moveToPoint(9.5, -30, 5000, {.forwards = false, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            delay(50);
            robot.mogoClamp.Clamp();
            robotDevices.armMotor1.move(-40);
            robotDevices.armMotor2.move(40);
            robotDevices.chassis.turnToHeading(140, 700);  
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(25, -47, 5000, {.forwards = true, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(85, 700);  
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(36, -48.5, 5000, {.forwards = true, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            robotDevices.chassis.turnToHeading(340, 700);  
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(38.5, -37, 5000, {.forwards = true, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-24, -11.5, 5000, {.forwards = true, .maxSpeed = 80, .minSpeed = 20});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(130, 700);  
            robotDevices.chassis.waitUntilDone();
            delay(600);
            robot.intake.setVelocity(127); // full intake

            robot.mogoClamp.Unclamp();
            robotDevices.chassis.turnToHeading(30, 700);  
            robotDevices.chassis.waitUntilDone();

            robotDevices.chassis.moveToPoint(-32, -34, 5000, {.forwards = false, .maxSpeed = 80, .minSpeed = 20});
            robotDevices.chassis.waitUntilDone();
            robot.mogoClamp.Clamp();
            robotDevices.chassis.turnToHeading(270, 700);  
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(-60, -34, 5000, {.forwards = true, .maxSpeed = 80, .minSpeed = 20});
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(10);
            robotDevices.armMotor2.move(-10);
            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.chassis.moveToPoint(-20, -65, 800, {.forwards = false, .maxSpeed = 110, .minSpeed = 100});

            break;
        case 2:
            robot.intake.redAlliance = false;
            robot.intake.startTask();

            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            pros::lcd::initialize(); 


            robotDevices.chassis.turnToHeading(-300, 700);  
            robotDevices.armMotor1.move(40);
            robotDevices.armMotor2.move(-40);
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            robot.mogoClamp.Unclamp();
            robotDevices.chassis.moveToPoint(-9.5, -30, 5000, {.forwards = false, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            delay(50);
            robot.mogoClamp.Clamp();
            robotDevices.armMotor1.move(-40);
            robotDevices.armMotor2.move(40);
            robotDevices.chassis.turnToHeading(-140, 700);  
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(-25, -47, 5000, {.forwards = true, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(-85, 700);  
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-36, -48.5, 5000, {.forwards = true, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            robotDevices.chassis.turnToHeading(-340, 700);  
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(-38.5, -37, 5000, {.forwards = true, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(24, -11.5, 5000, {.forwards = true, .maxSpeed = 80, .minSpeed = 20});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(-130, 700);  
            robotDevices.chassis.waitUntilDone();
            delay(600);
            robot.intake.setVelocity(127); // full intake

            robot.mogoClamp.Unclamp();
            robotDevices.chassis.turnToHeading(-30, 700);  
            robotDevices.chassis.waitUntilDone();

            robotDevices.chassis.moveToPoint(32, -34, 5000, {.forwards = false, .maxSpeed = 80, .minSpeed = 20});
            robotDevices.chassis.waitUntilDone();
            robot.mogoClamp.Clamp();
            robotDevices.chassis.turnToHeading(-270, 700);  
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(60, -38, 5000, {.forwards = true, .maxSpeed = 80, .minSpeed = 20});
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(10);
            robotDevices.armMotor2.move(-10);
            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.chassis.moveToPoint(10, -75
                , 800, {.forwards = false, .maxSpeed = 110, .minSpeed = 100});


            break;
        case 3:
            robot.intake.redAlliance = true;
            robot.intake.startTask();

            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

            robot.mogoClamp.Unclamp();
            robotDevices.doinker.set_value(true);
            robotDevices.chassis.moveToPoint(2.5, 28.5, 5000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110});
            robotDevices.chassis.waitUntilDone();
            robotDevices.doinker.set_value(false);
            delay(1000);
            robotDevices.chassis.moveToPoint(-3, 17, 5000, {.forwards = false, .maxSpeed = 90, .minSpeed = 45});

            robotDevices.doinker.set_value(true);
            delay(50);

            //robotDevices.chassis.turnToHeading(0, 1000);
            robotDevices.chassis.waitUntilDone();

            robotDevices.chassis.moveToPoint(-3, 13, 5000, {.forwards = false, .maxSpeed = 127, .minSpeed = 127});
            robotDevices.chassis.waitUntilDone();
            robotDevices.doinker.set_value(false);
            robotDevices.chassis.turnToHeading(190, 1000);
            robotDevices.chassis.waitUntilDone();

            
            robotDevices.chassis.moveToPoint(2.75, 28, 5000, {.forwards = false, .maxSpeed = 100, .minSpeed = 80});
            robotDevices.chassis.waitUntilDone();
            robot.mogoClamp.Clamp();
            delay(100);
            robot.intake.setVelocity(-127); // full intake
            robotDevices.chassis.moveToPoint(1, 15, 5000, {.forwards = true, .maxSpeed = 100, .minSpeed = 80});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(280, 400);
            robotDevices.chassis.waitUntilDone();
            robot.mogoClamp.Unclamp();
            delay(400);
            robotDevices.chassis.turnToHeading(110, 400);
            robotDevices.chassis.waitUntilDone();

            robotDevices.chassis.moveToPoint(-11, 24, 5000, {.forwards = false, .maxSpeed = 100, .minSpeed = 80});
            robotDevices.chassis.waitUntilDone();

            robot.mogoClamp.Clamp();
            delay(150);
            robotDevices.chassis.turnToHeading(75, 400);
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(18, 28, 5000, {.forwards = true, .maxSpeed = 80, .minSpeed = 45});
            robotDevices.chassis.waitUntilDone();



            break;
        case 4:
            robot.intake.redAlliance = false;
            robot.intake.startTask();

            break;
        case 5:
            robot.intake.redAlliance = true;
            robot.intake.startTask();

            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            //robot.lift.StartArmPID(170.0);
            //ui.DisplayMatchImage();
        
            pros::lcd::initialize(); // initialize brain screen
            robot.intake.setVelocity(-127); // full intake
            robot.doinker.Lower();
            robot.mogoClamp.Unclamp();
            
            // RING rush
            robotDevices.chassis.moveToPoint(-2, 32.5, 5000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110});
            robotDevices.chassis.waitUntilDone();
            delay(350);
            robot.intake.setVelocity(-20); // full intake

            // Back up from ring rush
            robotDevices.chassis.moveToPoint(-2, 21, 1500, {.forwards = false, .maxSpeed = 110, .minSpeed = 90});
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(0); // full intake

            robot.doinker.Raise();

            
            delay(300);
            robotDevices.chassis.moveToPoint(-2, 13, 1500, {.forwards = false, .maxSpeed = 80, .minSpeed = 50});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(-130, 700);  
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(14, 20.25, 1500, {.forwards = false, .maxSpeed = 60, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            delay(50);
            robot.mogoClamp.Clamp();
            robotDevices.chassis.turnToHeading(-65, 700);        
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake
            robotDevices.chassis.moveToPoint(-14.75, 31.5, 1500, {.forwards = true, .maxSpeed = 50, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(-190, 700);        
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-15, 8, 1500, {.forwards = true, .maxSpeed = 90, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(-100, 700);  
            robotDevices.chassis.waitUntilDone();      
            robotDevices.chassis.moveToPoint(-38.5, -7, 1000, {.forwards = true, .maxSpeed = 80, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-18, 10, 1500, {.forwards = false, .maxSpeed = 80, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-39.5, -4, 1500, {.forwards = true, .maxSpeed = 80, .minSpeed = 60});
            break;
        case 6:
            robot.intake.redAlliance = false;
            robot.intake.startTask();

            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            //robot.lift.StartArmPID(170.0);
            //ui.DisplayMatchImage();
        
            pros::lcd::initialize(); // initialize brain screen
            robot.intake.setVelocity(-127); // full intake
            robot.doinker.Lower();
            robot.mogoClamp.Unclamp();
            
            // RING rush
            robotDevices.chassis.moveToPoint(2, 32.5, 5000, {.forwards = true, .maxSpeed = 127, .minSpeed = 110});
            robotDevices.chassis.waitUntilDone();
            delay(350);
            robot.intake.setVelocity(-20); // full intake

            // Back up from ring rush
            robotDevices.chassis.moveToPoint(2, 21, 1500, {.forwards = false, .maxSpeed = 110, .minSpeed = 90});
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(0); // full intake

            robot.doinker.Raise();

            
            delay(300);
            robotDevices.chassis.moveToPoint(2, 13, 1500, {.forwards = false, .maxSpeed = 80, .minSpeed = 50});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(130, 700);  
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-14, 20.25, 1500, {.forwards = false, .maxSpeed = 60, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            delay(50);
            robot.mogoClamp.Clamp();
            robotDevices.chassis.turnToHeading(65, 700);        
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake
            robotDevices.chassis.moveToPoint(14.75, 31.5, 1500, {.forwards = true, .maxSpeed = 50, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(190, 700);        
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(15, 8, 1500, {.forwards = true, .maxSpeed = 90, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(100, 700);  
            robotDevices.chassis.waitUntilDone();      
            robotDevices.chassis.moveToPoint(40, -7, 1000, {.forwards = true, .maxSpeed = 80, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(18, 10, 1500, {.forwards = false, .maxSpeed = 80, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(40, -4, 1500, {.forwards = true, .maxSpeed = 80, .minSpeed = 60});
            break;

        case 7:
            robot.intake.redAlliance = false;
            robot.intake.startTask();

            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            pros::lcd::initialize(); 


            robotDevices.chassis.turnToHeading(-60, 700);  
            robotDevices.armMotor1.move(40);
            robotDevices.armMotor2.move(-40);
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            robot.mogoClamp.Unclamp();
            robotDevices.chassis.moveToPoint(9.5, -30, 5000, {.forwards = false, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            delay(50);
            robot.mogoClamp.Clamp();
            delay(50);
            robotDevices.armMotor1.move(-40);
            robotDevices.armMotor2.move(40);
            robotDevices.chassis.turnToHeading(-260, 700);  
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            robot.intake.setVelocity(-110); // full intake

            robotDevices.chassis.moveToPoint(34, -36, 5000, {.forwards = true, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(-345, 700);  
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(57, 8, 1200, {.forwards = true, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();

            delay(2500);

            robot.lift.StartArmPID(300.0);

            robotDevices.chassis.moveToPoint(-10, -35, 2700, {.forwards = true, .maxSpeed = 80, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();

            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            break;
        case 8:
            robot.intake.redAlliance = true;
            robot.intake.startTask();

            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            pros::lcd::initialize(); 


            robotDevices.chassis.turnToHeading(60, 700);  
            robotDevices.armMotor1.move(40);
            robotDevices.armMotor2.move(-40);
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            robot.mogoClamp.Unclamp();
            robotDevices.chassis.moveToPoint(-9.5, -30, 5000, {.forwards = false, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            delay(50);
            robot.mogoClamp.Clamp();
            delay(50);
            robotDevices.armMotor1.move(-40);
            robotDevices.armMotor2.move(40);
            robotDevices.chassis.turnToHeading(260, 700);  
            robotDevices.chassis.waitUntilDone();
            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);
            robot.intake.setVelocity(-110); // full intake

            robotDevices.chassis.moveToPoint(-34, -36, 5000, {.forwards = true, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(345, 700);  
            robotDevices.chassis.waitUntilDone();

            robotDevices.chassis.moveToPoint(-57, 8, 1200, {.forwards = true, .maxSpeed = 90, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();

            delay(2500);

            robot.lift.StartArmPID(300.0);

            robotDevices.chassis.moveToPoint(10, -35, 2700, {.forwards = true, .maxSpeed = 80, .minSpeed = 60});
            robotDevices.chassis.waitUntilDone();

            robotDevices.armMotor1.move(0);
            robotDevices.armMotor2.move(0);

            break;

        case 9:
            //robot.intake.redAlliance = true;
            robot.intake.startTask();
            robot.intake.setColorSortEnabled(false);


            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

            robot.mogoClamp.Unclamp();
            robot.intake.setVelocity(-127); // full intake
            delay(350);
            robot.intake.setVelocity(0); // full intake
            robotDevices.chassis.moveToPoint(0, 8, 800, {.forwards = true, .maxSpeed = 110, .minSpeed = 80});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(270, 500);
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(20.5, 13, 2700, {.forwards = false, .maxSpeed = 70, .minSpeed = 50});
            robotDevices.chassis.waitUntilDone();
            delay(100);

            robot.mogoClamp.Clamp();
            robotDevices.chassis.turnToHeading(350, 600);
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake
            robotDevices.chassis.moveToPoint(24, 30, 2700, {.forwards = true, .maxSpeed = 110, .minSpeed = 80});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(50, 600);
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(39, 82, 2700, {.forwards = true, .maxSpeed = 110, .minSpeed = 80});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(0, 600);

            delay(1000);
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(168.0);
            delay(50);
            robotDevices.chassis.moveToPoint(42, 104, 2700, {.forwards = true, .maxSpeed = 110, .minSpeed = 80});
            robotDevices.chassis.waitUntilDone();
            delay(500);
            robotDevices.chassis.moveToPoint(36, 72, 2700, {.forwards = false, .maxSpeed = 90, .minSpeed = 50});
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(10); // full intake

            robot.lift.StopArm();
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(350.0);
            robotDevices.chassis.turnToHeading(90, 600);
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-90); // full intake

            robotDevices.chassis.moveToPoint(56, 63.5, 1100, {.forwards = true, .maxSpeed = 45, .minSpeed = 30});
            //robotDevices.chassis.turnToHeading(89, 600);
            robotDevices.chassis.waitUntilDone();

            delay(100);
            robot.intake.setVelocity(15); // full intake
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(1300.0);
            delay(750);
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(170.0);
            delay(1000);
            robot.intake.setVelocity(-127); // full intake
            delay(500);
            robotDevices.chassis.turnToHeading(89, 600);
            robotDevices.chassis.waitUntilDone();

            robot.intake.setVelocity(15); // full intake
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(1000.0);
            delay(750);
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(450.0);
            robotDevices.chassis.moveToPoint(46.5, 60, 900, {.forwards = false, .maxSpeed = 80, .minSpeed = 50});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(178, 600);
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(45, 5, 2000, {.forwards = true, .maxSpeed = 70, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(45, 600);
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(54, 18, 2000, {.forwards = true, .maxSpeed = 70, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            delay(300);
            robotDevices.chassis.turnToHeading(330, 600);
            robotDevices.chassis.waitUntilDone();

            robotDevices.chassis.moveToPoint(59, 8, 1000, {.forwards = false, .maxSpeed = 70, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(127); // full intake

            robot.mogoClamp.Unclamp();

            robotDevices.chassis.moveToPoint(52, 14, 2000, {.forwards = true, .maxSpeed = 70, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(100, 600);
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-27, 15, 5000, {.forwards = false, .maxSpeed = 80, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(0); // full intake

            robot.mogoClamp.Clamp();
            delay(200);
            robotDevices.chassis.turnToHeading(0, 600);
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(-29, 35, 5000, {.forwards = true, .maxSpeed = 100, .minSpeed = 30});
            robotDevices.chassis.waitUntilDone();

            robotDevices.chassis.turnToHeading(-50, 600);
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-47.5, 83, 2700, {.forwards = true, .maxSpeed = 110, .minSpeed = 80});
            robotDevices.chassis.waitUntilDone();
            delay(750);

            robot.lift.StopArmPID();
            robot.lift.StartArmPID(175.0);
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.turnToHeading(0, 600);
            robotDevices.chassis.waitUntilDone();

            robotDevices.chassis.moveToPoint(-46, 105, 2700, {.forwards = true, .maxSpeed = 110, .minSpeed = 80}); // frhtest ring
            robotDevices.chassis.waitUntilDone();
            delay(750);
            robot.lift.StopArm();
            robot.lift.StopArmPID();
            robot.intake.setVelocity(10); // full intake

            robot.lift.StartArmPID(350.0);
            robotDevices.chassis.moveToPoint(-38, 70, 2700, {.forwards = false, .maxSpeed = 90, .minSpeed = 50});
            robotDevices.chassis.waitUntilDone();
  

 
            //robot.intake.setVelocity(10); // full intake
            robotDevices.chassis.turnToHeading(250, 600);
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-30); // full intake

            robotDevices.chassis.moveToPoint(-61, 68, 2700, {.forwards = true, .maxSpeed = 90, .minSpeed = 50});
            robotDevices.chassis.waitUntilDone();

            delay(100);
            //robot.intake.setVelocity(20); // full intake
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(1300.0);
            delay(750);
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(170.0);
            delay(1000);
            robot.intake.setVelocity(-127); // full intake
            delay(500);
            robotDevices.chassis.turnToHeading(-89, 600);
            robotDevices.chassis.waitUntilDone();

            robot.intake.setVelocity(20); // full intake
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(1000.0);
            delay(750);
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(450.0);

            robotDevices.chassis.moveToPoint(-49, 64, 2700, {.forwards = false, .maxSpeed = 90, .minSpeed = 50});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(180, 600);
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(-44, 10, 2700, {.forwards = true, .maxSpeed = 75, .minSpeed = 40});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(315, 600);
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-58, 17, 2700, {.forwards = true, .maxSpeed = 75, .minSpeed = 40});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(40, 600);
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-63, 9, 2700, {.forwards = false, .maxSpeed = 75, .minSpeed = 40});
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(127); // full intake

            robot.mogoClamp.Unclamp();
            robotDevices.chassis.turnToHeading(45, 600);
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(-60); // full intake
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(1000);
            delay(400);
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(90);
            robotDevices.chassis.moveToPoint(2, 62, 2700, {.forwards = true, .maxSpeed = 90, .minSpeed = 40});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(30, 100, 2700, {.forwards = true, .maxSpeed = 90, .minSpeed = 40});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(110, 600);
            robotDevices.chassis.waitUntilDone();
            robot.mogoClamp.Unclamp();

            robotDevices.chassis.moveToPoint(5, 115, 2700, {.forwards = false, .maxSpeed = 90, .minSpeed = 40});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(100, 600);

            robot.mogoClamp.Clamp();
            delay(100);
            robot.intake.setVelocity(-127); // full intake

            robotDevices.chassis.moveToPoint(58, 118.5, 2700, {.forwards = true, .maxSpeed = 90, .minSpeed = 40});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(195, 600);
            robotDevices.chassis.waitUntilDone();
            robot.intake.setVelocity(127); // full intake
            robot.mogoClamp.Unclamp();
            robotDevices.chassis.moveToPoint(65, 131, 2700, {.forwards = false, .maxSpeed = 90, .minSpeed = 40});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(57, 118.5, 2700, {.forwards = true, .maxSpeed = 90, .minSpeed = 40});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(270, 600);
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.moveToPoint(-70, 135, 6000 , {.forwards = true, .maxSpeed = 90, .minSpeed = 40});
            robotDevices.chassis.waitUntilDone();
            robotDevices.chassis.turnToHeading(335, 600);
            robotDevices.chassis.waitUntilDone();
            robot.lift.StopArmPID();
            robot.lift.StartArmPID(600);
            robotDevices.chassis.moveToPoint(0, 0, 6000 , {.forwards = false, .maxSpeed = 127, .minSpeed = 40});

            robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
            robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);

    }
}

/*** @brief Runs when initialized by VEX Field Controller */
void competition_initialize() {
    // Hold Arm motor and calibrate its position, and calibrate drivetrain sensors
    robotDevices.armMotor1.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    robotDevices.armMotor2.set_brake_mode(E_MOTOR_BRAKE_HOLD);

    //robotDevices.chassis.calibrate();
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
        robot.mogoClamp.Unclamp();
    }
    else {
        robot.mogoClamp.Clamp();
    }
}

bool piston1State = false;
bool piston2State = false;
bool lastBState = false;
bool lastDownState = false;

/**
 * @brief Controls the mobile goal clamp during the Driver Control period.
 *
 * This function manages the mobile goal clamp based on controller button inputs:
 * - Pressing the Y button will activate the clamp.
 * - Pressing the Right button will deactivate the clamp (release it).
 */
void DoinkerDriverControl() {

    bool currentB = master.get_digital(pros::E_CONTROLLER_DIGITAL_B);
    bool currentDown = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);


     // Toggle piston1 (B button)
    if (currentB && !lastBState) {
        piston1State = !piston1State;
        robotDevices.doinker.set_value(piston1State);
    }

    // Toggle piston2 (Down button)
    if (currentDown && !lastDownState) {
        piston2State = !piston2State;
        robotDevices.mogoClampPiston2.set_value(piston2State);
    }

        // Update last button states
        lastBState = currentB;
        lastDownState = currentDown;
}
// B , Down, toggle
void ArmDriverControl() {
    static bool lastL2 = false;
    static bool toggleState = true; // false = prep position, true = descore position
    bool currentL2 = master.get_digital(E_CONTROLLER_DIGITAL_L2);

    if (master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
        robot.lift.StopArmPID();
        robot.lift.Raise();
    }
    else if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
        robot.lift.StopArmPID();
        robot.lift.Lower();
    }
    else if (currentL2 && !lastL2) {
        robot.lift.StopArmPID();

        // Toggle between prep and descore
        if (toggleState) {
            robot.lift.StartArmPID(168.0); // Prep position
        } else {
            robot.lift.StartArmPID(700.0); // Descore position
        }

        toggleState = !toggleState; // Flip the toggle for next press
    }
    else if (!robot.lift.IsArmPIDActive() &&
             !master.get_digital(E_CONTROLLER_DIGITAL_Y) &&
             !master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
        robot.lift.StopArm();
    }

    if (robot.lift.GetPosition() > 450.0) {
        toggleState = true;
    }

    lastL2 = currentL2;
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
    if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
        robot.intake.setVelocity(-127); // full intake
    }
    else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
        robot.intake.setVelocity(127);  // full outtake
    }
    else {
        robot.intake.setVelocity(0);    // stop
    }
}

bool lastUp = false;
void ColorSortControl() {
    bool currentUp = master.get_digital(E_CONTROLLER_DIGITAL_UP);

    if (currentUp && !lastUp) {
        bool current = robot.intake.isColorSortEnabled();
        robot.intake.setColorSortEnabled(!current);

        if (robot.intake.isColorSortEnabled()) {
            master.rumble("..."); 
        } else {
            master.rumble("."); 
        }
    }


    lastUp = currentUp;
}

/**
 * @brief Executes the Driver Control (opcontrol) tasks while the robot is enabled.
 *
 * This function runs in an infinite loop while the robot is under operator control.
 * It handles the control of the drivetrain, mobile goal clamp, arm, and intake systems.
 */
void opcontrol() {
    //    pros::lcd::initialize();         

    robotDevices.optical.set_led_pwm(99);
    robotDevices.optical.set_integration_time(3);
    robot.intake.startTask();
    robot.intake.setColorSortEnabled(false);
    // Let Drivetrain motors coast when stopped

    while (true) {

        pros::lcd::print(0, "X: %f", robotDevices.chassis.getPose().x); // x
        pros::lcd::print(1, "Y: %f", robotDevices.chassis.getPose().y); // y
        pros::lcd::print(2, "Theta: %f", robotDevices.chassis.getPose().theta); // heading

        DrivetrainDriverControl();
        MogoClampDriverControl();
        ArmDriverControl();
        IntakeDriverControl();
        DoinkerDriverControl();
        ColorSortControl();
        // Small delay
        delay(5);

        
    }
}