/* Manipulator.cpp
 * Created on: Jul 30, 2018
 * Original Creator: Casey Jones
 * Rio Firmware Version at Creation: 2018
 * FRC Library Version at Creation: 2018
 * Motor Controller Types in Use: TalonSRX, victor
 * Motor Controller Firmware Version at Creation:2018
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
#include <Subclasses/Manipulator.h>

ManipulatorManager::ManipulatorManager() {
	this->stick = new Joystick{ 0 };
	outtake = new WPI_TalonSRX(5);
	intake = new Talon(1);
}

void ManipulatorManager::manipulate() {
	if(stick->GetRawButton(3) == true) {
		outtake->Set(0.5);
	}
	else if(stick->GetRawButton(4) == true) {
		outtake->Set(-0.5);
	}
	else {
		outtake->Set(0);
	}
}
