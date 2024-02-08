#include "FeelDriving.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

int FeelDriving::ImpactIntensity()
{
	return lastVelocity - vehicle->Velocity();
}

void FeelDriving::Execute()
{
	if (ImpactIntensity() > 20) 
	{
		device->Send(OWOGame::SensationsFactory::Create()->WithMuscles(OWOGame::MusclesGroup::All()));
		return;
	}

	if (vehicle->Velocity() <= 0) return;

	auto whereFeels = vehicle->DrivingForward() ? OWOGame::MusclesGroup::Back() : OWOGame::MusclesGroup::Front();
	device->Send(OWOGame::SensationsFactory::Create(100, .1f, engine.IntensityAt(vehicle->Velocity()))->WithMuscles(whereFeels));
	lastVelocity = vehicle->Velocity();
}