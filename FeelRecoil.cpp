#include "FeelRecoil.h"
#include "OWOAPI/Domain/SensationsFactory.h"
#include "OWOAPI/Domain/Muscle.h"

void FeelRecoil::ResetEquipedWeapon()
{
	equipedWeapon = playerInventory->CurrentWeapon();
	UpdateAmmo();
}

void FeelRecoil::SendRecoilSensation()
{
	auto sensation = SensationOf(equipedWeapon);
	sensation->SetPriority(FeelRecoil::Priority);
	owo->Send(movePtr(sensation));
}

bool FeelRecoil::DidShoot()
{
	return playerInventory->CurrentAmmo() < ammo;
}

bool FeelRecoil::DidChangeWeapon()
{
	return equipedWeapon != playerInventory->CurrentWeapon();
}

void FeelRecoil::UpdateAmmo()
{
	ammo = playerInventory->CurrentAmmo();
}

uniquePtr<OWOGame::Sensation> FeelRecoil::SensationOf(int weapon)
{
	if (sensations.ContainsWeapon(weapon))
		return sensations.ToBeFelt();

	return OWOGame::SensationsParser::Parse("5");
}

void FeelRecoil::Execute()
{
	if (DidChangeWeapon())
	{
		ResetEquipedWeapon();
		return;
	}

	if (DidShoot())
		SendRecoilSensation();

	UpdateAmmo();
}