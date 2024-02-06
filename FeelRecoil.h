#pragma once
#include "OWOAPI/Controller/OWO.h"
#include "PlayerInventory.h"
#include "SensationOfWeapons.h"

class FeelRecoil
{
private:
	sharedPtr<OWOGame::OWO> owo = nullptr;
	sharedPtr<PlayerInventory> playerInventory = nullptr;
	std::vector<SensationOfWeapons> sensations = {};

	int ammo = 0;
	int equipedWeapon = 0;

	void ResetEquipedWeapon();
	void SendRecoilSensation();
	bool DidShoot();
	bool DidChangeWeapon();
	void UpdateAmmo();
	uniquePtr<OWOGame::Sensation> RecoilSensation();
public:
	static const int Priority = 3;

	FeelRecoil(sharedPtr<OWOGame::OWO> device, sharedPtr<PlayerInventory> inventory, std::vector<SensationOfWeapons> sensations) : owo(device), playerInventory(inventory), sensations(sensations){}
	~FeelRecoil(){}
	void Execute();
};