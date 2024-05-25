#pragma once
#ifndef LIFT_CONTROL_H
#define LIFT_CONTROL_H

class Lift_Control {

    public:

        // Subystem Functions
        void SetPosition(int targetPosition); // Sets lift to desired position
        void RaiseLift(); // Sets lift to highest position
        void LowerLift(); // Sets lift to lowest position
        void StopLift(); // Holds lift
        int GetPosition(); // Returns position of lift

};

#endif