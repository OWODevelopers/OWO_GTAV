#include "FeelRecoil.h"
#include "OWOAPI/Domain/SensationsFactory.h"
#include "OWOAPI/Domain/Muscle.h"

void FeelRecoil::ResetEquipedWeapon()
{
	equipedWeapon = inventory->CurrentWeapon();
	UpdateAmmo();
}

void FeelRecoil::SendRecoilSensation()
{
	auto sensation = RecoilSensation();
	sensation->SetPriority(FeelRecoil::Priority);
	owo->Send(movePtr(sensation));
}

bool FeelRecoil::DidShoot()
{
	return inventory->CurrentAmmo() < ammo;
}

bool FeelRecoil::DidChangeWeapon()
{
	return equipedWeapon != inventory->CurrentWeapon();
}

void FeelRecoil::UpdateAmmo()
{
	ammo = inventory->CurrentAmmo();
}

uniquePtr<OWOGame::Sensation> FeelRecoil::RecoilSensation()
{
	for (auto sensation : sensations)
	{
		if (sensation.ContainsWeapon(equipedWeapon))
			return sensation.ToBeFelt();
	} 

	return OWOGame::SensationsParser::Parse("12");
}

void FeelRecoil::Execute()
{
	if (!inventory->HoldingWeapon()) return;

	if (DidChangeWeapon())
	{
		ResetEquipedWeapon();
		return;
	}

	if (DidShoot())
		SendRecoilSensation();

	UpdateAmmo();
}