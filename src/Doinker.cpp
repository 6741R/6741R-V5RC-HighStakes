#include "Robot_Config.h"
#include "Doinker.h"

// References the global robot configuration object for device management.
extern Robot_Config robotDevices;

/**
 *  @brief Constructor for Mogo_Clamp.
 * 
 * Initializes the `isClamped` state to `false`, indicating that the clamp is 
 * not engaged when the object is created.
 */
 Doinker::Doinker() : isLowered(false) {}

/**
 * @brief Engages the mobile goal (mogo) clamp.
 * 
 * This function activates the pneumatic piston responsible for clamping the 
 * mobile goal by setting its value to `true`. The `isClamped` state is then 
 * updated to reflect that the clamp is engaged.
 */
void Doinker::Lower() {
    robotDevices.doinker.set_value(true);
    isLowered = true;
}

/**
 * @brief Releases the mobile goal (mogo) clamp.
 * 
 * This function deactivates the pneumatic piston by setting its value to `false`, 
 * releasing the mobile goal. The `isClamped` state is then updated to reflect that 
 * the clamp is disengaged.
 */
void Doinker::Raise() {
    robotDevices.doinker.set_value(false);
    isLowered = false;
}
