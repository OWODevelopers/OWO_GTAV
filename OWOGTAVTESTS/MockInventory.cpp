#include "MockInventory.h"

int MockInventory::CurrentAmmo()
{
	return ammo;
}

int MockInventory::CurrentWeapon()
{
	return currentWeapon;
}

void MockInventory::Shoot()
{
	ammo--;
}

void MockInventory::Equip(int weapon)
{
	currentWeapon = weapon;
}

void MockInventory::Reload(int clipSize)
{
	ammo = clipSize;
}
