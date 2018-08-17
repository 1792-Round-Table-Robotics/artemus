/*
 * pixy.h
 *
 *  Created on: Aug 17, 2018
 *      Author: RTR
 */

#ifndef SRC_SUBCLASSES_PIXY_H_
#define SRC_SUBCLASSES_PIXY_H_

class PixyManager {

private:
	WPI_TalonSRX *rf;
	WPI_TalonSRX *rr;
	WPI_TalonSRX *lf;
	WPI_TalonSRX *lr;

	MecanumDrive *m_robotDrive;
	AHRS *ahrs;

	float Pixyx1;
	float Pixyy1;
	float Pixyh1;
	float Pixyw1;
	float Pixyx2;
	float Pixyy2;
	float Pixyh2;
	float Pixyw2;

	bool PixyNoTargets;

	float Xmid;
	float XAlmostmid;
	float Pixyx2Almost;
	float Pixyw1Almost;
	float Pixyx1Almost;
	float StrafePct;
	float HorzTune;
	float FrdRevPct;
	float FrdRevTune;
	bool targetHoldingAngle;
	int targetAngel;
	float TurnTune;

	I2C *i2cthing;

public:
	PixyManager();
	void pixyFunct();
	void pixyDriveTakeover();

};

#endif /* SRC_SUBCLASSES_PIXY_H_ */
