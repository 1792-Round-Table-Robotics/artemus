/* Drive.cpp
 * Created on: Jul 16, 2018
 * Original Creator: Casey Jones
 * Rio Firmware Version at Creation: 2018
 * FRC Library Version at Creation: 2018
 * Motor Controller Types in Use: TalonSRX
 * Motor Controller Firmware Version at Creation:
 *
 */

#include <iostream>
#include <string>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <Joystick.h>
#include <Drive/DifferentialDrive.h>
#include <Drive/Drive.h>
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
	driveVelX = 0;
	driveVelY = 0;
	driveVelRotation = 0;
	intakeIn = false;
	intakeOut = false;
	outtakeUp = false;
	outtakeDown = false;

	try{
		ahrs = new AHRS(SPI::Port::kMXP);
	}
	catch(std::exception ex){
		std::string err_string = "Error initalizing navX-MXP: ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}
	ahrs->Reset();

	m_robotDrive = new MecanumDrive(*lf, *lr, *rf, *rr);
//	m_robotDrive->SetSafetyEnabled(true);
}

void DriveManager::driveTrain() {

}
