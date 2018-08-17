/*
 * Pixy.cpp
 *
 *  Created on: Aug 17, 2018
 *      Author: RTR
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
#include <Subclasses/Pixy.h>

#define I2C_SLAVE_ADR 0x64

typedef unsigned char byte;

PixyManager::PixyManager() {
	rf = new WPI_TalonSRX(2);
	rr = new WPI_TalonSRX(1);
	lf = new WPI_TalonSRX(5);
	lr = new WPI_TalonSRX(4);

	m_robotDrive = new MecanumDrive(*lf, *lr, *rf, *rr);

	Pixyx1 = 0;
	Pixyy1 = 0;
	Pixyh1 = 0;
	Pixyw1 = 0;
	Pixyx2 = 0;
	Pixyy2 = 0;
	Pixyh2 = 0;
	Pixyw2 = 0;

	PixyNoTargets = true;

	Xmid = 0;
	XAlmostmid = 0;
	Pixyx2Almost = 301;
	Pixyw1Almost = 29;
	Pixyx1Almost = 214;
	StrafePct = 0;
	HorzTune = .02;
	FrdRevPct = 0;
	FrdRevTune = .02;
	targetHoldingAngle = false;
	targetAngel = 0;
	TurnTune = .663306452;

	i2cthing = new I2C(I2C::kOnboard, I2C_SLAVE_ADR);

	try{
		ahrs = new AHRS(SPI::Port::kMXP);
	}
	catch(std::exception ex){
		std::string err_string = "Error initalizing navX-MXP: ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}
	ahrs->Reset();
}

void PixyManager::pixyFunct() {
	byte buff[31];
	int translate[15];

	i2cthing->Read(0x64, 31, buff);

	if(!(buff[1] == buff[2]))
	{
		if(buff[0] == 0)
		{
			for(int i = 0;i < 30;i++)
			{
				buff[i] = buff[i + 1];
			}
		}
	}
	for(int i = 0;i < 15;i++)
	{
		translate[i] = buff[(2 * i) + 1] * 256 + buff[2 * i];
	}
	if(translate[0] == 43605 && translate[1] == 43605 && translate[8] == 43605)
	{
		Pixyx1 = translate[4];
		Pixyy1 = translate[5];
		Pixyw1 = translate[6];
		Pixyh1 = translate[7];

		Pixyx2 = translate[11];
		Pixyy2 = translate[12];
		Pixyw2 = translate[13];
		Pixyh2 = translate[14];
		PixyNoTargets = false;
		SmartDashboard::PutBoolean("PixyNoTargets", PixyNoTargets);
	}
	else if(translate[0] == 0 && translate[1] == 0 && translate[8] == 0)
	{
		//Target Non Existant
		PixyNoTargets = true;
		SmartDashboard::PutBoolean("PixyNoTargets", PixyNoTargets);
	}


	SmartDashboard::PutNumber("Pixyx1", Pixyx1);
	SmartDashboard::PutNumber("Pixyy1", Pixyy1);
	SmartDashboard::PutNumber("Pixyw1", Pixyw1);
	SmartDashboard::PutNumber("Pixyh1", Pixyh1);
	SmartDashboard::PutNumber("Pixyx2", Pixyx2);
	SmartDashboard::PutNumber("Pixyy2", Pixyy2);
	SmartDashboard::PutNumber("Pixyw2", Pixyw2);
	SmartDashboard::PutNumber("Pixyh2", Pixyh2);
	frc::SmartDashboard::PutNumber("Make Sure Updating", 676);
}

void PixyManager::pixyDriveTakeover() {
	Xmid = ((Pixyx1 + Pixyx2) / 2);
			XAlmostmid = ((Pixyx1Almost + Pixyx2Almost) / 2) - 15;
			StrafePct = (XAlmostmid - Xmid) * HorzTune;
			//StrafePct = StrafePct/fabs(StrafePct);
			//StrafePct = StrafePct *.5;

			FrdRevPct = (Pixyw1Almost - Pixyw1) * FrdRevTune; //70
			//FrdRevPct = FrdRevPct/fabs(FrdRevPct);
			//FrdRevPct = FrdRevPct *.125;
			if(PixyNoTargets)
			{
				StrafePct = 0;
				FrdRevPct = 0;
				frc::SmartDashboard::PutString("Feedback: ", "Lost");
			}

			frc::SmartDashboard::PutNumber("Fused Heading", ahrs->GetFusedHeading());

			if(targetHoldingAngle == false)
			{

				if((sin(ahrs->GetFusedHeading() * (3.141 / 180)) > sin(-30 * (3.141 / 180))) && (sin(ahrs->GetFusedHeading() * (3.141 / 180)) < sin(30 * (3.141 / 180))))
				{
					targetAngel = 1;
				}
				else if(ahrs->GetFusedHeading() > 270 && ahrs->GetFusedHeading() < 330)
				{
					targetAngel = 2;
				}
				else if(ahrs->GetFusedHeading() > 30 && ahrs->GetFusedHeading() < 90)
				{
					targetAngel = 3;
				}
				else
				{
					targetAngel = 0;
				}

				targetHoldingAngle = true;
			}

			float testAng = 0;

			if(targetAngel == 1)
			{
				frc::SmartDashboard::PutString("Feedback: ", "Targeting Mid");
				testAng = (sin(0 * (3.141 / 180)) - sin(ahrs->GetFusedHeading() * (3.141 / 180))) * 2.1;
				frc::SmartDashboard::PutNumber("testAng", testAng);
			}
			else if(targetAngel == 2)
			{
				frc::SmartDashboard::PutString("Feedback: ", "Targeting -60");
				testAng = ((300 - ahrs->GetFusedHeading()) / 180) * 4;
				frc::SmartDashboard::PutNumber("testAng", testAng);
			}
			else if(targetAngel == 3)
			{
				frc::SmartDashboard::PutString("Feedback: ", "Targeting 60");
				testAng = ((60 - ahrs->GetFusedHeading()) / 180) * 4;
				frc::SmartDashboard::PutNumber("testAng", testAng);
			}
			else
			{
				frc::SmartDashboard::PutString("Feedback: ", "Targeting NULL");
				testAng = 0;
				StrafePct = 0;
				FrdRevPct = 0;
			}

			frc::SmartDashboard::PutNumber("StrafePct", StrafePct);
			frc::SmartDashboard::PutNumber("FrdRevPct", FrdRevPct);

			//m_robotDrive.MecanumDrive_Cartesian(StrafePct, FrdRevPct, (((heldAng - currentAngle) / 180) * 4), 0);
			m_robotDrive->DriveCartesian(StrafePct, FrdRevPct, -testAng * TurnTune, 0);
}
