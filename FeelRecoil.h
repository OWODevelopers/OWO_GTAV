#pragma once
#include "OWOAPI/Controller/OWO.h"
#include "PlayerInventory.h"

class FeelRecoil
{
private:
	sharedPtr<OWOGame::OWO> owo = nullptr;
	sharedPtr<PlayerInventory> playerInventory = nullptr;
	int lastAmmo = 0;

public:
	FeelRecoil(sharedPtr<OWOGame::OWO> device, sharedPtr<PlayerInventory> inventory) : owo(device), playerInventory(inventory){}
	~FeelRecoil(){}
	void Execute();
};

