/*
 * drive.h
 *
 *  Created on: Jul 16, 2018
 *      Author: RTR
 */

#pragma once

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "AHRS.h"

class DriveManager {
private:
	//Initializations
	WPI_TalonSRX *rf;
	WPI_TalonSRX *rr;
	WPI_TalonSRX *lf;
	WPI_TalonSRX *lr;

	Joystick *stick;
	XboxController *xbox;

	AHRS *ahrs;

	MecanumDrive *m_robotDrive;
public:
	DriveManager();
	void driveTrain();
	//Control variables for driving
	double driveVelX;
	double driveVelY;
	double driveVelRotation;
	bool intakeIn;
	bool intakeOut;
	bool outtakeUp;
	bool outtakeDown;
};

