#include "Robot_Config.h"
#include "Intake_Control.h"

using namespace pros;

// References the global robot configuration object for managing devices.
extern Robot_Config robotDevices;

/**
 * @brief Activates the intake system at a specified velocity.
 * 
 * This function commands the intake motor to rotate forward at the given velocity, 
 * which is specified as a percentage of full power. The velocity is converted to 
 * a range suitable for the motor control function.
 * 
 * @param velocityPercent The desired intake velocity in percent (0-100).
 */
void Intake_Control::Intake(int velocityPercent) {
    // Rotates the intake motor forward at the desired speed.
    robotDevices.intakeMotor.move(127);
}

/**
 * @brief Reverses the intake system at a specified velocity.
 * 
 * This function commands the intake motor to rotate in reverse at the given velocity,
 * which is specified as a percentage of full power. The velocity is converted to a 
 * range suitable for the motor control function.
 * 
 * @param velocityPercent The desired outtake velocity in percent (0-100).
 */
void Intake_Control::Outtake(int velocityPercent) {
    // Rotates the intake motor in reverse at the desired speed.
    robotDevices.intakeMotor.move(-127);
}

/**
 * @brief Stops the intake system and sets it to coast mode.
 * 
 * This function stops the intake motor by setting its velocity to zero and
 * changes the brake mode to "coast," allowing the intake to spin freely when stopped.
 */
void Intake_Control::StopIntake() {
    robotDevices.intakeMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    robotDevices.intakeMotor.move(0);
}
