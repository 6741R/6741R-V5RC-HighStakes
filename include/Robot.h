#pragma once
#ifndef ROBOT_H
#define ROBOT_H

// Include all other subsystems
#include "Lift_Control.h"
#include "Mogo_Clamp.h"
#include "Intake_Control.h"

class Robot {
    public:

        // Constructor for this class
        Robot();  

        // Subsystem instances
        Lift_Control lift;
        Mogo_Clamp mogoClamp;
        Intake_Control intake;

        // Calibrate sensors, prepare robot for use
        void initialize();
};

#endif