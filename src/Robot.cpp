#include "Robot.h"
#include "Robot_Config.h"

// References the global robot configuration object for managing devices.
extern Robot_Config robotDevices;

/**
 * @brief Constructor for the Robot class.
 * 
 * Initializes the robot's subsystems including the lift, intake, and mogo clamp.
 * These subsystems are created as part of the Robot object upon instantiation.
 */
Robot::Robot() : lift(), intake(), mogoClamp(), doinker() {}

/**
 * @brief Initializes the robot's systems and devices.
 * 
 * This function is intended for tasks such as zeroing sensors, calibrating devices,
 * and performing any necessary setup operations to ensure the robot is ready for operation.
 */
void Robot::initialize() {

    // Placeholder
}