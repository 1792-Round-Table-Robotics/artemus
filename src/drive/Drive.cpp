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
#include <DriverStation.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "AHRS.h"
#include <RobotDrive.h>
#include <Subclasses/Drive.h>

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
	gyroAngle = 0;

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
	if (stick->GetRawAxis(1) < 0.05 and stick->GetRawAxis(1) > -0.05) {
		driveVelX = 0;
		}
		else {
			driveVelX = stick->GetRawAxis(1);
		}

	if (stick->GetRawAxis(2) < 0.05 and stick->GetRawAxis(2) > -0.05) {
			driveVelY = 0;
		}
		else{
			driveVelY = stick->GetRawAxis(2);
		}

	if (stick->GetRawAxis(3) < 0.05 and stick->GetRawAxis(3) > -0.05) {
			driveVelY = 0;
		}
		else{
			driveVelY = stick->GetRawAxis(3);
		}


	//driveVelX = stick->GetRawAxis(1);
	//driveVelY = stick->GetRawAxis(2);
    //driveVelRotation = stick->GetRawAxis(3);
	gyroAngle = ahrs->GetAngle();

	m_robotDrive->DriveCartesian(driveVelX, driveVelY, driveVelRotation, gyroAngle);
}
