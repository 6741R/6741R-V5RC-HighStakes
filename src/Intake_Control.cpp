#include "Robot_Config.h"
#include "Intake_Control.h"

using namespace pros;

// References global robot configuration
extern Robot_Config robotDevices;

// Intakes intake at desired velocity in percent units
void Intake_Control::Intake(int velocityPercent) {
    // Rotates intake motor forward at full speed
    c::motor_move(6, (1 / velocityPercent) * 127);
}

// Outtakes intake at desired velocity in percent units
void Intake_Control::Outtake(int velocityPercent) {
    // Rotates intake motor reversed at full speed
    c::motor_move(6, (1 / velocityPercent) * -127);
}

void Intake_Control::StopIntake() {
    robotDevices.intakeMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    c::motor_move(6, 0);
}

// Removes illegal rings from intake
void Intake_Control::CheckPossession() {
    // Check to see if there are more than two rings in intake,
    // if true, outtake until only 2
}

// Returns status of intake
bool Intake_Control::GetIntakingStatus() { 
    return robotDevices.intakeMotor.get_actual_velocity() > 0;
}
