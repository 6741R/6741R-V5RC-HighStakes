#pragma once
#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "lemlib/api.hpp"

using namespace pros;

class Robot_Config {
    public:
    
    // 3-WIRE DIGITAL OUT (PNEUMATICS)

        // Mogo-clamp sensor
        ADIDigitalOut mogoClampPiston;
        ADIDigitalOut ringStopperPiston;

    // 3-WIRE IN (SENSORS)

        // Nothing yet

    // V5 SENSORS
    
        // Inertial sensor
        Imu imu;

        // Rotation sensors for odometry
        Rotation trackingPodVertical;
        Rotation trackingPodHorizontal;
        Rotation liftRotation;

    // SUBSYSTEM MOTORS

        Motor liftMotor;
        Motor intakeMotor;

    // DRIVETRAIN MOTORS

        // Motors composing the left half of the Drivetrain
        Motor frontLeftMotor;
        Motor lowerLeftMotor;
        Motor upperLeftMotor;

        // Motors composing the right half of the Drivetrain
        Motor frontRightMotor;
        Motor lowerRightMotor;
        Motor upperRightMotor;

        // Drivetrain motor groups
        MotorGroup leftMotors;
        MotorGroup rightMotors;

        // Initialization of the Drivetrain object
        lemlib::Drivetrain drivetrain;

    // ODOMETRY OBJECTS

        // Tracking wheel objects
        lemlib::TrackingWheel vertTrackingWheel;
        lemlib::TrackingWheel horTrackingWheel;

        // Odometry sensors object
        lemlib::OdomSensors sensors;

        // Lateral PID controller
        lemlib::ControllerSettings lateralController;

        // Angular PID controller
        lemlib::ControllerSettings angularController;

    // CHASSIS 
    
        lemlib::Chassis chassis;

    Robot_Config();
};

#endif