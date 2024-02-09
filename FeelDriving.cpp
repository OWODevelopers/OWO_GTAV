#include "FeelDriving.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "Debug.h"

using namespace OWOGame;

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
	auto muscles = vehicle->DrivingForward() ? 
		OWOGame::MusclesGroup::Back().WithIntensity(engine.IntensityAt(vehicle->Velocity()))
		: OWOGame::MusclesGroup::Front().WithIntensity(engine.IntensityAt(vehicle->Velocity()));

	if (vehicle->SteeringAmount() > 0)
		return muscles + Right_Back().WithIntensity(60) - Left_Back().WithIntensity(60);

	if (vehicle->SteeringAmount() < 0)
		return muscles + Left_Back().WithIntensity(50);

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

	return OWOGame::SensationsFactory::Create(100, .1f)->WithMuscles(SteeringMuscles());
}

int FeelDriving::ImpactIntensity()
{
	return forImpacts.IntensityAt(lastVelocity - vehicle->Velocity());
}

OWOGame::MusclesGroup FeelDriving::Right_Back()
{
	return  MusclesGroup({ Muscle::Dorsal_R(),Muscle::Lumbar_R(),Muscle::Arm_R() });
}

OWOGame::MusclesGroup FeelDriving::Left_Back()
{
	return  MusclesGroup({ Muscle::Dorsal_L(),Muscle::Lumbar_L(),Muscle::Arm_L() });
}