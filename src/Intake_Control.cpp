#include "Robot_Config.h"
#include "Intake_Control.h"

using namespace pros;

extern Robot_Config robotDevices;

bool taskRunning = false;

void Intake_Control::setVelocity(int velocityPercent) {
    manualVelocity = velocityPercent;
}

void Intake_Control::startTask() {
    if (intakeTask == nullptr) {
        taskRunning = true;
        intakeTask = new pros::Task([this]() { this->taskFn(); });
    }
}

void Intake_Control::stopTask() {
    taskRunning = false;
    if (intakeTask != nullptr) {
        intakeTask->join();
        delete intakeTask;
        intakeTask = nullptr;
    }
    robotDevices.intakeMotor.move(0);
}

void Intake_Control::setColorSortEnabled(bool enabled) {
    colorSortEnabled = enabled;
}

bool Intake_Control::isColorSortEnabled() const {
    return colorSortEnabled;
}

void Intake_Control::taskFn() {
    robotDevices.optical.set_led_pwm(98);

    while (taskRunning) {
        double hue = robotDevices.optical.get_hue();
        int proximity = robotDevices.optical.get_proximity();

        bool isRed = (hue < 25 || hue > 330);
        bool isBlue = (hue > 210 && hue < 240);
        bool isClose = (proximity > 225);

        int now = pros::millis();

        if (ejecting) {
            robotDevices.intakeMotor.move(127);
            if (now > ejectTimer) {
                ejecting = false;
            }
        }
        else if (ejectScheduled) {
            if (now > ejectDelayTimer) {
                ejecting = true;
                ejectTimer = now + 350;
                ejectScheduled = false;
            } else {
                robotDevices.intakeMotor.move(manualVelocity);
            }
        }
        else {
            if (colorSortEnabled) {
                if (redAlliance) {
                    if (isBlue && isClose) {
                        ejectScheduled = true;
                        ejectDelayTimer = now + 150;
                    }
                } else {
                    if (isRed && isClose) {
                        ejectScheduled = true;
                        ejectDelayTimer = now + 150;
                    }
                }
            }
            robotDevices.intakeMotor.move(manualVelocity);
        }

        pros::delay(10);
    }

    robotDevices.intakeMotor.brake();
}
