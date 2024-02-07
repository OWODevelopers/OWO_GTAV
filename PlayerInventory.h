#pragma once
#include "../OWOAPI/Domain/Sensation.h"

class PlayerInventory {
public:
	virtual int CurrentAmmo() = 0;
	virtual int CurrentWeapon() = 0;
	virtual bool HoldingWeapon() = 0;
};