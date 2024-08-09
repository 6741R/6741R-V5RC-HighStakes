#include "Robot_Config.h"
using namespace pros;

// Constructor for global device configuration
Robot_Config::Robot_Config() :

    // 3-WIRE DIGITAL OUT (PNEUMATICS)

        // Mogo-clamp pneumatic device
        #define DIGITAL_SENSOR_PORT_A 'A'
        mogoClampPiston(DIGITAL_SENSOR_PORT_A),

    // 3-WIRE DIGITAL IN

        // None yet

    // 3-WIRE ANALOG OUT

        // None yet
    
    // 3-WIRE ANALOG IN

        // None yet

    // V5 SENSORS

        // Inertial sensor
        imu(10),

        // Rotation sensors for odometry
        trackingPodLeft(11),
        trackingPodRight(12),
        trackingPodBack(13),

    // SUBSYSTEM MOTORS

        liftMotor(12, E_MOTOR_GEAR_GREEN),
        intakeMotor(8, E_MOTOR_GEAR_GREEN),

    // DRIVETRAIN MOTORS

        // Motors comprising the left half of the Drivetrain
        frontLeftMotor (19, E_MOTOR_GEAR_BLUE),
        lowerLeftMotor (-9, E_MOTOR_GEAR_BLUE),
        upperLeftMotor (10, E_MOTOR_GEAR_BLUE), //op

        // Motors comprising the right half of the Drivetrain
        frontRightMotor (-6, E_MOTOR_GEAR_BLUE),
        lowerRightMotor (20, E_MOTOR_GEAR_BLUE),
        upperRightMotor (19, E_MOTOR_GEAR_BLUE),

        // Drivetrain motorgroups
        leftMotors ({frontLeftMotor, lowerLeftMotor, upperLeftMotor}),
        rightMotors ({frontRightMotor, lowerRightMotor, upperRightMotor}),

        // Initialization of the Drivetrain object
        drivetrain(&leftMotors, &rightMotors, 10, lemlib::Omniwheel::NEW_325, 480, 2),

    // ODOMETRY OBJECTS

        // Tracking wheel objects
        vertTrackingWheelLeft(&trackingPodLeft, lemlib::Omniwheel::NEW_325, 1, 0.8),
        vertTrackingWheelRight(&trackingPodRight, lemlib::Omniwheel::NEW_325, 1, 0.8),
        horTrackingWheel(&trackingPodBack, lemlib::Omniwheel::NEW_325, 1, 0.8),

        // Odometry sensors object
        sensors(&vertTrackingWheelLeft, &vertTrackingWheelRight, &horTrackingWheel, nullptr, &imu),

    // PID CONSTRUCTORS

        // Lateral PID controller constructor
        lateralController(10, // proportional gain (kP)
                        0, // integral gain (kI)
                        3, // derivative gain (kD)
                        3, // anti windup
                        1, // small error range, in inches
                        100, // small error range timeout, in milliseconds
                        3, // large error range, in inches
                        500, // large error range timeout, in milliseconds
                        20 // maximum acceleration (slew)
        ),

        // Angular PID controller constructor
        angularController(2, // proportional gain (kP)
                        0, // integral gain (kI)
                        10, // derivative gain (kD)
                        3, // anti windup
                        1, // small error range, in degrees
                        100, // small error range timeout, in milliseconds
                        3, // large error range, in degrees
                        500, // large error range timeout, in milliseconds
                        0 // maximum acceleration (slew)
        ),

    // OTHER STUFF

        // Robot chassis constructor
        chassis(drivetrain, lateralController, angularController, sensors) 
{}

