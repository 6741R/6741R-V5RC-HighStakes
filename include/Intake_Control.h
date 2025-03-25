#pragma once
#ifndef INTAKE_CONTROL_H
#define INTAKE_CONTROL_H

/**
 * @class Intake_Control
 * @brief Manages the intake system of the robot.
 *
 * The Intake_Control class provides functions to control the intake mechanism,
 * including intaking and outtaking at specific velocities, stopping the intake,
 * checking possession of rings, and retrieving the current intake status.
 */
class Intake_Control {
    public:

        /**
         * @brief Intakes objects at a specified velocity.
         * 
         * @param velocityPercent The desired velocity of the intake, expressed as a percentage.
         *
         * This method sets the intake motor to rotate forward at the specified speed.
         */
        void Intake(int velocityPercent);

        /**
         * @brief Outtakes objects at a specified velocity.
         * 
         * @param velocityPercent The desired velocity of the outtake, expressed as a percentage.
         *
         * This method sets the intake motor to rotate in reverse at the specified speed.
         */
        void Outtake(int velocityPercent);

        /**
         * @brief Stops the intake mechanism.
         *
         * This method halts the intake motor and sets it to coast mode, stopping all movement.
         */
        void StopIntake();


};

#endif