#pragma once
#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "lemlib/api.hpp"
#include "pros/optical.hpp"

using namespace pros;

class Robot_Config {
    public:
    
    // 3-WIRE DIGITAL OUT (PNEUMATICS)
        ADIDigitalOut mogoClampPiston1;
        ADIDigitalOut mogoClampPiston2;
        ADIDigitalOut doinker;

    // V5 SENSORS
        Optical optical;
        Imu imu;
        Rotation armRotation;

    // SUBSYSTEM MOTORS
        Motor armMotor1;
        Motor armMotor2;
        Motor intakeMotor;

    // DRIVETRAIN MOTORS
        Motor frontLeftMotor;
        Motor lowerLeftMotor;
        Motor upperLeftMotor;
        Motor frontRightMotor;
        Motor lowerRightMotor;
        Motor upperRightMotor;

        // Drivetrain motor groups
        MotorGroup leftMotors;
        MotorGroup rightMotors;

    // ODOMETRY OBJECTS
        // Initialization of the Drivetrain object
        lemlib::Drivetrain drivetrain;

        lemlib::TrackingWheel horizontal_tracking_wheel;
        lemlib::TrackingWheel vertical_tracking_wheel;

        pros::Rotation horizontal_encoder;
        pros::Rotation vertical_encoder;

        lemlib::OdomSensors sensors;

    // PID CONTROLLERS
        lemlib::ControllerSettings lateralController;
        lemlib::ControllerSettings angularController;
        lemlib::Chassis chassis;

    Robot_Config();
};

#endif
