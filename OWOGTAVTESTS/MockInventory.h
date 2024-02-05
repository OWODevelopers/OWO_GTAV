#pragma once
#include "../PlayerInventory.h"

class MockInventory : public PlayerInventory{
public:
	int ammo = 0;
	int currentWeapon = 0;

	int CurrentAmmo() override;
	int CurrentWeapon() override;
};