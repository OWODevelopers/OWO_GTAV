#pragma once
#include "PlayerInventory.h"

class GTAInventory : public PlayerInventory {
	
	int CurrentAmmo() override;
	int CurrentWeapon() override;
	bool HoldingWeapon() override;
};