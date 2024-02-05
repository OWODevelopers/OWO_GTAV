#include "FeelRecoil.h"
#include "OWOAPI/Domain/SensationsFactory.h"
#include "OWOAPI/Domain/Muscle.h"

void FeelRecoil::Execute()
{
	if (lastWeapon != playerInventory->CurrentWeapon())
	{
		lastWeapon = playerInventory->CurrentWeapon();
		lastAmmo = playerInventory->CurrentAmmo();
		return;
	}

	if (playerInventory->CurrentAmmo() < lastAmmo)
	{
		owo->Send(OWOGame::SensationsFactory::Create()->WithMuscles({OWOGame::Muscle::Abdominal_L()}));
	}

	lastAmmo = playerInventory->CurrentAmmo();
}
