#pragma once
#include "OWOAPI/Controller/OWO.h"
#include "PlayerInventory.h"
#include "SensationOfWeapons.h"

class FeelRecoil
{
private:
	sharedPtr<OWOGame::OWO> owo = nullptr;
	sharedPtr<PlayerInventory> playerInventory = nullptr;
	SensationOfWeapons sensations = SensationOfWeapons({}, "");

	int ammo = 0;
	int equipedWeapon = 0;

	void ResetEquipedWeapon();
	void SendRecoilSensation();
	bool DidShoot();
	bool DidChangeWeapon();
	void UpdateAmmo();
	uniquePtr<OWOGame::Sensation> SensationOf(int weapon);
public:
	static const int Priority = 3;

	FeelRecoil(sharedPtr<OWOGame::OWO> device, sharedPtr<PlayerInventory> inventory, SensationOfWeapons sensations) : owo(device), playerInventory(inventory), sensations(sensations){}
	~FeelRecoil(){}
	void Execute();
};