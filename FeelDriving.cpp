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
	auto result = vehicle->DrivingForward() ? OWOGame::MusclesGroup::Back() : OWOGame::MusclesGroup::Front();

	return result.WithIntensity(VelocityIntensity()) + TurningTowardsMuscles().WithIntensity(SteeringIntensity()) - TurningAgainstMuscles().WithIntensity(SteeringIntensity());
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

int FeelDriving::SteeringIntensity()
{
	return forSteering.IntensityAt(abs(vehicle->SteeringAmount()));
}

int FeelDriving::VelocityIntensity()
{
	return engine.IntensityAt(vehicle->Velocity());
}

OWOGame::MusclesGroup FeelDriving::Right()
{
	if (vehicle->DrivingForward())
		return  MusclesGroup({ Muscle::Dorsal_R(),Muscle::Lumbar_R(),Muscle::Arm_R() });

	return  MusclesGroup({ Muscle::Abdominal_R(),Muscle::Pectoral_R(),Muscle::Arm_R() });
}

OWOGame::MusclesGroup FeelDriving::Left()
{
	if (vehicle->DrivingForward())
		return  MusclesGroup({ Muscle::Dorsal_L(),Muscle::Lumbar_L(),Muscle::Arm_L() });

	return  MusclesGroup({ Muscle::Abdominal_L(),Muscle::Pectoral_L(),Muscle::Arm_L() });
}

OWOGame::MusclesGroup FeelDriving::TurningTowardsMuscles()
{
	if (vehicle->SteeringAmount() > 0) return Right();
	if (vehicle->SteeringAmount() < 0) return Left();
	return MusclesGroup({});
}

OWOGame::MusclesGroup FeelDriving::TurningAgainstMuscles()
{
	if (vehicle->SteeringAmount() > 0) return Left();
	if (vehicle->SteeringAmount() < 0) return Right();
	return MusclesGroup({});
}