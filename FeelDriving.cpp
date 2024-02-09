#include "FeelDriving.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "Debug.h"

void FeelDriving::Execute()
{
	if (!vehicle->IsDriving())
	{
		lastVelocity = 0;
		return;
	} 

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
	auto muscles = vehicle->DrivingForward() ? OWOGame::MusclesGroup::Back() : OWOGame::MusclesGroup::Front();

	if(vehicle->SteeringAmount() > 0)
		return muscles + OWOGame::MusclesGroup({OWOGame::Muscle::Arm_R()});
	
	return muscles;
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