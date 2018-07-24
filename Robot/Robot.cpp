/*------------------------------------------*/
/* Artemus 2018 rewrite                     */
/* Created by: Casey Jones                  */
/* artemus code re-written for 2018 firmware*/
/* Motor type: Mixed                        */
/*------------------------------------------*/

#include <Drive/Drive.h>
#include <WPILib.h>
#include <Joystick.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>


class Robot : public frc::IterativeRobot {
public:
	Robot() {
		this->driveManager = new DriveManager();
	}
private:
	DriveManager *driveManager;

	void RobotInit() {
	}

	void TeleopInit() {}

	void TeleopPeriodic() {}

	void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
};

START_ROBOT_CLASS(Robot)
