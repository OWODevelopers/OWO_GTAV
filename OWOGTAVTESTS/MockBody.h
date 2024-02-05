#pragma once
#include "../OWOAPI/Domain/Muscle.h"
#include "../PlayerBody.h"

class MockBody : public PlayerBody {
public:
	MockBody(){}
	~MockBody(){}

	OWOGame::MusclesGroup LastHit() override;
};