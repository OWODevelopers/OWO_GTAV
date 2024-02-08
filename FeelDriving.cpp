#include "FeelDriving.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

void FeelDriving::Execute()
{
	if (vehicle->Velocity() <= 0)return;


	device->Send(OWOGame::SensationsFactory::Create(100, .1f, engine.IntensityAt(vehicle->Velocity()))->WithMuscles(OWOGame::MusclesGroup::Back()));
}