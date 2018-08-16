/*
 * Manipulator.h
 *
 *  Created on: Jul 30, 2018
 *      Author: RTR
 */

#pragma once

#ifndef SRC_SUBCLASSES_MANIPULATOR_H_
#define SRC_SUBCLASSES_MANIPULATOR_H_

class ManipulatorManager {
private:
	Joystick *stick;
	XboxController *xbox;
	WPI_TalonSRX *outtake;
	Talon *intake;
	Talon *climber;
	Servo *gearServoLeft;
	Servo *gearServoRight;
	bool flip;
	bool toggle;

public:
	ManipulatorManager();
	void manipulate();
};



#endif /* SRC_SUBCLASSES_MANIPULATOR_H_ */
