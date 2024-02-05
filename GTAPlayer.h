#pragma once
#include "../PlayerBody.h"

class GTAPlayer : PlayerBody
{
	virtual OWOGame::MusclesGroup LastHit() override;
	virtual uniquePtr<OWOGame::Sensation> DamageFelt() override;
};