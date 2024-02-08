#include "FeelDriving.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

void FeelDriving::Execute()
{
	if (vehicle->Velocity() <= 0)return;

	device->Send(OWOGame::SensationsFactory::Create());
}