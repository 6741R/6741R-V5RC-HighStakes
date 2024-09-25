#pragma once
#ifndef ROBOT_H
#define ROBOT_H

// Include all subsystem headers
#include "Lift_Control.h"
#include "Mogo_Clamp.h"
#include "Intake_Control.h"
#include "Ring_Stopper.h"

/**
 * @class Robot
 * @brief Manages the overall robot, including all subsystems.
 *
 * The Robot class is responsible for orchestrating the behavior of all subsystems
 * such as the lift, mogo clamp, and intake. It provides a unified interface to
 * control the entire robot.
 */
class Robot {
    
    public:

        /**
         * @brief Constructor for the Robot class.
         * 
         * Initializes the robot by creating instances of each subsystem.
         */
        Robot();  

        /**
         * @brief Initializes the robot for operation.
         * 
         * This function is used to calibrate sensors and prepare the robot
         * for use in competition or practice.
         */
        void initialize();

        // Subsystem instances
        Lift_Control lift;      ///< Controls the lift mechanism.
        Mogo_Clamp mogoClamp;   ///< Controls the mobile goal clamp.
        Intake_Control intake;  ///< Controls the intake mechanism.
        Ring_Stopper ringStopper; ///< Controls the ring stopping mechanism.
};

#endif