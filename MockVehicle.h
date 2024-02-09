#pragma once
#include "OWOVehicle.h"

class MockVehicle : public OWOVehicle
{
private:
	int velocity = 0;
	bool drivingForward = true;
	bool isDriving = true;
	int steer = 0;
public:
	
	void DriveAt(int newVelocity);
	void DriveBackwards();
	void ExitTheVehicle();
	void EnterTheVehicle();
	void TurnRight(int howMuch);

	int Velocity() override;
	bool DrivingForward() override;
	bool IsDriving() override;
	int SteeringAmount() override;
};