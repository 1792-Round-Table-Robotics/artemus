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

public:
	ManipulatorManager();
	void manipulate();
	WPI_TalonSRX *outtake;
	Talon *intake;
};



#endif /* SRC_SUBCLASSES_MANIPULATOR_H_ */
