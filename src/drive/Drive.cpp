/*
 * drive.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: RTR
 */

#include <iostream>
#include <string>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <Joystick.h>
#include "drive/Drive.h"
#include <Drive/DifferentialDrive.h>
#include <DriverStation.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "AHRS.h"

DriveManager::DriveManager() {
	rf = new WPI_TalonSRX(1);
	rr = new WPI_TalonSRX(2);
	lf = new WPI_TalonSRX(3);
	lr = new WPI_TalonSRX(4);
	this->stick = new Joystick{ 0 };
	xbox = new XboxController { 1 };

	try{
		ahrs = new AHRS(SPI::Port::kMXP);
	}
	catch(std::exception ex){
		std::string err_string = "Error initalizing navX-MXP: ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}
	ahrs->Reset();

	m_robotDrive = new MecanumDrive(*rf, *lf);
//	m_robotDrive->SetSafetyEnabled(true);
}

void DriveManager::driveTrain() {

}
