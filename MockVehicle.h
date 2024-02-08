#pragma once
#include "Vehicle.h"

class MockVehicle : public Vehicle
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