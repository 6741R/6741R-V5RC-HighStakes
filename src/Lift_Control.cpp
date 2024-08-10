#include "Robot_Config.h"
#include "Lift_Control.h"

// References global robot configuration
extern Robot_Config robotDevices;

// Stops and holds the lift
void Lift_Control::StopLift() {
    robotDevices.liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    robotDevices.liftMotor.move_velocity(0);
}

// Sets lift to any desired position
void Lift_Control::SetPosition(int targetPosition) {

    // Raise/lower lift to desired position
    // This is just a placeholder, it uses IME rather than Rotation sensor
    robotDevices.liftMotor.move_absolute(targetPosition, 75);
    StopLift();

}

// Raises lift to highest possible position
void Lift_Control::RaiseLift() {

    SetPosition(90); // Set lift to highest possible position (90 is a placeholder)
    StopLift();
}

// Lowers lift to lowest possible position
void Lift_Control::LowerLift() {

    SetPosition(0); // Set lift to lowest possible position (0 is a placeholder)
    StopLift();
}

// Returns position of lift
int Lift_Control::GetPosition() {

    // This uses IME, replace with Rotation sensor on lift when ready
    return robotDevices.liftMotor.get_position();

}
