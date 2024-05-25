#include "Robot.h"
#include "Robot_Config.h"

// References the global robot configuration
extern Robot_Config robotDevices;

// Initializes subsystems into Robot object
Robot::Robot() : lift(), intake(), mogoClamp() {}

void Robot::initialize() {

    // Zero sensors, calibrate devices, etc etc

}