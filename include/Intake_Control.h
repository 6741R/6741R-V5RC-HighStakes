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
         * @brief Sets the desired intake velocity manually.
         * 
         * @param velocityPercent The desired velocity of the intake, expressed as a percentage.
         */
        void setVelocity(int velocityPercent);

        /**
         * @brief Starts the background task that manages color sorting.
         */
        void startTask();
        void stopTask();

        void setColorSortEnabled(bool enabled);
        bool isColorSortEnabled() const;

        bool taskRunning = false;
        bool redAlliance = false;

    private:
        int manualVelocity = 0; // Velocity set by the driver
        bool ejecting = false;
        bool ejectScheduled = false;
        int ejectTimer = 0;
        int ejectDelayTimer = 0;
        bool colorSortEnabled = true;

        void taskFn(); // The background task function
        pros::Task* intakeTask = nullptr;

};

#endif
