#include "sdfgh.h"
#include "../OWOAPI/Domain/SensationsFactory.h"


void sdfgh::Execute(int hp)
{
	if (hp < lastHealth)
	{
		owo->Send(OWOGame::SensationsFactory::Create()->WithMuscles(body->LastHit().WithIntensity(OWOGame::Math::Clamp(lastHealth - hp, 20, 100))));
	}

	lastHealth = hp;
}