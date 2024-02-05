#pragma once
#include "../OWOAPI/Domain/MusclesGroup.h"
#include "../OWOAPI/Domain/Sensation.h"

class PlayerBody {
public:
	PlayerBody(){}
	~PlayerBody() {};

	virtual OWOGame::MusclesGroup LastHit() = 0;
	virtual uniquePtr<OWOGame::Sensation> DamageFelt() = 0;
};