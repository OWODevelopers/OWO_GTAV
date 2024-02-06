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
	auto sensation = playerInventory->RecoilSensation();
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