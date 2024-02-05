#pragma once
#include "../OWOAPI/Domain/Muscle.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "../PlayerBody.h"

class MockBody : public PlayerBody {
private:
	OWOGame::MusclesGroup muscleGroup = OWOGame::MusclesGroup({});
public:
	uniquePtr<OWOGame::Sensation> damageSensation = OWOGame::SensationsFactory::Create();
	MockBody(OWOGame::MusclesGroup muscles)
	{
		muscleGroup = muscles;
	}

	~MockBody(){}

	OWOGame::MusclesGroup LastHit() override;
	uniquePtr<OWOGame::Sensation>  DamageFelt() override;
};