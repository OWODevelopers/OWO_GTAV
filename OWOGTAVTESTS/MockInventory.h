#pragma once
#include "../PlayerInventory.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

class MockInventory : public PlayerInventory{
private:
	int ammo = 0;
	int currentWeapon = 0;

public:
	int CurrentAmmo() override;
	int CurrentWeapon() override;
	bool HoldingWeapon() override;

	void Shoot();
	void Equip(int weapon);
	void Reload(int clipSize);
};