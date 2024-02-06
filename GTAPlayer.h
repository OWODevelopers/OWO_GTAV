#pragma once
#include "../PlayerBody.h"
#include <vector>
#include <types.h>
#include "../SensationOfWeapons.h"

class GTAPlayer : public PlayerBody
{
private:
	std::vector<SensationOfWeapons> weapons = {};

public:
	GTAPlayer(std::vector<SensationOfWeapons> weapons) : weapons(weapons) {}

	virtual OWOGame::MusclesGroup LastHit() override;
	virtual uniquePtr<OWOGame::Sensation> DamageFelt() override;
	const Ped& Player();
};