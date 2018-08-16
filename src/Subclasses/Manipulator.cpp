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
	xbox = new XboxController{ 1 };
	outtake = new WPI_TalonSRX(3);
	intake = new Talon{ 2 };
	climber = new Talon{ 4 };
	gearServoLeft = new Servo { 3 };
	gearServoRight = new Servo { 4 };
	flip = false;
	toggle = false;
}

void ManipulatorManager::manipulate() {
	if(xbox->GetRawButton(3) == true) {
		outtake->Set(0.5);
	}
	else if(xbox->GetRawButton(4) == true) {
		outtake->Set(-0.5);
	}
	else {
		outtake->Set(0);
	}

	if(stick->GetRawButton(11))
	{
		climber->Set(fabs(stick->GetY()));
	}
	else
	{
		climber->Set(0);
	}

	if(xbox->GetRawButton(1) == true)
	{
		intake->Set(0.5);
	}
	else if(xbox->GetRawButton(2) == true)
	{
		intake->Set(-0.5);
	}
	else
	{
		intake->Set(0);
	}

	if(stick->GetRawButton(3) && !toggle)
		{
			flip = !flip;
			toggle = true;
		}
	else if(!stick->GetRawButton(3) && toggle)
		{
			toggle = false;
		}

	if(flip) {
		gearServoLeft->SetAngle(90);
		gearServoRight->SetAngle(0);
		}
	else if(!flip) {
		gearServoLeft->SetAngle(0);
		gearServoRight->SetAngle(110);
		}
}
