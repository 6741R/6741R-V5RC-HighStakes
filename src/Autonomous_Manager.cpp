#include "Autonomous_Manager.h"

// Class constructor

/**
 * @brief Constructor for the Autonomous_Manager class.
 * 
 * Initializes the Autonomous_Manager with a reference to the Robot object, 
 * allowing access to the robot's subsystems during autonomous routines.
 * 
 * @param robot Reference to the Robot object that this manager will control.
 */
Autonomous_Manager::Autonomous_Manager(Robot& robot) : robot(robot) {}

// Autonomous routines

/**
 * @brief Executes the autonomous routine for the Blue Alliance, left side.
 * 
 * This function contains the sequence of actions that the robot should perform 
 * during the autonomous period when positioned on the left side of the Blue Alliance field.
 */
void Autonomous_Manager::BlueMatchLeft() {

    // Example action: Start the intake motor at full speed.
    robot.intake.Intake(127);
}

/**
 * @brief Executes the autonomous routine for the Blue Alliance, right side.
 * 
 * This function is intended to contain the sequence of actions for the Blue Alliance's 
 * right side during the autonomous period. Currently empty and needs to be implemented.
 */
void Autonomous_Manager::BlueMatchRight() {

}

/**
 * @brief Executes the autonomous routine for the Red Alliance, left side.
 * 
 * This function is intended to contain the sequence of actions for the Red Alliance's 
 * left side during the autonomous period. Currently empty and needs to be implemented.
 */
void Autonomous_Manager::RedMatchLeft() {

}

/**
 * @brief Executes the autonomous routine for the Red Alliance, right side.
 * 
 * This function is intended to contain the sequence of actions for the Red Alliance's 
 * right side during the autonomous period. Currently empty and needs to be implemented.
 */
void Autonomous_Manager::RedMatchRight() {

}

/**
 * @brief Executes the autonomous routine for the Skills challenge.
 * 
 * This function is intended to contain the sequence of actions for the Skills challenge 
 * during the autonomous period. Currently empty and needs to be implemented.
 */
void Autonomous_Manager::Skills() {

}