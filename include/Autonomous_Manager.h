#pragma once
#ifndef AUTONOMOUS_MANAGER_H
#define AUTONOMOUS_MANAGER_H

#include "Robot.h"

/**
 * @class Autonomous_Manager
 * @brief Manages and executes various autonomous routines for the robot.
 *
 * The Autonomous_Manager class provides methods to execute different autonomous
 * routines based on the selected strategy. It interacts with the Robot object to
 * control various subsystems during the autonomous period of a match.
 */
class Autonomous_Manager {
    public:

        /**
         * @brief Constructor for the Autonomous_Manager class.
         * 
         * @param robot Reference to the Robot object used for controlling subsystems.
         *
         * Initializes the Autonomous_Manager with a reference to the Robot object,
         * allowing access to its subsystems for executing autonomous routines.
         */
        Autonomous_Manager(Robot& robot);


        /**
         * @brief Executes the autonomous routine for the Blue Alliance, left side.
         *
         * This method contains the code to be run during the autonomous period for
         * the Blue Alliance when starting from the left side.
         */
        void BlueMatchLeft();

        /**
         * @brief Executes the autonomous routine for the Blue Alliance, right side.
         *
         * This method contains the code to be run during the autonomous period for
         * the Blue Alliance when starting from the right side.
         */
        void BlueMatchRight();

        /**
         * @brief Executes the autonomous routine for the Red Alliance, left side.
         *
         * This method contains the code to be run during the autonomous period for
         * the Red Alliance when starting from the left side.
         */
        void RedMatchLeft();

        /**
         * @brief Executes the autonomous routine for the Red Alliance, right side.
         *
         * This method contains the code to be run during the autonomous period for
         * the Red Alliance when starting from the right side.
         */
        void RedMatchRight();

        /**
         * @brief Executes the skills autonomous routine.
         *
         * This method contains the code for a skills challenge routine, which is
         * typically a default routine used for testing or special skills challenges.
         */
        void Skills();

    private:
        /**
         * @brief Reference to the Robot object used for controlling subsystems.
         *
         * This private member variable holds a reference to the Robot object, which
         * allows the Autonomous_Manager to access and control the robot's subsystems
         * during autonomous routines.
         */
        Robot& robot;
};

#endif