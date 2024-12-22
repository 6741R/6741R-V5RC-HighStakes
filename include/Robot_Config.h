#pragma once
#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "lemlib/api.hpp"
#include "pros/optical.hpp"

using namespace pros;

class Robot_Config {
    public:
    
    // 3-WIRE DIGITAL OUT (PNEUMATICS)

        // Mogo-clamp sensor
        ADIDigitalOut mogoClampPiston;
        ADIDigitalOut ringStopperPiston;
        ADIDigitalOut doinker;

    // 3-WIRE IN (SENSORS)

        // Nothing yet

    // V5 SENSORS
        Optical optical;

        // Inertial sensors
        Imu imu;
        Imu imu2;

    // SUBSYSTEM MOTORS

        Motor liftMotor;
        Motor intakeMotor;
        Motor intakeMotor2;
        Rotation liftRotation;
        lemlib::Chassis chassis;

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
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel;
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel;
// horizontal tracking wheel encoder
pros::Rotation horizontal_encoder;
// vertical tracking wheel encoder
pros::Rotation vertical_encoder;
// odometry settings
lemlib::OdomSensors sensors;
    // ENCODERS (in motors, read individually)

    // PID CONTROLLERS

        lemlib::ControllerSettings lateralController;
        lemlib::ControllerSettings angularController;
        lemlib::ControllerSettings armPid;

    Robot_Config();
};

#endif
