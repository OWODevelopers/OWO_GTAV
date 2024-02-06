#pragma once
#include "PlayerInventory.h"

class GTAInventory : public PlayerInventory {
	
	virtual int CurrentAmmo() override;
	virtual int CurrentWeapon() override;
};