#include "Robot_Config.h"
using namespace pros;

// Constructor for global device configuration
Robot_Config::Robot_Config() :

    // 3-WIRE DIGITAL OUT (PNEUMATICS)

        // Mogo-clamp pneumatic device
        #define DIGITAL_SENSOR_PORT_A 'A'
        mogoClampPiston(DIGITAL_SENSOR_PORT_A),

        // Ring-stopper pneumatic device
        #define DIGITAL_SENSOR_PORT_B 'B'
        ringStopperPiston(DIGITAL_SENSOR_PORT_B),

    // 3-WIRE DIGITAL IN

        // None yet

    // 3-WIRE ANALOG OUT

        // None yet
    
    // 3-WIRE ANALOG IN

        // None yet

    // V5 SENSORS

        // Inertial sensor
        imu(14),

        // Rotation sensors for odometry
        trackingPodHorizontal(16, true),
        trackingPodVertical(19, true),

    // SUBSYSTEM MOTORS

        liftMotor(12, E_MOTOR_GEAR_BLUE),
        intakeMotor(6, E_MOTOR_GEAR_BLUE),

    // DRIVETRAIN MOTORS

        // Motors comprising the left half of the Drivetrain when looking from the front
        frontRightMotor (8, E_MOTOR_GEAR_BLUE),
        lowerRightMotor (10, E_MOTOR_GEAR_BLUE),
        upperRightMotor (-9, E_MOTOR_GEAR_BLUE), 

        // Motors comprising the right half of the Drivetrain when looking from the front
        frontLeftMotor (-17, E_MOTOR_GEAR_BLUE),
        lowerLeftMotor (-19, E_MOTOR_GEAR_BLUE),
        upperLeftMotor (18, E_MOTOR_GEAR_BLUE),

        // Drivetrain motorgroups
        leftMotors ({frontLeftMotor, lowerLeftMotor, upperLeftMotor}),
        rightMotors ({frontRightMotor, lowerRightMotor, upperRightMotor}),

        // Initialization of the Drivetrain object
        drivetrain(&leftMotors, &rightMotors, 13, lemlib::Omniwheel::NEW_325, 480, 2),

    // ODOMETRY OBJECTS

        // Tracking wheel objects
        vertTrackingWheel(&trackingPodVertical, lemlib::Omniwheel::OLD_275, -1.25),
        horTrackingWheel(&trackingPodHorizontal, lemlib::Omniwheel::OLD_275, 2.25),

        // Odometry sensors object
        sensors(&vertTrackingWheel, nullptr, &horTrackingWheel, nullptr, &imu),

    // PID CONSTRUCTORS

        // Lateral PID controller constructor
        lateralController (6, // proportional gain (kP)
                           0, // integral gain (kI)
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
                           0, // integral gain (kI)
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

