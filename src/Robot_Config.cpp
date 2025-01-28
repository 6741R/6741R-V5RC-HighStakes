#include "Robot_Config.h"
#include "pros/optical.hpp"


using namespace pros;

// Constructor for global device configuration
Robot_Config::Robot_Config() : 

    // 3-WIRE DIGITAL OUT (PNEUMATICS)
    #define DIGITAL_SENSOR_PORT_B 'B'
    mogoClampPiston(DIGITAL_SENSOR_PORT_B),

    // Ring-stopper pneumatic device
    #define DIGITAL_SENSOR_PORT_A 'A'
    ringStopperPiston(DIGITAL_SENSOR_PORT_A),

    // Doinker pneumatic device
    #define DIGITAL_SENSOR_PORT_C 'C'
    doinker(DIGITAL_SENSOR_PORT_C),

    // V5 SENSORS
    optical(10), // Optical sensor
    imu(7),      // First inertial sensor
    imu2(8),     // Second inertial sensor
    liftRotation(20),

    // SUBSYSTEM MOTORS
    liftMotor(17, E_MOTOR_GEAR_BLUE),
    intakeMotor(18, E_MOTOR_GEAR_BLUE),
    intakeMotor2(5, E_MOTOR_GEAR_GREEN),

    // DRIVETRAIN MOTORS
    frontLeftMotor(16, E_MOTOR_GEAR_BLUE),
    lowerLeftMotor(-15, E_MOTOR_GEAR_BLUE),
    upperLeftMotor(14, E_MOTOR_GEAR_BLUE),
    frontRightMotor(-13, E_MOTOR_GEAR_BLUE),
    lowerRightMotor(12, E_MOTOR_GEAR_BLUE),
    upperRightMotor(-11, E_MOTOR_GEAR_BLUE),

    // Drivetrain motor groups
    leftMotors({frontLeftMotor, lowerLeftMotor, upperLeftMotor}),
    rightMotors({frontRightMotor, lowerRightMotor, upperRightMotor}),

    // Drivetrain initialization
    drivetrain(&leftMotors, &rightMotors, 11.375, lemlib::Omniwheel::NEW_325, 450.75, 2),
    
    horizontal_encoder(6, false),
    vertical_encoder(1, true),

// horizontal tracking wheel
horizontal_tracking_wheel(&horizontal_encoder, 1.996, 1.55),
// vertical tracking wheel
vertical_tracking_wheel(&vertical_encoder, 1.996, 0.88),

// odometry settings
sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu2 // inertial sensor
),
    // Removing ADIEncoder initialization as it is not necessary
    // Using motor encoders directly
    // Chassis initialization without odometry

    // PID CONSTRUCTORS
    lateralController(6, 0.1, 0.5, 3, 1, 100, 3, 500, 20),
    angularController(0.95, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              0.2, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
),
    armPid(0.5, 0.01, 0.1, 3, 1, 100, 3, 500, 0),

   
        chassis(drivetrain, lateralController, angularController, sensors){}
       
       
        // initialize function. Runs on program startup
// initialize function. Runs on program startup

