#include "FeelDriving.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

void FeelDriving::Execute()
{
	if (!CanFeelDriving()) return;

	device->Send(DrivingSensation());
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

bool FeelDriving::CanFeelDriving()
{
	return DidImpact() || vehicle->Velocity() > 0;
}

uniquePtr<OWOGame::Sensation> FeelDriving::DrivingSensation()
{
	if (DidImpact())
		return OWOGame::SensationsFactory::Create(100, .1f, ImpactIntensity())->WithMuscles(OWOGame::MusclesGroup::All());

	return OWOGame::SensationsFactory::Create(100, .1f, engine.IntensityAt(vehicle->Velocity()))->WithMuscles(SteeringMuscles());
}

int FeelDriving::ImpactIntensity()
{
	return forImpacts.IntensityAt(lastVelocity - vehicle->Velocity());
}