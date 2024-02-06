#pragma once
#include "../PlayerBody.h"
#include <vector>
#include <types.h>
#include "../SensationOfWeapons.h"

enum DamagePrecision {
	Single,
	Side,
	General
};

class GTAPlayer : public PlayerBody
{
private:
	std::vector<SensationOfWeapons> weapons = {};
	DamagePrecision precision = General;

public:
	GTAPlayer(std::vector<SensationOfWeapons> weapons) : weapons(weapons) {}

	virtual OWOGame::MusclesGroup LastHit() override;
	virtual uniquePtr<OWOGame::Sensation> DamageFelt() override;
	const Ped& Player();
};