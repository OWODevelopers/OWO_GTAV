#pragma once
#include "../OWOAPI/Controller/OWO.h"
#include "Vehicle.h"
#include "VehicleEngine.h"

class FeelDriving
{
private:
	sharedPtr<OWOGame::OWO> device = nullptr;
	sharedPtr<Vehicle> vehicle = nullptr;
	VehicleCalculator engine = VehicleCalculator(0,0,0,0,0,0);
	int lastVelocity = 0;

public:
	FeelDriving(sharedPtr<OWOGame::OWO> device, sharedPtr<Vehicle> vehicle, VehicleCalculator engine) : device(device), vehicle(vehicle), engine(engine) {}
	void Execute();
};