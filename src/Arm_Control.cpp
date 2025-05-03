#include "Robot_Config.h"
#include "Arm_Control.h"
#include "lemlib/api.hpp"

extern Robot_Config robotDevices;

pros::Task *Arm_Control::armTask = nullptr;
int Arm_Control::armTargetPosition = 0;

// PID Constants
const double kP = 0.4
;
const double kI = 0.0;
const double kD = 0.0;
const double tolerance = 2.0;
const double maxPower = 127.0;
const double minPower = -127.0;



void Arm_Control::StopArm() {
    robotDevices.armMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    robotDevices.armMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    robotDevices.armMotor1.move(0);
    robotDevices.armMotor2.move(0);
}

void Arm_Control::Raise() {
    robotDevices.armMotor1.move(127);
    robotDevices.armMotor2.move(-127);
}

void Arm_Control::Lower() {
    robotDevices.armMotor1.move(-127);
    robotDevices.armMotor2.move(127);
}

int Arm_Control::GetPosition() {
    return robotDevices.armMotor1.get_position();
}
void Arm_Control::ArmPID(void *param) {
    robotDevices.armMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    robotDevices.armMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    double error = 0.0, lastError = 0.0;
    double integral = 0.0, derivative = 0.0;
    double motorPower = 0.0;

    while (true) {
        double currentPosition = GetPosition();
        
        error = armTargetPosition - currentPosition;
        integral += error;
        derivative = error - lastError;

        // Prevent integral wind-up
        if (fabs(error) < 50) {
            integral += error;
        } else {
            integral = 0;
        }

        motorPower = (kP * error) + (kI * integral) + (kD * derivative);
        motorPower = std::clamp(motorPower, minPower, maxPower);

        robotDevices.armMotor1.move(motorPower);
        robotDevices.armMotor2.move(-motorPower);

        lastError = error;
        pros::delay(10);
    }
}

bool Arm_Control::armPIDActive = false;

bool Arm_Control::IsArmPIDActive() {
    return armPIDActive;
}

void Arm_Control::StartArmPID(int target) {
    if (armTask == nullptr) {
        armTargetPosition = target;
        armPIDActive = true;
        armTask = new pros::Task(ArmPID, nullptr, "Arm PID Task");
    }
}

void Arm_Control::StopArmPID() {
    if (armTask != nullptr) {
        armTask->remove();
        delete armTask;
        armTask = nullptr;
        armPIDActive = false;
    }
}
