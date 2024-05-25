#include "Robot_Config.h"
#include "Mogo_Clamp.h"

// References global robot configuration
extern Robot_Config robotDevices;

// Initialize isClamped as false
Mogo_Clamp::Mogo_Clamp() : isClamped(false) {}

// Clamps mogo clamp
void Mogo_Clamp::Clamp() {
    robotDevices.mogoClampPiston.set_value(true);
    isClamped = true;
}

// Releases mogo clamp
void Mogo_Clamp::Unclamp() {
    robotDevices.mogoClampPiston.set_value(false);
    isClamped = false;
}

// Returns status of clamp
bool Mogo_Clamp::GetIsClamped() const {
    return isClamped;
}
