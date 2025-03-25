#include "Robot_Config.h"
#include "Mogo_Clamp.h"

// References the global robot configuration object for device management.
extern Robot_Config robotDevices;

/**
 *  @brief Constructor for Mogo_Clamp.
 * 
 * Initializes the `isClamped` state to `false`, indicating that the clamp is 
 * not engaged when the object is created.
 */
Mogo_Clamp::Mogo_Clamp() : isClamped(false) {}

/**
 * @brief Engages the mobile goal (mogo) clamp.
 * 
 * This function activates the pneumatic piston responsible for clamping the 
 * mobile goal by setting its value to `true`. The `isClamped` state is then 
 * updated to reflect that the clamp is engaged.
 */
void Mogo_Clamp::Clamp() {
    robotDevices.mogoClampPiston1.set_value(true);
    robotDevices.mogoClampPiston2.set_value(true);
    isClamped = true;
}

/**
 * @brief Releases the mobile goal (mogo) clamp.
 * 
 * This function deactivates the pneumatic piston by setting its value to `false`, 
 * releasing the mobile goal. The `isClamped` state is then updated to reflect that 
 * the clamp is disengaged.
 */
void Mogo_Clamp::Unclamp() {
    robotDevices.mogoClampPiston1.set_value(false);
    robotDevices.mogoClampPiston2.set_value(true);
    isClamped = false;
}
