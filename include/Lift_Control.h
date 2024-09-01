#pragma once
#ifndef LIFT_CONTROL_H
#define LIFT_CONTROL_H

/**
 * @class Lift_Control
 * @brief Manages the control of the lift mechanism.
 *
 * The Lift_Control class provides functions to control the position of the lift,
 * including raising, lowering, and stopping the lift. It also provides a method
 * to get the current position of the lift.
 */
class Lift_Control {

    public:

        /**
         * @brief Sets the lift to a specific target position.
         * 
         * @param targetPosition The desired position to set the lift to.
         * This method moves the lift to the specified position, adjusting the
         * lift motor accordingly.
         */
        void SetPosition(int targetPosition);

        /**
         * @brief Raises the lift to the highest possible position.
         *
         * This method sets the lift to its maximum height.
         */
        void RaiseLift();

        /**
         * @brief Lowers the lift to the lowest possible position.
         *
         * This method sets the lift to its minimum height.
         */
        void LowerLift();

        /**
         * @brief Stops the lift and holds it in its current position.
         *
         * This method applies hold mode to hold the lift in place without
         * further movement.
         */
        void StopLift();

        /**
         * @brief Retrieves the current position of the lift.
         * 
         * @return The current position of the lift.
         *
         * This method returns the position of the lift as reported by the
         * rotation sensor.
         */
        int GetPosition();
};

#endif