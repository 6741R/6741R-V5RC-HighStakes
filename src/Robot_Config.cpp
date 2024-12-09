#include "Robot_Config.h"
#include "pros/optical.hpp"

using namespace pros;

// Constructor for global device configuration
Robot_Config::Robot_Config() :

    // 3-WIRE DIGITAL OUT (PNEUMATICS)

        // Mogo-clamp pneumatic device
        #define DIGITAL_SENSOR_PORT_B 'B'
        mogoClampPiston(DIGITAL_SENSOR_PORT_B),

        // Ring-stopper pneumatic device
        #define DIGITAL_SENSOR_PORT_A 'A'
        ringStopperPiston(DIGITAL_SENSOR_PORT_A),

    // 3-WIRE DIGITAL IN

        // None yet

    // 3-WIRE ANALOG OUT

        // None yet
    
    // 3-WIRE ANALOG IN

        // None yet

    // V5 SENSORS
optical(1),
        // Inertial sensor
        imu(12),

        // Rotation sensors for odometry
        trackingPodHorizontal(6, true),
        trackingPodVertical(5, false),
        liftRotation(15, false),

    // SUBSYSTEM MOTORS

        liftMotor(7, E_MOTOR_GEAR_BLUE),
        intakeMotor(17, E_MOTOR_GEAR_BLUE),
        intakeMotor2(13, E_MOTOR_GEAR_GREEN),


        

    // DRIVETRAIN MOTORS

        // Motors comprising the left half of the Drivetrain when looking from the front
        frontRightMotor (-20, E_MOTOR_GEAR_BLUE),
        lowerRightMotor (18, E_MOTOR_GEAR_BLUE),
        upperRightMotor (-19, E_MOTOR_GEAR_BLUE), 

        // Motors comprising the right half of the Drivetrain when looking from the front
        frontLeftMotor (9, E_MOTOR_GEAR_BLUE),
        lowerLeftMotor (-10, E_MOTOR_GEAR_BLUE),
        upperLeftMotor (8, E_MOTOR_GEAR_BLUE),

        // Drivetrain motorgroups
        leftMotors ({frontLeftMotor, lowerLeftMotor, upperLeftMotor}),
        rightMotors ({frontRightMotor, lowerRightMotor, upperRightMotor}),

        // Initialization of the Drivetrain object
        drivetrain(&leftMotors, &rightMotors, 11.475, lemlib::Omniwheel::NEW_325, 450, 2),

    // ODOMETRY OBJECTS

        // Tracking wheel objects
        vertTrackingWheel(&trackingPodVertical, lemlib::Omniwheel::NEW_2, 1.25),
        horTrackingWheel(&trackingPodHorizontal, lemlib::Omniwheel::NEW_2, -1.475),

        // Odometry sensors object
        sensors(&vertTrackingWheel, nullptr, &horTrackingWheel, nullptr, &imu),

    // PID CONSTRUCTORS

        // Lateral PID controller constructor
        lateralController (6, // proportional gain (kP)
                           0.1, // integral gain (kI)
                           0.5, // derivative gain (kD)
                           3, // anti windup
                           1, // small error range, in inches
                           100, // small error range timeout, in milliseconds
                           3, // large error range, in inches
                           500, // large error range timeout, in milliseconds
                           20 // maximum acceleration (slew)
        ),

        // Angular PID controller constructor
        angularController( 1.05, // proportional gain (kP)
                           0.2, // integral gain (kI)
                           0.25, // derivative gain (kD)
                           3, // anti windup
                           1, // small error range, in inches
                           100, // small error range timeout, in milliseconds
                           3, // large error range, in inches
                           500, // large error range timeout, in milliseconds
                           0 // maximum acceleration (slew)
        ),

    // OTHER STUFF

        // Robot chassis constructor
        chassis(drivetrain, lateralController, angularController, sensors) 
{}
