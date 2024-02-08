#include "FeelDriving.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

void FeelDriving::Execute()
{
	if (DidImpact())
	{
		device->Send(OWOGame::SensationsFactory::Create(100, .1f, ImpactIntensity())->WithMuscles(OWOGame::MusclesGroup::All()));
		lastVelocity = vehicle->Velocity();
		return;
	}

	if (vehicle->Velocity() <= 0) return;

	device->Send(OWOGame::SensationsFactory::Create(100, .1f, engine.IntensityAt(vehicle->Velocity()))->WithMuscles(SteeringMuscles()));
	lastVelocity = vehicle->Velocity();
}

bool FeelDriving::DidImpact()
{
	return ImpactIntensity() > 0;
}

OWOGame::MusclesGroup FeelDriving::SteeringMuscles()
{
	return vehicle->DrivingForward() ? OWOGame::MusclesGroup::Back() : OWOGame::MusclesGroup::Front();
}

int FeelDriving::ImpactIntensity()
{
	return forImpacts.IntensityAt(lastVelocity - vehicle->Velocity());
}
