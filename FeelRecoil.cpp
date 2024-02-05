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
		auto sensation = playerInventory->RecoilSensation();
		sensation->SetPriority(FeelRecoil::Priority);
		owo->Send(movePtr(sensation));
	}

	lastAmmo = playerInventory->CurrentAmmo();
}
