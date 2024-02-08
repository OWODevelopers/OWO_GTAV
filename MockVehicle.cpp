#include "MockVehicle.h"

void MockVehicle::DriveAt(int newVelocity)
{
	velocity = newVelocity;
}

void MockVehicle::DriveBackwards()
{
	drivingForward = false;
}

int MockVehicle::Velocity()
{
	return velocity;
}

bool MockVehicle::DrivingForward()
{
	return drivingForward;
}