#pragma once
#include "../OWOAPI/Controller/OWO.h"
#include "OWOVehicle.h"
#include "VehicleEngine.h"

class FeelDriving
{
private:
	sharedPtr<OWOGame::OWO> device = nullptr;
	sharedPtr<OWOVehicle> vehicle = nullptr;
	VehicleCalculator engine = VehicleCalculator(0,0,0,0,0,0);
	int lastVelocity = 0;

public:
	FeelDriving(sharedPtr<OWOGame::OWO> device, sharedPtr<OWOVehicle> vehicle, VehicleCalculator engine) : device(device), vehicle(vehicle), engine(engine) {}
	void Execute();
};