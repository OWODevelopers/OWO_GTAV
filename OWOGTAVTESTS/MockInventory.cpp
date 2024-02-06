#include "MockInventory.h"

int MockInventory::CurrentAmmo()
{
	return ammo;
}

int MockInventory::CurrentWeapon()
{
	return currentWeapon;
}

uniquePtr<OWOGame::Sensation> MockInventory::RecoilSensation()
{
	return movePtr(toBeFelt->Clone());
}
