#pragma once
#include "Vehicle.h"

class MockVehicle : public Vehicle
{
private:
	int velocity = 0;
	bool drivingForward = true;
public:
	
	void DriveAt(int newVelocity);
	void DriveBackwards();
	int Velocity() override;
	bool DrivingForward() override;
};