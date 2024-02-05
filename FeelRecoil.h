#pragma once
#include "OWOAPI/Controller/OWO.h"
#include "PlayerInventory.h"

class FeelRecoil
{
private:
	sharedPtr<OWOGame::OWO> owo = nullptr;
	sharedPtr<PlayerInventory> playerInventory = nullptr;

	int lastAmmo = 0;
	int lastWeapon = 0;
public:
	static const int Priority = 3;

	FeelRecoil(sharedPtr<OWOGame::OWO> device, sharedPtr<PlayerInventory> inventory) : owo(device), playerInventory(inventory){}
	~FeelRecoil(){}
	void Execute();
};