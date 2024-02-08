#pragma once
#include "Vehicle.h"

class MockVehicle : public Vehicle
{
private:
	int velocity = 0;
public:
	
	void DriveAt(int newVelocity);
	int Velocity() override;
};

