#include "MockVehicle.h"

void MockVehicle::DriveAt(int newVelocity)
{
	velocity = newVelocity;
}

int MockVehicle::Velocity()
{
	return velocity;
}