#pragma once
#include "../OWOAPI/Domain/MusclesGroup.h"

class PlayerBody {
public:
	PlayerBody(){}
	~PlayerBody() {};

	virtual OWOGame::MusclesGroup LastHit() = 0;
};