#include "FeelDriving.h"
#include "../OWOAPI/Domain/SensationsFactory.h"


void FeelDriving::Execute()
{
	if (!vehicle->IsInVehicle()) {
		lastVelocity = 0;
		return;
	}

	if (engine.ImpactStrongEnough(lastVelocity, vehicle->Velocity())) 
	{
		device->Send(OWOGame::SensationsFactory::Create(100, .1f, engine.ImpactIntensity(lastVelocity, vehicle->Velocity()))->WithMuscles(OWOGame::MusclesGroup::All()));
		lastVelocity = vehicle->Velocity();
		return;
	}

	if (vehicle->Velocity() <= 0) return;

	auto whereFeels = vehicle->DrivingForward() ? OWOGame::MusclesGroup::Back() : OWOGame::MusclesGroup::Front();
	device->Send(OWOGame::SensationsFactory::Create(100, .1f, engine.IntensityAt(vehicle->Velocity()))->WithMuscles(whereFeels));
	lastVelocity = vehicle->Velocity();
}