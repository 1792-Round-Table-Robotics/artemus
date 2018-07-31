/*------------------------------------------*/
/* Artemus 2018 rewrite                     */
/* Created by: Casey Jones                  */
/* artemus code re-written for 2018 firmware*/
/* Motor type: Mixed                        */
/*------------------------------------------*/

#include <WPILib.h>
#include <Joystick.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subclasses/Drive.h>
#include <Subclasses/Manipulator.h>


class Robot : public frc::IterativeRobot {
public:
	Robot() {
		this->driveManager = new DriveManager();
		this->manipulatorManager = new ManipulatorManager();
	}
private:
	DriveManager *driveManager;
	ManipulatorManager *manipulatorManager;

	void RobotInit() {
	}

	void TeleopInit() {}

	void TeleopPeriodic() {
		driveManager->driveTrain();
	}

	void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
};

START_ROBOT_CLASS(Robot)
