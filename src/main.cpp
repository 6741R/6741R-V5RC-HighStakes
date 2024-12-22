// Include headers for the inherited classes
#include "main.h"
#include "Brain_UI.h"
#include "Robot.h"
#include "Autonomous_Manager.h"
#include "Robot_Config.h"
#include "pros/optical.hpp"
#include <thread>

using namespace pros;

// Global objects

/*** @brief Global configuration object for the robot's devices. */
Robot_Config robotDevices;

/*** @brief Global robot object, contains input and output 
 * functionality for all of the robot's subcomponents.*/
Robot robot;

/*** @brief Manages autonomous routines, initialized with
 * the global robot object.*/
Autonomous_Manager autonManager(robot);

/*** @brief Manages the robot's UI display and user interactions. */
Brain_UI ui;

/*** @brief Represents the master controller used to operate the robot. */
Controller master(pros::E_CONTROLLER_MASTER);

/**
 * @brief Runs when robot is disabled by VEX Field Controller.
 */
void disabled() {
	// Placeholder
}

// Constants for Rotational PID
const double kP_rot = 1.5;   // Proportional constant
const float kI_rot = 0.00;   // Integral constant (small to avoid overcorrection)
const double kD_rot = 1.5;  // Derivative constant (moderate to dampen oscillations)
const double tolerance_rot = 2.00;  // Tolerance in degrees
const double integralLimit = 100.0; // Limit to prevent integral windup
const double minMotorSpeed = 0.05;  // Minimum motor speed to avoid stopping too early
const double headingOffset = 180.0; // Offset to adjust sensor heading

// Function for rotational PID with timeout
void rotateToTarget(double targetAngle, unsigned long timeout_ms) {
    // PID variables
    double error = 0.0;            // Difference between target and current heading
    double lastError = 0.0;        // Error from the previous iteration
    double integral = 0.0;         // Sum of all previous errors (I term)
    double derivative = 0.0;       // Rate of change of error (D term)
    double motorPower = 0.0;       // Motor power output

    unsigned long startTime = pros::millis();  // Start time to track timeout

    while (true) {
        // Get current heading from IMUs (average their readings for better accuracy)
        double currentHeading = (robotDevices.imu.get_heading() + robotDevices.imu2.get_heading()) / 2;

        // Adjust for offset
        currentHeading = fmod(currentHeading + headingOffset, 360.0);

        // Calculate error
        error = targetAngle - currentHeading;

        // Wrap error to the shortest path (-180° to 180°)
        if (error > 180) error -= 360;
        if (error < -180) error += 360;

        // Calculate PID components
        integral += error;  // Integral term
        if (integral > integralLimit) integral = integralLimit;  // Limit integral to prevent windup
        if (integral < -integralLimit) integral = -integralLimit;

        // Calculate the derivative term
        derivative = error - lastError;

        // Reduce the effect of the proportional gain as we get closer to the target (adaptive damping)
        double distance = std::abs(error);
        double dampingFactor = 1.0 - std::min(distance / 180.0, 1.0);  // Damping increases as we approach the target

        // Apply PID formula with adaptive damping factor
        motorPower = (kP_rot * error * dampingFactor) + (kI_rot * integral) + (kD_rot * derivative);

        // Ensure motor power does not fall below the minimum speed
        if (std::abs(motorPower) < minMotorSpeed && std::abs(error) > tolerance_rot) {
            motorPower = std::copysign(minMotorSpeed, motorPower);
        }

        // Constrain motor power to prevent overshooting
        motorPower = std::clamp(motorPower, -100.0, 100.0);

        // Set motor powers for rotation
        robotDevices.leftMotors.move(-motorPower); // Negative power for counter rotation
        robotDevices.rightMotors.move(motorPower);

        // Update last error
        lastError = error;
        pros::lcd::set_text(1, "Error: " + std::to_string(error));

        // Check if the error is within tolerance
        if (std::abs(error) <= tolerance_rot) {
            break;  // Exit loop if within tolerance
        }

        // Check if timeout has been reached
        if (pros::millis() - startTime > timeout_ms) {
            pros::lcd::set_text(1, "Timeout reached!");  // Display timeout message
            break;  // Exit loop if timeout exceeded
        }

        // Delay for stability
        pros::delay(10);
    }

    // Stop motors after rotation
    robotDevices.leftMotors.move(0);
    robotDevices.rightMotors.move(0);
}

//swing to heading(weston is trying to cook)
//void swingToHeading(float theta, DriveSide lockedside, int timeout_ms, SwingToHeadingParams params = {}, bool async = true)

// Constants for Linear PID
const double kP_distance = 8.00;   // Proportional constant for distance
const double kI_distance = 0.0;    // Integral constant for distance (avoid overcorrection)
const double kD_distance = 0.00;    // Derivative constant for distance
const double kP_heading = 0.50;     // Proportional constant for heading correction
const double kI_heading = 0.0;     // Integral constant for heading correction
const double kD_heading = 0.00;    // Derivative constant for heading correction
const double tolerance_distance = 0.5;  // Tolerance in inches for distance
const double tolerance_heading = 2.0;   // Tolerance in degrees for heading
const double integralLimit2 = 100.0; // Limit to prevent integral windup
const double minMotorSpeed2 = 10.0;  // Minimum motor speed to avoid stopping too early
const double wheelDiameter = 3.25;  // Diameter of the wheels in inches
const double gearRatio = 48.0 / 36.0; // Gear ratio for the drivetrain

// Function for linear movement PID with heading correction
void moveToDistance(double targetDistanceInches, unsigned long timeout_ms, double maxSpeed) {
    // PID variables for distance
    double errorDistance = 0.0;
    double lastErrorDistance = 0.0;
    double integralDistance = 0.0;
    double derivativeDistance = 0.0;
    double motorPowerDistance = 0.0;

    // PID variables for heading correction
    double errorHeading = 0.0;
    double lastErrorHeading = 0.0;
    double integralHeading = 0.0;
    double derivativeHeading = 0.0;
    double motorPowerHeading = 0.0;

    // Calculate wheel circumference
    double wheelCircumference = M_PI * wheelDiameter;  // Circumference in inches

    // Get counts per revolution for encoders based on gear ratio and wheel circumference
    double countsPerRevolution = 360.0 * gearRatio;  // Assuming encoder gives 360 counts per revolution
    double distancePerCount = wheelCircumference / countsPerRevolution;

    robotDevices.frontLeftMotor.tare_position();
    robotDevices.lowerLeftMotor.tare_position();
    robotDevices.upperLeftMotor.tare_position();

    robotDevices.frontRightMotor.tare_position();
    robotDevices.lowerRightMotor.tare_position();
    robotDevices.upperRightMotor.tare_position();

    // Get start time to track timeout
    unsigned long startTime = pros::millis();

    // Initialize encoder positions
    double initialEncoderPosition = (robotDevices.frontLeftMotor.get_position() + robotDevices.frontRightMotor.get_position() +
                                     robotDevices.upperLeftMotor.get_position() + robotDevices.upperRightMotor.get_position() +
                                     robotDevices.lowerLeftMotor.get_position() + robotDevices.lowerRightMotor.get_position()) / 6.0;

    // Record the initial heading at the start of the movement
    double initialHeading = (robotDevices.imu.get_heading() + robotDevices.imu2.get_heading()) / 2.0;

    while (true) {
        // Get current encoder position (average of all encoders)
        double currentEncoderPosition = (robotDevices.frontLeftMotor.get_position() + robotDevices.frontRightMotor.get_position() +
                                         robotDevices.upperLeftMotor.get_position() + robotDevices.upperRightMotor.get_position() +
                                         robotDevices.lowerLeftMotor.get_position() + robotDevices.lowerRightMotor.get_position()) / 6.0;

        // Calculate distance traveled in inches
        double currentDistance = (currentEncoderPosition - initialEncoderPosition) * distancePerCount;

        // Calculate error for distance
        errorDistance = targetDistanceInches - currentDistance;

        // PID calculation for distance
        integralDistance += errorDistance;
        if (integralDistance > integralLimit2) integralDistance = integralLimit2;
        if (integralDistance < -integralLimit2) integralDistance = -integralLimit2;

        derivativeDistance = errorDistance - lastErrorDistance;
        motorPowerDistance = (kP_distance * errorDistance) + (kI_distance * integralDistance) + (kD_distance * derivativeDistance);

        // Get current heading
        double currentHeading = (robotDevices.imu.get_heading() + robotDevices.imu2.get_heading()) / 2.0;

        // Calculate error for heading (maintain the initial heading)
        errorHeading = initialHeading - currentHeading;  // Target heading is the initial heading
        if (errorHeading > 180.0) errorHeading -= 360.0;
        if (errorHeading < -180.0) errorHeading += 360.0;

        // PID calculation for heading correction
        integralHeading += errorHeading;
        if (integralHeading > integralLimit2) integralHeading = integralLimit2;
        if (integralHeading < -integralLimit2) integralHeading = -integralLimit2;

        derivativeHeading = errorHeading - lastErrorHeading;
        motorPowerHeading = (kP_heading * errorHeading) + (kI_heading * integralHeading) + (kD_heading * derivativeHeading);

        // Apply the heading correction to the motor power
        double motorPowerLeft = motorPowerDistance + motorPowerHeading;
        double motorPowerRight = motorPowerDistance - motorPowerHeading;

        // Constrain motor power to the min/max range and scale by maxSpeed
        motorPowerLeft = std::clamp(motorPowerLeft, -maxSpeed, maxSpeed);
        motorPowerRight = std::clamp(motorPowerRight, -maxSpeed, maxSpeed);

        // Set motor speeds for both sides
        robotDevices.leftMotors.move(motorPowerLeft);
        robotDevices.rightMotors.move(motorPowerRight);

        // Update last errors
        lastErrorDistance = errorDistance;
        lastErrorHeading = errorHeading;

        // Print the error values to the controller's screen using master.print
        master.print(0, 0, "Dist: %.2f", currentDistance);
        master.print(1, 0, "Heading: %.2f", errorHeading);

        // Check if distance target is reached or timeout occurred
        if (std::abs(errorDistance) <= tolerance_distance) {
            break;
        }

        // Check if timeout has been reached
        if (pros::millis() - startTime > timeout_ms) {
            master.print(0, 0, "Timeout reached!");  // Display timeout message
            break;
        }

        // Delay for stability
        pros::delay(10);
    }

    // Stop motors after movement
    robotDevices.leftMotors.move(0);
    robotDevices.rightMotors.move(0);
}




// Constants for PID
const double tolerance = 200.0;
const double kP = 0.035;   // Proportional constant
const double kI = 0;  // Integral constant
const double kD = 0;   // Derivative constant

// Target position in ticks
const double targetPosition = -3300;

// Maximum and minimum motor power limits
const int maxPower = 100;
const int minPower = -100;

// Prep Arm Function with PID Controller
void prepArm() {
    // Set brake modes
    c::motor_set_brake_mode(19, E_MOTOR_BRAKE_HOLD);
    c::motor_set_brake_mode(17, E_MOTOR_BRAKE_HOLD);

    // PID variables
    double error = 0.0;            // Difference between target and current position
    double lastError = 0.0;        // Error from the previous loop
    double integral = 0.0;         // Sum of all previous errors (I term)
    double derivative = 0.0;       // Rate of change of error (D term)
    double motorPower = 0.0;       // Motor power output

    while (true) {
        // Current position of the arm
        double currentPosition = robotDevices.liftRotation.get_position();

        // Calculate PID components
        error = targetPosition - currentPosition;            // Proportional term
        integral += error;                                   // Integral term
        derivative = error - lastError;                      // Derivative term

        // Compute motor power using PID formula
        motorPower = (kP * error) + (kI * integral) + (kD * derivative);

        // Constrain motor power to max/min limits
        motorPower = std::clamp(motorPower, (double)minPower, (double)maxPower);

        // Move motors with calculated power
        c::motor_move(19, motorPower);  // Adjust motor 19
        c::motor_move(17, -motorPower); // Adjust motor 17 (opposite direction)

        // Break if the arm is within the tolerance range
        if (fabs(error) <= tolerance) {
            break;
        }

        // Update last error
        lastError = error;

        // Delay to prevent overloading the CPU
        pros::delay(10);
    }

    // Stop the motors
    c::motor_move(19, 0);
    c::motor_move(17, 0);
}

// Score Arm Function
void scoreArm() {

		c::motor_set_brake_mode(19, E_MOTOR_BRAKE_HOLD); c::motor_set_brake_mode(17, E_MOTOR_BRAKE_HOLD);
	while (robotDevices.liftRotation.get_position() > -22000) {
			c::motor_move(18, 50);

		c::motor_move(19, -90); c::motor_move(17, 90);
		pros::delay(10);
	}
	c::motor_move(19, 0); c::motor_move(17, 0);

	c::motor_move(18, 0);
}


void ejectRing() {
	c::motor_move(17, 0);
	delay(300);
}

// Wrapper functions to start tasks
void startPrepArmTask() { pros::Task prepArmTask(prepArm); }

void startScoreArmTask() { pros::Task scoreArmTask(scoreArm); }

void startEjectTask() { pros::Task ejectTask(ejectRing); }

/*** @brief Load paths. */


bool colorSortBlue = false;
/**
 * @brief Runs Autonomous period functions.
 */
void autonomous() {
	robotDevices.liftRotation.set_position(359);

// Retrieve the selected autonomous mode from the BrainUI.
	int selectedMode = ui.selectedAuton;
	
	selectedMode = 0;
	// Blue Right - 0
	// Blue Left - 1
	// Red left - 2
	// Red Right - 3

	// Determine which autonomous routine to execute based on the selected mode.
	switch(selectedMode) {
		case 0:
		rotateToTarget(275, 900);
		delay(500);
		moveToDistance(14.0, 1800, 20);
		delay(500);
				moveToDistance(-12.0, 60000, 127);

			//rotateToTarget(170, 2000);
		//	delay(500);

		//	rotateToTarget(10, 2000);
		//	delay(500);
						//rotateToTarget(260, 2000);


			/*rotateToTarget(270);
									delay(500);

			rotateToTarget(180);*/


			break;
		case 1:

			break;
		case 2:
		
			break;
		case 3:
			
			break;
		case 4:
		
			break;
			
	}
}

/**
 * @brief Runs when initialized by VEX Field Controller.
 */
void competition_initialize() {
	robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST); robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST); robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST); robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);

	robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	robotDevices.liftMotor.tare_position();
    // Start calibration for both inertial sensors
    robotDevices.imu.reset();
    robotDevices.imu2.reset();

    // Wait for calibration to complete
    while (robotDevices.imu.is_calibrating() || robotDevices.imu2.is_calibrating()) {
        pros::delay(20); // Allow the system to process
    }


	// Draws autonomous selector UI on the Brain using LVGL,
	// an industry standard micro-controller screen UI library.
	ui.DisplayAutonSelectorUI();
}

/**
 * @brief Manages the drivetrain controls during the Driver Control period.
 * 
 * This function reads the analog inputs from the controller to control the robot's drivetrain
 * using a "tank drive" configuration. The tank drive configuration separates control of the left 
 * and right wheels, where each joystick controls one side of the drivetrain.
 */
void DrivetrainDriverControl() {

	// Read the Y-axis values from the controller's analog sticks.
	// rightY controls the right side of the drivetrain.
	// leftY controls the left side of the drivetrain.
	int rightY = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
	int leftY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);

	// Apply tank drive control to the drivetrain.
	// The tank method from lemlibs takes two arguments:
	// The first argument is the power for the left side (negative of leftY to match joystick direction).
	// The second argument is the power for the right side (rightY directly from joystick).
	robotDevices.chassis.tank(leftY, rightY);
}

/**
 * @brief Controls the mobile goal clamp during the Driver Control period.
 * 
 * This function manages the mobile goal clamp based on controller button inputs:
 * - Pressing the Y button will activate the clamp.
 * - Pressing the Right button will deactivate the clamp (release it).
 */
void MogoClampDriverControl() {

	// Check if the Y button is pressed on the controller.
	// If pressed, activate the clamp to secure the mobile goal.
	if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) { robotDevices.mogoClampPiston.set_value(true);  } 
	else  											 { robotDevices.mogoClampPiston.set_value(false); }

}

/**
 * @brief Controls the mobile goal clamp during the Driver Control period.
 * 
 * This function manages the mobile goal clamp based on controller button inputs:
 * - Pressing the Y button will activate the clamp.
 * - Pressing the Right button will deactivate the clamp (release it).
 */
void RingStopperDriverControl() {

	// Check if the Y button is pressed on the controller.
	// If pressed, activate the clamp to secure the mobile goal.
	if (master.get_digital(E_CONTROLLER_DIGITAL_B)) {
		 robotDevices.doinker.set_value(true);
	}

	// Check if the Right button is pressed on the controller.
	// If pressed, deactivate the clamp to release the mobile goal.
	if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
		 robotDevices.doinker.set_value(false);
	}
}


int pressCount = 1;
bool lastButtonState = false;
bool isPressed = false;
bool wasPressed = false;

/**
 * @brief Manages the high stake lift controls during the Driver Control period.
 * 
 * This function adjusts the position of the high stake lift based on controller button inputs:
 * - Pressing the L2 button will raise the lift.
 * - Pressing the L1 button will lower the lift.
 * - When neither button is pressed, the lift will be held in its current position.
 */
void LiftDriverControl() {
/*
	bool isPressed = master.get_digital(E_CONTROLLER_DIGITAL_L2);

	if (isPressed && !wasPressed) {
		pressCount = (pressCount + 1) % 4;
		switch(pressCount) {
			case 0: startPrepArmTask(); break;
			case 1: startScoreArmTask(); break;
			case 2: startReturnArmTask(); break;
			case 3: startrestArm(); break;
		}
	}

	wasPressed = isPressed;*/

		if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			startPrepArmTask();
		}


	// Check if the L2 button is pressed.
	// If pressed, command the lift to rise.
	if (master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
		// Create threads to run prepArm and scoreArm asynchronously
		//startScoreArmTask();
		c::motor_move(17, -127);
		
	}
	// Check if the L1 button is pressed.
	// If pressed and L2 is not pressed, command the lift to lower.
	else if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
		// Create threads to run prepArm and scoreArm asynchronously
		c::motor_move(17, 127);
	
	}
	// If neither L2 nor L1 is pressed.
	// Stop the lift to hold it in its current position.
	else {
		robotDevices.liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);	
	 c::motor_move(17, 0);
		c::motor_move(19, 0);
	}
}

/**
 * @brief Controls the ring intake system during the Driver Control period.
 * 
 * This function manages the intake system based on the following controller button inputs:
 * - Pressing the R1 button will spin the intake forward.
 * - Pressing the R2 button will spin the intake backward.
 * - When neither R1 nor R2 is pressed, the intake will coast to a stop.
 */
void IntakeDriverControl() {

	// Check if the R1 button is pressed.
	// If pressed, command the intake to spin forward with full power (100%).
	if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
		 c::motor_move(18, -127);
		 c::motor_move(5, -127);

	} 
	// Check if the R2 button is pressed.
	// If pressed and R1 is not pressed, command the intake to spin backward with full power (100%).
	else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		c::motor_move(5, -127);

	} 
	// If neither R1 nor R2 is pressed.
	// Command the intake to stop and coast.
	else {
				c::motor_move(18, 0);
				c::motor_move(5, 0);

		robot.intake.StopIntake();
	}
}

/**
 * @brief Executes the Driver Control (opcontrol) tasks while the robot is enabled.
 * 
 * This function runs in an infinite loop while the robot is under operator control.
 * It handles the control of the drivetrain, mobile goal clamp, lift, and intake systems.
 */
void opcontrol() {
	ui.DisplayMatchImage();
					 robotDevices.ringStopperPiston.set_value(false);

	/*pros::lcd::initialize(); // initialize brain screen
    robotDevices.chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", robotDevices.chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", robotDevices.chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", robotDevices.chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
*/

	colorSortBlue = true;
	robotDevices.liftRotation.set_position(359);

	robotDevices.frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.upperLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.lowerLeftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.upperRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	robotDevices.lowerRightMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
	/*
    pros::lcd::initialize(); // initialize brain screen
    robotDevices.chassis.calibrate(); // calibrate sensors
	while (robotDevices.imu.is_calibrating()) {
		pros::delay(10);
	}
	*/

    robotDevices.optical.set_led_pwm(100);

	// Infinite loop to continuously run operator control tasks.
	while (true) {
		/*
		double hue = robotDevices.optical.get_hue();
		if (robotDevices.optical.get_proximity() > 75) {
		if (colorSortBlue) 
		{
			if ((hue >=0 && hue <= 20) || (hue >=340 && hue <= 360)) {
					//delay(50);

				startEjectTask();
			}
		} else {
			if (hue >=120 && hue <= 200) {
					//delay(50);

				startEjectTask();
			}
		}
		}*/

		if (master.get_digital(E_CONTROLLER_DIGITAL_X)) {
			
					 robotDevices.ringStopperPiston.set_value(false);


		} 
		// Call function to handle drivetrain controls based on joystick input.
		DrivetrainDriverControl();
		
		// Call function to manage mobile goal clamp based on button input.
		MogoClampDriverControl();
		
		// Call function to control the lift based on button input.
		LiftDriverControl();
	
		// Call function to manage the intake system based on button input.
		IntakeDriverControl();

		RingStopperDriverControl();

		// Small delay to prevent the loop from running too fast
		// This helps to balance processing load and maintain responsiveness.
		delay(25);
	}
	
}