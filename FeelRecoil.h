#pragma once
#include "OWOAPI/Controller/OWO.h"
#include "PlayerInventory.h"

class FeelRecoil
{
private:
	sharedPtr<OWOGame::OWO> owo = nullptr;
	sharedPtr<PlayerInventory> playerInventory = nullptr;

	int ammo = 0;
	int equipedWeapon = 0;

	void ResetEquipedWeapon();
	void SendRecoilSensation();
	bool DidShoot();
	bool DidChangeWeapon();
	void UpdateAmmo();
public:
	static const int Priority = 3;

	FeelRecoil(sharedPtr<OWOGame::OWO> device, sharedPtr<PlayerInventory> inventory) : owo(device), playerInventory(inventory){}
	~FeelRecoil(){}
	void Execute();
};