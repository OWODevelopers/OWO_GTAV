#pragma once
#include "OWOVehicle.h"

class MockVehicle : public OWOVehicle
{
private:
	int velocity = 0;
	bool drivingForward = true;
	bool isDriving = true;
public:
	
	void DriveAt(int newVelocity);
	void DriveBackwards();
	void ExitTheVehicle();
	void EnterTheVehicle();

	int Velocity() override;
	bool DrivingForward() override;
	bool IsDriving() override;
};