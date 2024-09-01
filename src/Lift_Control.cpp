#include "Robot_Config.h"
#include "Lift_Control.h"

// References the global robot configuration object for managing devices.
extern Robot_Config robotDevices;

/**
 * @brief Stops the lift and holds its current position.
 * 
 * This function sets the brake mode of the lift motor to "hold," then stops the motor
 * by setting its velocity to zero, effectively holding the lift in its current position.
 */
void Lift_Control::StopLift() {
    
    robotDevices.liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    robotDevices.liftMotor.move_velocity(0);
}

/**
 * @brief Moves the lift to a specified target position.
 * 
 * This function commands the lift to move to a desired position using the motor's
 * internal encoder (IME). After reaching the target position, it stops the lift.
 * 
 * @param targetPosition The position the lift should move to, specified in motor ticks.
 */
void Lift_Control::SetPosition(int targetPosition) {

    // Move the lift to the desired position.
    // This uses the motor's IME, replace with a Rotation sensor when available.
    robotDevices.liftMotor.move_absolute(targetPosition, 75);
    StopLift();
}

/**
 * @brief Raises the lift to its highest possible position.
 * 
 * This function commands the lift to move to a predefined maximum position.
 * The current placeholder value is 90 motor ticks.
 */
void Lift_Control::RaiseLift() {

    SetPosition(90); // Set the lift to the highest possible position (90 is a placeholder).
    StopLift();
}

/**
 * @brief Lowers the lift to its lowest possible position.
 * 
 * This function commands the lift to move to a predefined minimum position.
 * The current placeholder value is 0 motor ticks.
 */
void Lift_Control::LowerLift() {

    SetPosition(0); // Set the lift to the lowest possible position (0 is a placeholder).
    StopLift();
}

/**
 * @brief Retrieves the current position of the lift.
 * 
 * This function returns the lift's position based on the motor's internal encoder (IME).
 * It is intended to be replaced with a more accurate Rotation sensor in the future.
 * 
 * @return The current position of the lift in motor ticks.
 */
int Lift_Control::GetPosition() {

    // Retrieve the lift's position using the IME. Replace with a Rotation sensor when ready.
    return robotDevices.liftMotor.get_position();
}