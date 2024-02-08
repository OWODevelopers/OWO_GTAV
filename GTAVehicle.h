#pragma once
#include "OWOVehicle.h"

class GTAVehicle : public OWOVehicle
{
	int Velocity() override;
	bool DrivingForward() override;
	bool IsDriving() override;
};