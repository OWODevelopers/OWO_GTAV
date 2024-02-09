#include "MockVehicle.h"

void MockVehicle::DriveAt(int newVelocity)
{
	velocity = newVelocity;
}

void MockVehicle::DriveBackwards()
{
	drivingForward = false;
}

void MockVehicle::ExitTheVehicle()
{
	isDriving = false;
}

void MockVehicle::EnterTheVehicle()
{
	isDriving = true;
}

void MockVehicle::TurnRight(int howMuch)
{
	steer = howMuch;
}

int MockVehicle::Velocity()
{
	return velocity;
}

bool MockVehicle::DrivingForward()
{
	return drivingForward;
}

bool MockVehicle::IsDriving()
{
	return isDriving;
}

int MockVehicle::SteeringAmount()
{
	return steer;
}