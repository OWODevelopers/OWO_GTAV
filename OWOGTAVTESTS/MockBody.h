#pragma once
#include "../OWOAPI/Domain/Muscle.h"
#include "../PlayerBody.h"

class MockBody : public PlayerBody {
private:
	OWOGame::MusclesGroup muscleGroup = OWOGame::MusclesGroup({});
public:
	MockBody(OWOGame::MusclesGroup muscles)
	{
		muscleGroup = muscles;
	}
	~MockBody(){}

	OWOGame::MusclesGroup LastHit() override;
};