#pragma once
#ifndef AUTONOMOUS_MANAGER_H
#define AUTONOMOUS_MANAGER_H

#include "Robot.h"

class Autonomous_Manager {
    public:
        // Constructor
        Autonomous_Manager(Robot& robot);

        // Autonomous routines
        void BlueMatchLeft();
        void BlueMatchRight();
        void RedMatchLeft();
        void RedMatchRight();
        void Skills();

    private:
        // Reference to the Robot object
        Robot& robot;
};

#endif