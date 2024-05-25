#pragma once
#ifndef INTAKE_CONTROL_H
#define INTAKE_CONTROL_H

class Intake_Control {
    public:

        // Subystem Functions
        void Intake(int velocityPercent); // Intakes at desired velocity in percentage units
        void Outtake(int velocityPercent); // Outtakes at desired velocity in percentage units
        void StopIntake(); // Stops intake
        void CheckPossession(); // Removes illegal rings from intake
        bool GetIntakingStatus(); // Gets rotational status of intake
};

#endif