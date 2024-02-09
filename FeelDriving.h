#pragma once
#include "../OWOAPI/Controller/OWO.h"
#include "OWOVehicle.h"
#include "IntensityLerp.h"

class FeelDriving
{
private:
	sharedPtr<OWOGame::OWO> device = nullptr;
	sharedPtr<OWOVehicle> vehicle = nullptr;
	IntensityLerp engine = IntensityLerp(0,0,0,0);
	IntensityLerp forImpacts = IntensityLerp(10,60,40,90);
	IntensityLerp forSteering = IntensityLerp(10,60,40,90);
	int lastVelocity;

	int ImpactIntensity();
	int SteeringIntensity();
	int VelocityIntensity();
	bool DidImpact();
	bool CanFeelDriving();

	uniquePtr<OWOGame::Sensation> Sensation();
	uniquePtr<OWOGame::Sensation> DrivingSensation();
	uniquePtr<OWOGame::Sensation> ImpactSensation();

	OWOGame::MusclesGroup SteeringMuscles();
	OWOGame::MusclesGroup TurningTowardsMuscles();
	OWOGame::MusclesGroup TurningAgainstMuscles();

	OWOGame::MusclesGroup Right();
	OWOGame::MusclesGroup Left();
public:
	FeelDriving(sharedPtr<OWOGame::OWO> device, sharedPtr<OWOVehicle> vehicle, IntensityLerp engine, IntensityLerp forImpacts, IntensityLerp forSteering)
		: device(device), vehicle(vehicle), engine(engine), forImpacts(forImpacts), forSteering(forSteering) {}

	static const int Priority = 2;
	void Execute();
};