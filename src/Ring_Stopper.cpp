#include "Robot_Config.h"
#include "Ring_Stopper.h"

// References the global robot configuration object for device management.
extern Robot_Config robotDevices;

/**
 *  @brief Constructor for Mogo_Clamp.
 * 
 * Initializes the `isClamped` state to `false`, indicating that the clamp is 
 * not engaged when the object is created.
 */
Mogo_Clamp::Ring_Stopper() : isLowered(false) {}

/**
 * @brief Engages the mobile goal (mogo) clamp.
 * 
 * This function activates the pneumatic piston responsible for clamping the 
 * mobile goal by setting its value to `true`. The `isClamped` state is then 
 * updated to reflect that the clamp is engaged.
 */
void Ring_Stopper::Lower() {
    robotDevices.ringStopperPiston.set_value(true);
    isLowered = true;
}

/**
 * @brief Releases the mobile goal (mogo) clamp.
 * 
 * This function deactivates the pneumatic piston by setting its value to `false`, 
 * releasing the mobile goal. The `isClamped` state is then updated to reflect that 
 * the clamp is disengaged.
 */
void Ring_Stopper::Raise() {
    robotDevices.ringStopperPiston.set_value(false);
    isLowered = false;
}

/**
 * @brief Retrieves the current status of the mobile goal clamp.
 * 
 * This function returns the value of `isClamped`, indicating whether the clamp 
 * is currently engaged (`true`) or released (`false`).
 * 
 * @return `true` if the clamp is engaged, `false` otherwise.
 */
bool Ring_Stopper::GetIsLowered() const {
    return isClamped;
}