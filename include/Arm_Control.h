#pragma once
#ifndef ARM_CONTROL_H
#define ARM_CONTROL_H

#include "pros/rtos.hpp"
#include "Robot_Config.h"
#include "Arm_Control.h"
#include "lemlib/api.hpp"



extern Robot_Config robotDevices;

class Arm_Control {
public:
    static void StopArm();
    static int GetPosition();

    // Task management
    static void StartArmPID(int target);
    static void StopArmPID();

private:
    static void ArmPID(void *param);

    static pros::Task *armTask;
    static int armTargetPosition;
};

#endif