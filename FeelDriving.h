#pragma once
#include "../OWOAPI/Controller/OWO.h"
#include "Vehicle.h"

class FeelDriving
{
private:
	sharedPtr<OWOGame::OWO> device = nullptr;
	sharedPtr<Vehicle> vehicle = nullptr;

public:
	FeelDriving(sharedPtr<OWOGame::OWO> device, sharedPtr<Vehicle> vehicle) : device(device), vehicle(vehicle) {}
	void Execute();
};