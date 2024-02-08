#pragma once
#include "../OWOAPI/Controller/OWO.h"
#include "Vehicle.h"
#include "VehicleEngine.h"

class FeelDriving
{
private:
	sharedPtr<OWOGame::OWO> device = nullptr;
	sharedPtr<Vehicle> vehicle = nullptr;
	VehicleEngine engine = VehicleEngine(0,0,0,0);
	VehicleEngine forImpact = VehicleEngine(10,60,40,90);
	int lastVelocity;

	int ImpactIntensity();
public:
	FeelDriving(sharedPtr<OWOGame::OWO> device, sharedPtr<Vehicle> vehicle, VehicleEngine engine) : device(device), vehicle(vehicle), engine(engine) {}
	void Execute();
};