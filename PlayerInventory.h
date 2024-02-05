#pragma once

class PlayerInventory {
public:
	virtual int CurrentAmmo() = 0;
	virtual int CurrentWeapon() = 0;
};