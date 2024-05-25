#include "Robot_Config.h"
#include "Lift_Control.h"

// References global robot configuration
extern Robot_Config robotDevices;

void StopLift() {
    robotDevices.liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    robotDevices.liftMotor.move_velocity(0);
}

// Intakes intake at desired velocity in percent units
void Lift_Control::SetPosition(int targetPosition) {

    // Raise/lower lift to desired position
    // This is just a placeholder, it uses IME rather than Rotation sensor
    robotDevices.liftMotor.move_absolute(targetPosition, 75);
    StopLift();

}

void Lift_Control::RaiseLift() {

    SetPosition(90); // Set lift to highest possible position (90 is a placeholder)
    StopLift();
}

void Lift_Control::LowerLift() {

    SetPosition(0); // Set lift to lowest possible position (0 is a placeholder)
    StopLift();
}

int Lift_Control::GetPosition() {

    // This uses IME, replace with Rotation sensor on lift when ready
    return robotDevices.liftMotor.get_position();

}