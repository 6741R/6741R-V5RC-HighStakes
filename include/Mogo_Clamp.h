#pragma once
#ifndef MOGO_CLAMP_H
#define MOGO_CLAMP_H

class Mogo_Clamp {

    public:
        // Class Constructor
        Mogo_Clamp();

        // Subystem Functions
        void Clamp(); // Clamps mogo clamp
        void Unclamp(); // Releases mogo clamp
        bool GetIsClamped() const; // Returns status of clamp

    private:
        bool isClamped; // Used privately to determine status of clamp

};

#endif